#pragma once

#include <iostream>
#include <math.h>
#include <cmath>
#include <cstring>
#include <chrono>
#include <ctime>
#include <unordered_map>

#include "sys/types.h"
#include "sys/sysinfo.h"

#include <petscksp.h>
#include <metis.h>
#include <petscmat.h>

#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/qvm/mat_operations.hpp>

#include <fstream>

#include "../main.h"

#define getCurrentDir getcwd
#define rm "rm "

using namespace boost::numeric::ublas;

class Funcoes
{
public:
    // F_Iniciate: ----------------------------------------------
    static void Iniciar();
    // F_Prog: ----------------------------------------------
    static std::string dtoc(double n);
    static std::vector<std::string> Split(std::string str, char delim);
    // F_Gmsh: ----------------------------------------------
    static std::string getCurrentWorkingDir();
    static void ExportToGeo(std::string FileName);
    static std::pair<std::string, bool> CreateMesh(const std::string &elementType, const std::string &algorithm, std::string geofile, const std::string &gmshPath, const bool &plotMesh, const bool &showInfo);
    static void GenerateMesh(const std::string &elementType, const std::string &algorithm, std::string geofile, const std::string &gmshPath, const bool &plotMesh, const bool &showInfo);
    static void ReadInput(const std::string &inputFile, const bool &deleteFiles);
    static void domainDecompositionMETIS();
    // F_Paraview: ----------------------------------------------
    static void ExportToParaview(std::string Name, int nt);
    // F_PETSc: ----------------------------------------------
};