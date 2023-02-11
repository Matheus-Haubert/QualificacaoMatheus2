#include <vector>
#include "../../../main.h"

using namespace boost::numeric::ublas;

class fNode
{
public:
    int Id;                // IDENTIFICADOR
    std::vector<double> X; // POSIÇÃO INICIAL

    fNode() {}
    fNode(const int &_Id, const std::vector<double> &_x)
    {
        Id = _Id;
        X = _x;
    }
    ~fNode() {}
};