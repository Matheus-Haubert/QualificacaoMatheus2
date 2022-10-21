#pragma once

#include "Functions/Funcoes.h"

using namespace boost::numeric::ublas;

// VARIÁVEIS DO PROBLEMA
extern float m, c, k, f;
extern float nt, tf, dt;
extern float Y0, V0, A0;

// CRONÔMETRO
extern std::chrono::duration<double> elapsed_seconds;
extern std::time_t end_time;