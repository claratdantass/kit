#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"

typedef struct Solution {
    std::vector<int> sequencia;
    double valorObj;
} Solution;

bool bestImprovementSwap(Solution *s){
    double bestDelta = 0;
    int best_i, best_j;
    for(int i = 1; i < s->sequencia.size() - 1; i++){
        int vi = s->sequencia[i];
        int vi_next = s->sequencia[i + 1];
        int vi_prev = s->sequencia[i - 1];

        for(int j = i + 1; j < s->sequencia.size() - 1; j++){
            int vj = s->sequencia[j];
            int vj_next = s->sequencia[j + 1];
            int vj_prev = s->sequencia[j - 1];
            double delta = - data.getDistance(vi_prev, vi) - data.getDistance(vi, vi_next) + data.getDistance(vi_prev, vj)
                         + data.getDistance(vj, vi_next) - data.getDistance(vj_prev, vj) - data.getDistance(vj, vj_next)
                         + data.getDistance(vj_prev, vi) + data.getDistance(vi, vj_next);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0){
        std::swap(s->sequencia[best_i], s->sequencia[best_j]);
        s->valorObj = s->valorObj + bestDelta;
        return true;
    }
    return false;
}
bool bestImprovement2Opt(Solution vParcial) {
    double bestDelta = 0.0;
    int best_i, best_j;
    
    for (int i = 0; i < vParcial.sequencia.size() - 1; ++i) {
        for (int j = i + 2; j < vParcial.sequencia.size(); ++j) { 
            int vi = vParcial.sequencia[i];
            int vi_next = vParcial.sequencia[i + 1];
            int ej = vParcial.sequencia[j];
            int ej_next = (j + 1 < vParcial.sequencia.size()) ? vParcial.sequencia[j + 1] : vParcial.sequencia[0]; 

            double delta = - data.getDistance(vi, vi_next) 
                           - data.getDistance(ej, ej_next) 
                           + data.getDistance(vi, ej) 
                           + data.getDistance(vi_next, ej_next);
            
            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestDelta < 0) {
        std::reverse(vParcial.sequencia.begin() + best_i + 1, vParcial.sequencia.begin() + best_j + 1);
        return true; 
    }
    
    return false; 
}

bool bestImprovementOrOpt(Solution sParcial, int N){
    double bestDelta = 0.0;
    int best_i, best_j;
    
        

    
}

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
