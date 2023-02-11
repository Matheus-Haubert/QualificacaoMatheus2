#include "Funcoes.h"

void Funcoes::Iniciar()
{
    Exemplos::Exemplo1();                                    // EXEMPLO
    ExportToGeo(GmshName);                                   // EXPORTAR PARA GEO
    GenerateMesh("T6", "FRONT", GmshName, "", false, false); // GERA A MALHA E CRIA OS OBJETOS
    ExportToParaview("x", 0);

    if (rank == 0)
    {
        for (fKP *KP : fKPs)
            std::cout << "KP[" << KP->Id << "] = (" << KP->X[0] << ", " << KP->X[1] << ")\n";
        for (fLine *L : fLines)
            std::cout << "L[" << L->Id << "] = " << L->L << "\n";
        for (fNode *N : fNodes)
            std::cout << "No[" << N->Id << "] - " << nodePartition_[N->Id] << " = (" << N->X[0] << ", " << N->X[1] << ")\n";
        for (fPlaneElement *PE : fPlaneElements)
        {
            std::cout << "PE[" << PE->Id << "] - " << elementPartition_[PE->Id] << ": ";
            for (fNode *N : PE->N)
                std::cout << N->Id << " ";
            std::cout << "\n";
        }
    }
}