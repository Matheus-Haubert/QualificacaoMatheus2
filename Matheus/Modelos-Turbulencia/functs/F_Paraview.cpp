#include "Funcoes.h"

double esc = 1;

void Funcoes::ExportToParaview(std::string Name, int nt)
{
    char tmp[256];
    getcwd(tmp, 256);
    std::string path = tmp;
    std::stringstream text;
    text << path << "/Output_vtu/" << Name << nt << ".vtu";
    std::ofstream file(text.str());
    file << "<?xml version=\"1.0\"?>\n"
         << "<VTKFile type=\"UnstructuredGrid\">\n"
         << "  <UnstructuredGrid>\n"
         << "  <Piece NumberOfPoints=\"" << fNodes.size()
         << "\"  NumberOfCells=\"" << fPlaneElements.size() << "\">\n"; // HEADER
    file << "    <Points>\n"                                            // NODAL COORDINATES - BEGIN
         << "      <DataArray type=\"Float64\" "
         << "NumberOfComponents=\"3\" format=\"ascii\">"
         << "\n";
    for (fNode *N : fNodes)
    {
        if (Name != "x")
            // file << N->X[0] + esc * (N->Y[0] - N->X[0]) << " " << N->X[1] + esc * (N->Y[1] - N->X[1]) << " " << 0.0 << "\n";
            file << N->X[0] << " " << N->X[1] << " " << 0.0 << "\n";
        else
            file << N->X[0] << " " << N->X[1] << " " << 0.0 << "\n";
    }
    file << "      </DataArray>\n"
         << "    </Points>\n"; // NODAL COORDINATES - END
    file << "    <Cells>\n"
         << "      <DataArray type=\"Int32\" "
         << "Name=\"connectivity\" format=\"ascii\">\n"; // ELEMENT CONNECTIVITY - BEGIN
    for (fPlaneElement *PE : fPlaneElements)
    {
        for (int i = 0; i < PE->N.size(); i++)
            file << PE->N[i]->Id << " ";
        file << "\n";
    }
    file << "      </DataArray>\n";                                                 // ELEMENT CONNECTIVITY -END
    file << "      <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n"; // OFFSETS - BEGIN
    int aux = 0;
    for (fPlaneElement *PE : fPlaneElements)
    {
        aux += PE->N.size();
        file << aux << "\n";
    }
    file << "      </DataArray>\n";                                               // OFFSETS - END
    file << "      <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n"; // ELEMENTS TYPE - BEGIN
    for (fPlaneElement *PE : fPlaneElements)
        file << 69 << "\n";
    file << "      </DataArray>\n"; // ELEMENTS TYPE - END
    file << "    </Cells>\n";
    // if (Name != "x")
    //{
    //     file << "    <PointData>\n"; // NODAL RESULTS - BEGIN
    //     file << "      <DataArray type=\"Float64\" NumberOfComponents=\"2\" Name=\"Displacement\" format=\"ascii\">\n";
    //     for (fNode *N : fNodes)
    //         file << N->Y[0] - N->X[0] << " " << N->Y[1] - N->X[1] << "\n";
    //     file << "      </DataArray> \n";
    //     if (Analise == 1)
    //     {
    //         file << "      <DataArray type=\"Float64\" NumberOfComponents=\"2\" Name=\"Velocity\" format=\"ascii\">\n";
    //         for (fNode *N : fNodes)
    //             file << N->V[0] << " " << N->V[1] << "\n";
    //         file << "      </DataArray> \n";
    //         file << "      <DataArray type=\"Float64\" NumberOfComponents=\"2\" Name=\"Acceleration\" format=\"ascii\">\n";
    //         for (fNode *N : fNodes)
    //             file << N->A[0] << " " << N->A[1] << "\n";
    //         file << "      </DataArray> \n";
    //     }
    //     file << "      <DataArray type=\"Float64\" NumberOfComponents=\"2\" Name=\"Normal Strain\" format=\"ascii\">\n";
    //     for (fNode *N : fNodes)
    //         file << N->E(0, 0) << " " << N->E(1, 1) << "\n";
    //     file << "      </DataArray> \n";
    //     file << "      <DataArray type=\"Float64\" NumberOfComponents=\"\" Name=\"Shear Strain\" format=\"ascii\">\n";
    //     for (fNode *N : fNodes)
    //         file << N->E(0, 1) << "\n";
    //     file << "      </DataArray> \n";
    //     file << "      <DataArray type=\"Float64\" NumberOfComponents=\"2\" Name=\"Normal Stress\" format=\"ascii\">\n";
    //     for (fNode *N : fNodes)
    //         file << N->s(0, 0) << " " << N->s(1, 1) << "\n";
    //     file << "      </DataArray> \n";
    //     file << "      <DataArray type=\"Float64\" NumberOfComponents=\"\" Name=\"Shear Stress\" format=\"ascii\">\n";
    //     for (fNode *N : fNodes)
    //         file << N->s(0, 1) << "\n";
    //     file << "      </DataArray> \n";
    //     file << "    </PointData>\n"; // NODAL RESULTS - END
    //                                   // file << "    <CellData>\n";   // ELEMENTAL RESULTS - BEGIN
    //                                   // file << "      <DataArray type=\"Float64\" NumberOfComponents=\"1\" Name=\"Normal Force\" format=\"ascii\">\n";
    //                                   // for (Elements e : Elementos)
    //                                   //     file << e.fn << "\n";
    //                                   // file << "      </DataArray> \n";
    //                                   // file << "    </CellData>\n"; // ELEMENTAL RESULTS - END
    // }
    file << "  </Piece>\n" // FOOTNOTE
         << "  </UnstructuredGrid>\n"
         << "</VTKFile>\n";
}