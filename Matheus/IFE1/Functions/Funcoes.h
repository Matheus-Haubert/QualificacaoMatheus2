#pragma once

#include <iostream>
#include <math.h>
#include <cstring>
#include <math.h>
#include <chrono>
#include <ctime>

#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/qvm/mat_operations.hpp>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>

#include <fstream>

#include "../Main.h"

using namespace boost::numeric::ublas;

class Funcoes
{
public:
    // F_Calculos: ----------------------------------------------
    static void Calculate();
    // F_MATRIX: ----------------------------------------------
    static int dij(int i, int j);
    static float sgn(float n);
    static matrix<float> InvertMatrix(matrix<float> input);
    static float Determinant(matrix<float> m);
    static void Zero(matrix<float> &m);
    static void Zero(vector<float> &v);
    static void PrintMatrix(std::string s, matrix<float> m);
    static void PrintVector(std::string s, vector<float> v);
    // F_PETSc: ----------------------------------------------
    static int SolveLS(matrix<float> _A, vector<float> _b, vector<float> &_x);
    // F_Prog: ----------------------------------------------
    static vector<float> Prod(matrix<float> M1, vector<float> V1);
    static std::string dtoc(float n);
};