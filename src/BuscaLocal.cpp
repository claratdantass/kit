#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"
#include "BuscaLocal.h"

bool bestImprovementSwap(Solution s, Data& data){
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 1; i < s.sequencia.size() - 1; i++){
        int vi = s.sequencia[i];
        int vi_next = s.sequencia[i + 1];
        int vi_prev = s.sequencia[i - 1];
        for(int j = i + 1; j < s.sequencia.size() - 1; j++){
            int vj = s.sequencia[j];
            int vj_next = s.sequencia[j + 1];
            int vj_prev = s.sequencia[j - 1];

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
        std::swap(s.sequencia[best_i], s.sequencia[best_j]);
        s.valorObj = s.valorObj + bestDelta;
        return true;
    }

    return false;
}

bool bestImprovement2Opt(Solution sParcial, Data& data){
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 1; i < sParcial.sequencia.size() - 1; ++i){
        for(int j = i + 2; j < sParcial.sequencia.size(); ++j){ 
            int vi = sParcial.sequencia[i];
            int vi_next = sParcial.sequencia[i + 1];
            int vj = sParcial.sequencia[j];
            int vj_next = (j + 1 < sParcial.sequencia.size()) ? sParcial.sequencia[j + 1] : sParcial.sequencia[0]; 

            double delta = - data.getDistance(vi, vi_next) 
                           - data.getDistance(vj, vj_next) 
                           + data.getDistance(vi, vj) 
                           + data.getDistance(vi_next, vj_next);

            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestDelta < 0) {
        std::reverse(sParcial.sequencia.begin() + best_i + 1, sParcial.sequencia.begin() + best_j + 1);
        return true; 
    }
    return false; 
}

bool bestImprovementOrOpt(Solution sParcial, int N, Data& data){
    double bestDelta = 0.0;
    int best_i, best_j;
    
    for(int i = 1; i < sParcial.sequencia.size() - 1; ++i){
        int vi = sParcial.sequencia[i];
        int vi_next = sParcial.sequencia[i + 1];
        int vi_prev = sParcial.sequencia[i - 1];
        double delta = 0;
        
        for(int j = i + N; j < sParcial.sequencia.size() - 1; ++j){
            int vj = sParcial.sequencia[j];
            int vj_next = sParcial.sequencia[j + 1];
            int vj_prev = sParcial.sequencia[j - 1];
        

            if(N == 1){
                delta = - data.getDistance(vi, vi_prev) - data.getDistance(vi, vi_next) + data.getDistance(vi_prev, vi_next) 
                            - data.getDistance(vj, vj_next) + data.getDistance(vj, vi) + data.getDistance(vi, vj_next);
            }         
            if(N == 2){
                delta = - data.getDistance(vi_prev, vi) - data.getDistance(vi, vi_next) - data.getDistance(vi_next, sParcial.sequencia[i + 2]) 
                        + data.getDistance(vi_prev, sParcial.sequencia[i + 2]) 
                        - data.getDistance(vj, vj_next) 
                        + data.getDistance(vj, vi) 
                        + data.getDistance(vi, vi_next) 
                        + data.getDistance(vi_next, vj_next);
            }
            if(N == 3){
                delta = 
                    - data.getDistance(vi_prev, vi)
                    - data.getDistance(vi, vi_next)
                    - data.getDistance(vi_next, sParcial.sequencia[i + 2])
                    - data.getDistance(sParcial.sequencia[i + 2], sParcial.sequencia[i + 3])
                    + data.getDistance(vi_prev, sParcial.sequencia[i + 3])
                    - data.getDistance(vj, vj_next)
                    + data.getDistance(vj, vi)
                    + data.getDistance(vi, vi_next)
                    + data.getDistance(vi_next, sParcial.sequencia[i + 2])
                    + data.getDistance(sParcial.sequencia[i + 2], vj_next);
            }

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestDelta < 0) {
        std::reverse(sParcial.sequencia.begin() + best_i + 1, sParcial.sequencia.begin() + best_j + 1);
        return true; 
    }
    return false; 
}


void BuscaLocal(Solution vParcial, Data& data){
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    std::cout << "Iniciando busca local..." << std::endl;
    while (!NL.empty()) {
        int n = rand() % NL.size();

        switch (NL[n]) {
            case 1:
                improved = bestImprovementSwap(vParcial, data);
                break;
            case 2:
                improved = bestImprovement2Opt(vParcial, data);
                break;
            case 3:
                improved = bestImprovementOrOpt(vParcial, 1, data); 
                break;
            case 4:
                improved = bestImprovementOrOpt(vParcial, 2, data); 
                break;
            case 5:
                improved = bestImprovementOrOpt(vParcial, 3, data); 
                break;
        }

        if(improved)
            NL = {1, 2, 3, 4, 5};
        else 
            NL.erase(NL.begin() + n);
    }
    std::cout << "Busca local concluída." << std::endl;
}


