#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"
#include "Construcao.h"

bool bestImprovementSwap(Solution& sParcial, Data& data);

bool bestImprovement2Opt(Solution& sParcial, Data& data);

bool bestImprovementOrOpt(Solution& sParcial, int N, Data& data);

void BuscaLocal(Solution& sParcial, Data& data);



