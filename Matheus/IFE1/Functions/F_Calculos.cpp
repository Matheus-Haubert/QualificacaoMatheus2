#include "Funcoes.h"

void Funcoes::Calculate()
{
    matrix<float> A(3, 3, 0);
    vector<float> b(3, 0), YY(3, 0);
    YY <<= Y0, V0, A0;
    A <<= k, c, m, 1, 0, -pow(dt, 2) / 4, 0, 1, -dt / 2;
    for (float ti = 0; ti <= tf; ti += dt)
    {
        b <<= f, YY(0) + YY(1) * dt + YY(2) / 4 * pow(dt, 2), YY(1) + YY(2) / 2 * dt;
        SolveLS(A, b, YY);
        std::cout << dtoc(ti + dt) << ";" << dtoc(YY(0)) << "\n";
    }
}