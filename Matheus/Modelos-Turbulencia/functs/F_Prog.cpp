#include "Funcoes.h"

std::string Funcoes::dtoc(double n)
{
    std::string s = std::to_string(n);
    std::replace(s.begin(), s.end(), '.', ',');
    return s;
}
std::vector<std::string> Funcoes::Split(std::string str, char delim)
{
    std::istringstream is(str);
    std::vector<std::string> values;
    std::string token;
    while (getline(is, token, delim))
        values.push_back(token);
    return values;
}