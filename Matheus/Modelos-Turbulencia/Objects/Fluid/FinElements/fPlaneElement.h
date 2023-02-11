#include <vector>
#include "../../../main.h"

using namespace boost::numeric::ublas;

class fPlaneElement
{
public:
    int Id;                 // IDENTIFICADOR
    int Idg;                // ID DA SUPERFÍCIE GERADORA
    fMaterial *Mat;         // MATERIAL QUE COMPÕE O ELEMENTO
    std::vector<fNode *> N; // NÓS LOCAIS DO ELEMENTO

    fPlaneElement(const int &_Id, const int &_Idg, fMaterial *_Mat, std::vector<fNode *> _No)
    {
        Id = _Id;
        Idg = _Idg;
        Mat = _Mat;
        N = _No;
    }
    ~fPlaneElement() {}
};