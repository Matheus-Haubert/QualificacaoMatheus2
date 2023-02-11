#include "Funcoes.h"

std::string Funcoes::getCurrentWorkingDir()
{
    char buff[FILENAME_MAX];
    getCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}
void Funcoes::ExportToGeo(std::string FileName)
{
    char tmp[256];
    getcwd(tmp, 256);
    std::string path = tmp;
    std::stringstream text;
    text << path + "/../Geo/" + FileName + ".geo";
    std::ofstream file(text.str());
    file << std::fixed;
    for (fKP *KP : fKPs)
        file << "p" << KP->Id << " = newp; Point(p" << KP->Id << ") = {" << KP->X[0] << ", " << KP->X[1] << ", 0.0, " << 1. << "}; Physical Point('p" << KP->Id << "') = {p" << KP->Id << "};\n//\n";
    for (fLine *L : fLines)
        file << "l" << L->Id << " = newl; Line(l" << L->Id << ") = {p" << L->KP[0]->Id << ", p" << L->KP[1]->Id << "}; Physical Line('l" << L->Id << "') = {l" << L->Id << "};\n//\n";
    for (fSurface *S : fSurfaces)
    {
        file << "ll" << S->Id << " = newll; Line Loop(ll" << S->Id << ") = {";
        for (int i = 0; i < S->L.size(); i++)
        {
            file << "l" << S->L[i]->Id;
            if (i != S->L.size() - 1)
                file << ", ";
        }
        file << "};\n//\n";
        file << "s" << S->Id << " = news; Plane Surface(s" << S->Id << ") = {ll" << S->Id << "}; Physical Surface('s" << S->Id << "') = {s" << S->Id << "};\n//\n";
    }
    for (fLine *L : fLines)
        file << "Transfinite Line {l" << L->Id << "} = " << L->Divisions << " Using Progression 1;\n//\n";
}

void Funcoes::GenerateMesh(const std::string &elementType, const std::string &algorithm, std::string geofile, const std::string &gmshPath, const bool &plotMesh, const bool &showInfo)
{
    std::pair<std::string, bool> pair;
    pair.second = false;
    if (rank == 0)
    {
        pair = CreateMesh(elementType, algorithm, geofile, gmshPath, plotMesh, showInfo);
        for (int i = 1; i < size; i++)
        {
            MPI_Send(pair.first.c_str(), pair.first.length() + 1, MPI_CHAR, i, 0, PETSC_COMM_WORLD);
            if (i == size - 1)
            {
                MPI_Send(&pair.second, 1, MPI_C_BOOL, i, 0, PETSC_COMM_WORLD);
                pair.second = false;
            }
        }
    }
    else
    {
        MPI_Status status;
        MPI_Probe(0, 0, PETSC_COMM_WORLD, &status);
        int count;
        MPI_Get_count(&status, MPI_CHAR, &count);
        char buf[count + 1];
        MPI_Recv(&buf, count + 1, MPI_CHAR, 0, 0, PETSC_COMM_WORLD, &status);
        pair.first = buf;
        if (rank == size - 1)
            MPI_Recv(&pair.second, 1, MPI_C_BOOL, 0, 0, PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    ReadInput(pair.first, pair.second);
    domainDecompositionMETIS();
}
std::pair<std::string, bool> Funcoes::CreateMesh(const std::string &elementType, const std::string &algorithm, std::string FileName, const std::string &gmshPath, const bool &plotMesh, const bool &showInfo)
{
    char tmp[256];
    getcwd(tmp, 256);
    std::string path = tmp;
    std::string geofile = path + "/../Geo/" + FileName;

    std::string mshfile;
    bool deleteFiles = geofile.empty();
    if (deleteFiles)
        mshfile = geofile + "temp.msh", geofile = geofile + "temp.geo";
    else
        mshfile = geofile + ".msh", geofile = geofile + ".geo";

    // std::cout << geofile << "\n";

    std::string gmshExe = (gmshPath.empty()) ? getCurrentWorkingDir() + "/../gmsh" : gmshPath;
    std::string cmd = gmshExe;
    cmd += " -2 -clscale 1.0 " + geofile + " -o " + mshfile;

    if (algorithm == "FRONT")
        cmd += " -algo front2d";
    else if (algorithm == "DELAUNAY")
        cmd += " -algo del2d";
    else if (algorithm == "ADAPT")
        cmd += " -algo meshadapt";
    else if (algorithm == "PACK")
        cmd += " -algo pack";
    else if (algorithm == "QUAD")
        cmd += " -algo delquad";
    else if (algorithm == "BAMG")
        cmd += " -algo bamg";

    if (elementType == "T3" || elementType == "Q4")
        cmd += " -order 1";
    else if (elementType == "T6" || elementType == "Q8" || elementType == "Q9")
    {
        cmd += " -order 2";
        if (elementType == "Q8")
            cmd += " -string Mesh.SecondOrderIncomplete=1;";
    }
    else if (elementType == "T10" || elementType == "Q12" || elementType == "Q16")
    {
        cmd += " -order 3";
        if (elementType == "Q12")
            cmd += " -string Mesh.SecondOrderIncomplete=1;";
    }
    else
    {
        std::cout << "Element " << elementType << " is not supported.";
        exit(EXIT_FAILURE);
    }

    if (!showInfo)
        cmd += " -v 0";

    system(cmd.c_str());

    if (deleteFiles)
        system((rm + geofile).c_str());

    if (plotMesh)
        system((gmshExe + " " + mshfile).c_str());

    return std::make_pair(mshfile, deleteFiles);
}
void Funcoes::ReadInput(const std::string &inputFile, const bool &deleteFiles)
{
    std::unordered_map<int, std::string> gmshElement = {{1, "line"}, {2, "triangle"}, {3, "quadrilateral"}, {8, "line3"}, {9, "triangle6"}, {10, "quadrilateral9"}, {15, "vertex"}, {16, "quadrilateral8"}, {20, "triangle9"}, {21, "triangle10"}, {26, "line4"}, {36, "quadrilateral16"}, {39, "quadrilateral12"}};
    std::unordered_map<std::string, int> numNodes = {{"vertex", 1}, {"line", 2}, {"triangle", 3}, {"quadrilateral", 4}, {"line3", 3}, {"triangle6", 6}, {"quadrilateral8", 8}, {"quadrilateral9", 9}, {"line4", 4}, {"triangle", 9}, {"triangle10", 10}, {"quadrilateral12", 12}, {"quadrilateral16", 16}};
    std::unordered_map<std::string, std::string> supportedElements = {{"triangle", "T3"}, {"triangle6", "T6"}, {"triangle10", "T10"}, {"quadrilateral", "Q4"}, {"quadrilateral8", "Q8"}, {"quadrilateral9", "Q9"}, {"quadrilateral12", "Q12"}, {"quadrilateral16", "Q16"}};

    std::ifstream file(inputFile);                                                                          // ABRE O ARQUIVO .msh
    std::string line;                                                                                       // LÊ A LINHA
    std::getline(file, line), std::getline(file, line), std::getline(file, line), std::getline(file, line); // PULA QUATRO LINHAS

    int number_physical_entities;                                            // NÚMERO DE PhysicalEntities
    file >> number_physical_entities;                                        // RECEBE O NÚMERO DE PhysicalEntities
    std::getline(file, line);                                                // PRÓXIMA LINHA
    std::unordered_map<int, std::string> physicalEntities;                   // CRIA AS PhysicalEntities
    physicalEntities.reserve(number_physical_entities);                      // DEFINE O NÚMERO DE PhysicalEntities
    for (int i = 0; i < number_physical_entities; i++)                       //
    {                                                                        //
        std::getline(file, line);                                            // PRÓXIMA LINHA
        std::vector<std::string> tokens = Split(line, ' ');                  // SEPARA POR ESPAÇO
        int index;                                                           // ÍNDICE
        std::istringstream(tokens[1]) >> index;                              // DEFINE ÍNDICE
        physicalEntities[index] = tokens[2].substr(1, tokens[2].size() - 2); // RETIRA AS ASPAS E DEFINE A PhysicalEntity
    }                                                                        //
    std::getline(file, line), std::getline(file, line);                      // PULA DUAS LINHAS

    int number_nodes;                                         // LÊ NÚMERO DE NÓS
    file >> number_nodes;                                     // RECEBE NÚMERO DE NÓS
    std::getline(file, line);                                 // PRÓXIMA LINHA
    for (int i = 0; i < number_nodes; i++)                    //
    {                                                         //
        std::getline(file, line);                             // PRÓXIMA LINHA
        std::vector<std::string> tokens = Split(line, ' ');   // SEPARA POR ESPAÇO
        std::vector<double> coord(2);                         // COORDENADAS
        coord = {std::stod(tokens[1]), std::stod(tokens[2])}; // RECEBE AS COORDENADAS
        fNodes.push_back(new fNode(i, coord));                // CRIA O NÓ
    }                                                         //
    std::getline(file, line), std::getline(file, line);       // PULA LINHA

    // reading elements
    int number_elements;
    file >> number_elements;
    std::getline(file, line);
    int cont = 0;
    for (int ne = 0; ne < number_elements; ne++)
    {
        std::getline(file, line);
        std::vector<std::string> tokens = Split(line, ' ');
        std::vector<int> values(tokens.size(), 0);
        for (size_t j = 0; j < tokens.size(); j++)
            std::istringstream(tokens[j]) >> values[j];
        std::string elementType = gmshElement[values[1]];
        int number_nodes_per_element = numNodes[elementType];
        std::string name = physicalEntities[values[3]];
        int _s = std::stoi(name.substr(1, name.size())); // RETIRA O PRIMEIRO CARACTER E TRANSFORMA EM INT
        if (name[0] == 's')                              // ADICIONANDO OS ELEMENTOS PLANOS
        {
            if (supportedElements.find(elementType) == supportedElements.end())
            {
                std::cout << elementType << " is not supported.\n";
                exit(EXIT_FAILURE);
            }
            fMaterial *_M = fSurfaces[_s]->M; // BUSCA A SUPERFÍCIE E O MATERIAL
            std::vector<fNode *> _N;
            for (int i = 0; i < number_nodes_per_element; i++)
                _N.push_back(fNodes[values[5 + i] - 1]);
            fPlaneElements.push_back(new fPlaneElement(fPlaneElements.size(), _s, _M, _N));
        }
        else if (name[0] == 'l') // ADICIONANDO OS ELEMENTOS LINEARES
        {
            std::vector<fNode *> _N;
            for (int i = 0; i < number_nodes_per_element; i++)
                _N.push_back(fNodes[values[5 + i] - 1]);
            fLineElements.push_back(new fLineElement(fLineElements.size(), _s, _N));
        }
    }
    file.close(); // FECHANDO O ARQUIVO
    if (deleteFiles)
        system((rm + inputFile).c_str());
}
void Funcoes::domainDecompositionMETIS()
{
    std::string mirror2 = "domain_decomposition.txt";
    std::ofstream mirrorData(mirror2.c_str());

    idx_t objval;
    idx_t numEl = fPlaneElements.size();
    idx_t numNd = fNodes.size();
    idx_t ssize = size;
    idx_t one = 1;
    idx_t n = fPlaneElements[0]->N.size();
    idx_t elem_start[numEl + 1], elem_connec[n * numEl];
    elementPartition_ = new idx_t[numEl];
    nodePartition_ = new idx_t[numNd];

    for (idx_t i = 0; i < numEl + 1; i++)
        elem_start[i] = n * i;
    for (idx_t jel = 0; jel < numEl; jel++)
        for (idx_t i = 0; i < fPlaneElements[jel]->N.size(); i++)
            elem_connec[n * jel + i] = fPlaneElements[jel]->N[i]->Id;

    METIS_PartMeshDual(&numEl, &numNd, elem_start, elem_connec, NULL, NULL, &one, &ssize, NULL, NULL, &objval, elementPartition_, nodePartition_);

    mirrorData << "\nELEMENTS" << std::endl;
    for (int i = 0; i < fPlaneElements.size(); i++)
        mirrorData << "process = " << elementPartition_[i] << ", element = " << i << std::endl;

    mirrorData << "\nNODES" << std::endl;
    for (int i = 0; i < fNodes.size(); i++)
        mirrorData << "process = " << nodePartition_[i] << ", node = " << i << std::endl;
}