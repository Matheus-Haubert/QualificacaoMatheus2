#include "Main.h"
#include <cmath>
#include "Functions/Funcoes.h"

#include <petscksp.h>
#include <metis.h>
// DEFINIÇÃO DE VARIÁVEIS: --------------------------------------------------------------------------------
static char help[] = "Code for solve 3D non linear analysis of elastic truss";

// VARIÁVEIS DO PROBLEMA
float m = 1, c = 0.25, k = 1, f = 0;
float nt = 100, tf = 10 * M_PI, dt = tf / nt;
float Y0 = 1, V0 = 0, A0 = (f - k * Y0 - c * V0) / m;

// CRONÔMETRO
std::chrono::duration<double> elapsed_seconds;
std::time_t end_time;

int main(int argc, char **args)
{
    PetscInitialize(&argc, &args, (char *)0, help);       // INICIANDO O PETSC
    auto start = std::chrono::system_clock::now();        // CRONOMETRO INICIADO
    Funcoes::Calculate();                                 //
    auto end = std::chrono::system_clock::now();          // CRONOMETRO DESLIGADO
    elapsed_seconds = end - start;                        // TEMPO DE PROCESSAMENTO
    end_time = std::chrono::system_clock::to_time_t(end); // HORÁRIO EM QUE O CRONOMETRO FOI DESLIGADO
    PetscFinalize();                                      // FINALIZANDO O PETSC
}