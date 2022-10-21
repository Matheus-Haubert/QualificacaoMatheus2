#include "Funcoes.h"

int Funcoes::dij(int i, int j)
{
    if (i == j)
        return 1;
    else
        return 0;
}
float Funcoes::sgn(float n)
{
    if (n > 0)
        return 1;
    else if (n < 0)
        return -1;
    else
        return 0;
}
matrix<float> Funcoes::InvertMatrix(matrix<float> M)
{
    assert(M.size1() == M.size2() && "Can only calculate the invert of square matrices");
    matrix<float> Mi(M), A(M);
    permutation_matrix<std::size_t> pivots(M.size1());
    const int is_singular = lu_factorize(A, pivots);
    if (is_singular)
        return Mi;
    Mi.assign(identity_matrix<float>(A.size1()));
    lu_substitute(A, pivots, Mi);
    return Mi;
}
float Funcoes::Determinant(matrix<float> M)
{
    assert(M.size1() == M.size2() && "Can only calculate the determinant of square matrices");
    permutation_matrix<std::size_t> pivots(M.size1());
    const int is_singular = lu_factorize(M, pivots);
    if (is_singular)
        return 0;
    float d = 1;
    const std::size_t sz = pivots.size();
    for (std::size_t i = 0; i != sz; ++i)
    {
        if (pivots(i) != i)
            d *= -1;
        d *= M(i, i);
    }
    return d;
}
void Funcoes::Zero(matrix<float> &m)
{
    matrix<float> m2(m.size1(), m.size2(), 0);
    m = m2;
}
void Funcoes::Zero(vector<float> &v)
{
    vector<float> v2(v.size(), 0);
    v = v2;
}
void Funcoes::PrintMatrix(std::string s, matrix<float> m)
{
    if (s != "")
        printf("%s\n", s.c_str());
    for (int i = 0; i < m.size1(); i++)
    {
        for (int j = 0; j < m.size2(); j++)
        {
            printf("%f\t", m(i, j));
        }
        printf("\n");
    }
}
void Funcoes::PrintVector(std::string s, vector<float> v)
{
    if (s != "")
        printf("%s ", s.c_str());
    printf("(");
    for (int i = 0; i < v.size(); i++)
    {
        printf("%f", v(i));
        if (i < v.size() - 1)
            printf(",\t");
    }
    printf(")\n");
}