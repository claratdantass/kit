#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"
#include "Construcao.h"

bool bestImprovementSwap(Solution *s, Data& data);

bool bestImprovement2Opt(Solution vParcial, Data& data);

bool bestImprovementOrOpt(Solution sParcial, int N, Data& data);

void BuscaLocal(Solution vParcial, Data& data);



