#include <vector>

class fKP
{
public:
    int Id;                // IDENTIFICADOR
    std::vector<double> X; // POSIÇÃO INICIAL

    fKP() {}
    fKP(const int &_Id, const std::vector<double> _x)
    {
        Id = _Id;
        X = _x;
    }
    ~fKP() {}
};