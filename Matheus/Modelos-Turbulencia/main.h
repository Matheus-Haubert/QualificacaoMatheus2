#pragma once
#include "functs/Funcoes.h"
#include "inputs/Exemplos.h"

// BASE FLUID ELEMENTS
#include "Objects/Fluid/BaseElements/fKP.h"
#include "Objects/Fluid/BaseElements/fLine.h"
#include "Objects/Fluid/BaseElements/fMaterial.h"
#include "Objects/Fluid/BaseElements/fSurface.h"
// FINITE FLUID ELEMENTS
#include "Objects/Fluid/FinElements/fNode.h"
#include "Objects/Fluid/FinElements/fLineElement.h"
#include "Objects/Fluid/FinElements/fPlaneElement.h"

using namespace boost::numeric::ublas;

extern std::string InputName;
extern int Analise; // ANALISE: 0 - ESTÁTICA; 1 - DINÂMICA

// ===========================================================================
// PETSc
// ===========================================================================
extern idx_t *elementPartition_; // PARTIÇÃO DOS ELEMENTOS
extern idx_t *nodePartition_;    // PARTIÇÃO DOS NÓS
extern int rank;                 // NÚMERO DO PROCESSADOR
extern int size;                 // NÚMERO DE PROCESSADORES UTILIZADOS
extern PetscScalar value;        // VALOR

// ===========================================================================
// GMSH
// ===========================================================================
extern std::string GmshName; // NOME DO ARQUIVO GMSH

// ===========================================================================
// VARIÁVEIS DO PROBLEMA
// ===========================================================================

// BASE FLUID ELEMENTS
extern std::vector<fKP *> fKPs;             // LISTA DE PONTOS CHAVE
extern std::vector<fLine *> fLines;         // LISTA DE LINHAS
extern std::vector<fMaterial *> fMaterials; // LISTA DE MATERIAIS
extern std::vector<fSurface *> fSurfaces;   // LISTA DE SUPERFÍCIES
// FINITE FLUID ELEMENTS
extern std::vector<fNode *> fNodes;                 // LISTA DE NÓS
extern std::vector<fLineElement *> fLineElements;   // LISTA DE ELEMENTOS LINEARES
extern std::vector<fPlaneElement *> fPlaneElements; // LISTA DE ELEMENTOS PLANOS

// ===========================================================================
// CRONÔMETRO
// ===========================================================================
extern std::time_t end_time;