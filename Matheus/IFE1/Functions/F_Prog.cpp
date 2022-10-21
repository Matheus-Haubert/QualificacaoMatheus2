#include "Funcoes.h"

vector<float> Funcoes::Prod(matrix<float> M1, vector<float> V1)
{
    vector<float> V2(V1.size(), 0);
    axpy_prod(M1, V1, V2);
    return V2;
}
std::string Funcoes::dtoc(float n)
{
    std::string s = std::to_string(n);
    std::replace(s.begin(), s.end(), '.', ',');
    return s;
}