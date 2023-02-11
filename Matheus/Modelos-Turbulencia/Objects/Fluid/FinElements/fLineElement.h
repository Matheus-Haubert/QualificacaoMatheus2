#include <vector>
#include "../../../main.h"

class fLineElement
{
public:
    int Id;                 // IDENTIFICADOR
    int Idg;                // ID DA LINHA GERADORA
    std::vector<fNode *> N; // NÓS LOCAIS DO ELEMENTO

    fLineElement(const int &_Id, const int &_Idg, std::vector<fNode *> _No)
    {
        Id = _Id;
        Idg = _Idg;
        N = _No;
    }
    ~fLineElement() {}
};