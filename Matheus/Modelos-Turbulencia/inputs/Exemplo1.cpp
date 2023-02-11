#include "Exemplos.h"

void Exemplos::Exemplo1()
{
    fKPs.push_back(new fKP(fKPs.size(), {1, 1}));
    fKPs.push_back(new fKP(fKPs.size(), {20, 1}));
    fKPs.push_back(new fKP(fKPs.size(), {20, 9}));
    fKPs.push_back(new fKP(fKPs.size(), {1, 9}));

    fLines.push_back(new fLine(fLines.size(), fKPs[0], fKPs[1], 5));
    fLines.push_back(new fLine(fLines.size(), fKPs[1], fKPs[2], 5));
    fLines.push_back(new fLine(fLines.size(), fKPs[2], fKPs[3], 5));
    fLines.push_back(new fLine(fLines.size(), fKPs[3], fKPs[0], 5));

    fMaterials.push_back(new fMaterial(fMaterials.size(), 1E-3, 1000)); // EXEMPLO DE ÁGUA

    fSurfaces.push_back(new fSurface(fSurfaces.size(), fMaterials[0], {fLines[0], fLines[1], fLines[2], fLines[3]}));
}