#include "main.h"

std::string InputName;

// ===========================================================================
// PETSc
// ===========================================================================
static char help[] = "Code Test";
idx_t *elementPartition_, *nodePartition_;
int rank, size;
PetscScalar value;

// ===========================================================================
// GMSH
// ===========================================================================
std::string GmshName = "GmshExport"; // NOME DO ARQUIVO GMSH

// ===========================================================================
// VARIÁVEIS DO PROBLEMA
// ===========================================================================

// BASE FLUID ELEMENTS
std::vector<fKP *> fKPs;             // LISTA DE KEYPOINTS
std::vector<fLine *> fLines;         // LISTA DE LINHAS
std::vector<fMaterial *> fMaterials; // LISTA DE MATERIAIS
std::vector<fSurface *> fSurfaces;   // LISTA DE SUPERFÍCIES
// FINITE FLUID ELEMENTS
std::vector<fNode *> fNodes;                 // LISTA DE NÓS
std::vector<fLineElement *> fLineElements;   // LISTA DE ELEMENTOS LINEARES
std::vector<fPlaneElement *> fPlaneElements; // LISTA DE ELEMENTOS PLANOS

// ===========================================================================
// CRONÔMETRO
// ===========================================================================
std::time_t end_time;

int main(int argc, char **args)
{
    PetscInitialize(&argc, &args, (char *)0, help); // INICIANDO O PETSC
    MPI_Comm_rank(PETSC_COMM_WORLD, &rank);         // DEFINE O NÚMERO DO PROCESSO
    MPI_Comm_size(PETSC_COMM_WORLD, &size);         // RECEBE O NÚMERO DE PROCESSOS
    Funcoes::Iniciar();                             // INICIAR
    PetscFinalize();                                // FINALIZANDO O PETSC
}