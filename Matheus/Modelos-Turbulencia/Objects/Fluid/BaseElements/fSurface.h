#include <vector>
#include "../../../main.h"

class fSurface
{
public:
    int Id;                 // IDENTIFICADOR
    std::vector<fLine *> L; // LINHAS QUE DELIMITAM A SUPERFÍCIE
    fMaterial *M;           // MATERIAL QUE COMPÕE O ELEMENTO

    fSurface() {}
    fSurface(const int &_Id, fMaterial *_M, std::vector<fLine *> _L)
    {
        Id = _Id;
        L = _L;
        M = _M;
    }
    ~fSurface() {}
};