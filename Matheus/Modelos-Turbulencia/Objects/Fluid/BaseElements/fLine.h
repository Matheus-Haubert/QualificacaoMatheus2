#include <vector>
#include "../../../main.h"

class fLine
{
public:
    int Id;                // IDENTIFICADOR
    std::vector<fKP *> KP; // NÓS LOCAIS DO ELEMENTO
    double L;              // COMPRIMENTO DA LINHA
    int Divisions;         // DIVISÕES

    fLine() {}
    fLine(const int &_Id, fKP *_KP1, fKP *_KP2, const int &_Div)
    {
        Id = _Id;
        KP.push_back(_KP1);
        KP.push_back(_KP2);
        Divisions = _Div;
        L = sqrt(pow(KP[1]->X[0] - KP[0]->X[0], 2) + pow(KP[1]->X[1] - KP[0]->X[1], 2));
    }
    ~fLine() {}
};