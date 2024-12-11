#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

typedef struct Solution {
    std::vector<int> sequencia;
    double valorObj;
} Solution;


void BuscaLocal(Solution vParcial){
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while (!NL.empty()) {
        int n = rand() % NL.size();
        switch (NL[n]) {
            case 1:
                improved = bestImprovementSwap(vParcial);
                break;
            case 2:
                improved = bestImprovement2Opt(vParcial);
                break;
            case 3:
                improved = bestImprovementOrOpt(vParcial, 1); // Reinsertion
                break;
            case 4:
                improved = bestImprovementOrOpt(vParcial, 2); // Or-opt2
                break;
            case 5:
                improved = bestImprovementOrOpt(vParcial, 3); // Or-opt3
                break;
        }

        if (improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}