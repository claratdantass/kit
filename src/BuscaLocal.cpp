#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"
#include "BuscaLocal.h"

bool bestImprovementSwap(Solution& sParcial, Data& data){
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 1; i < sParcial.sequencia.size() - 1; i++){
        int vi = sParcial.sequencia[i];
        int vi_next = sParcial.sequencia[i + 1];
        int vi_prev = sParcial.sequencia[i - 1];

        for(int j = i + 1; j < sParcial.sequencia.size() - 1; j++){
            //if(j == i+1) continue;
            // como o i e o j são adj algumas arestas se sobrepõem antes e depois da troca  
            if (j == i + 1){
                int vi_prev = sParcial.sequencia[i - 1];
                int vi      = sParcial.sequencia[i];
                int vj      = sParcial.sequencia[j];
                int vj_next = sParcial.sequencia[j + 1];

                double delta = 
                    -data.getDistance(vi_prev, vi)
                    -data.getDistance(vi, vj)
                    -data.getDistance(vj, vj_next)
                    +data.getDistance(vi_prev, vj)
                    +data.getDistance(vj, vi)
                    +data.getDistance(vi, vj_next);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }else{
                int vj = sParcial.sequencia[j];
                int vj_next = sParcial.sequencia[j + 1];
                int vj_prev = sParcial.sequencia[j - 1];

                double delta = - data.getDistance(vi_prev, vi) - data.getDistance(vi, vi_next) + data.getDistance(vi_prev, vj)
                                + data.getDistance(vj, vi_next) - data.getDistance(vj_prev, vj) - data.getDistance(vj, vj_next)
                                + data.getDistance(vj_prev, vi) + data.getDistance(vi, vj_next);
                    
                std::cout << "delta:" << delta << std::endl;

                    if(delta < bestDelta){
                        bestDelta = delta;
                        best_i = i;
                        best_j = j;
                    }    
                }
            }
    }
    if(bestDelta < 0){
        std::cout << "bestDelta: "<< bestDelta << std::endl;
        std::swap(sParcial.sequencia[best_i], sParcial.sequencia[best_j]);
        
        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << "." << std::endl;

        sParcial.valorObj = sParcial.valorObj + bestDelta;
        return true;
    }
    return false;
}

bool bestImprovement2Opt(Solution& sParcial, Data& data){
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

bool bestImprovementOrOpt(Solution& sParcial, int N, Data& data){
    double bestDelta = 0; 
    int best_i, best_j, best_w, best_k;
    double delta = 0;

    for (int i = 1; i < sParcial.sequencia.size() - 1; ++i){
        int vi = sParcial.sequencia[i];
        int vi_next = sParcial.sequencia[i + 1];
        int vi_prev = sParcial.sequencia[i - 1];
        for(int j = i + N; j < sParcial.sequencia.size() - 1; ++j){
            int vj = sParcial.sequencia[j];
            int vj_next = sParcial.sequencia[j + 1];
            int vj_prev = sParcial.sequencia[j - 1];

            if(N == 1){
                delta = - data.getDistance(vi, vi_prev) - data.getDistance(vi, vi_next) 
                        + data.getDistance(vi_prev, vi_next) 
                        - data.getDistance(vj, vj_next) 
                        + data.getDistance(vj, vi) 
                        + data.getDistance(vi, vj_next);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
            else if (N == 2){
                delta = - data.getDistance(vi_prev, vi) - data.getDistance(vi, vi_next) 
                        - data.getDistance(vi_next, sParcial.sequencia[i + 2]) 
                        + data.getDistance(vi_prev, sParcial.sequencia[i + 2]) 
                        - data.getDistance(vj, vj_next) 
                        + data.getDistance(vj, vi) 
                        + data.getDistance(vi, vi_next) 
                        + data.getDistance(vi_next, vj_next);

                if (delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_w = i + 1;
                    best_j = j;
                }
            }
            else if (N == 3){
                delta = - data.getDistance(vi_prev, vi) - data.getDistance(vi, vi_next) 
                        - data.getDistance(vi_next, sParcial.sequencia[i + 2]) 
                        - data.getDistance(sParcial.sequencia[i + 2], sParcial.sequencia[i + 3])
                        + data.getDistance(vi_prev, sParcial.sequencia[i + 3]) 
                        - data.getDistance(vj, vj_next) 
                        + data.getDistance(vj, vi) 
                        + data.getDistance(vi, vi_next) 
                        + data.getDistance(vi_next, sParcial.sequencia[i + 2]) 
                        + data.getDistance(sParcial.sequencia[i + 2], vj_next);

                if (delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_w = i + 1;
                    best_k = i + 2;
                    best_j = j;
                }
            }

            if (bestDelta < 0){
                if (N == 1){
                    auto it_i = std::next(sParcial.sequencia.begin(), best_i);
                    auto it_j = std::next(sParcial.sequencia.begin(), best_j);

                    auto temp_i = *it_i;

                    sParcial.sequencia.erase(it_i);

                    if (it_j + 1 == sParcial.sequencia.end()) {
                        it_j = sParcial.sequencia.end() - 2;
                    }
                    sParcial.sequencia.insert(it_j + 1, temp_i);
                }
                else if (N == 2){
                    auto it_i = std::next(sParcial.sequencia.begin(), best_i);
                    auto it_w = std::next(sParcial.sequencia.begin(), best_w);
                    auto it_j = std::next(sParcial.sequencia.begin(), best_j);

                    auto temp_i = *it_i;
                    auto temp_w = *it_w;

                    sParcial.sequencia.erase(it_i);
                    sParcial.sequencia.erase(it_i);

                    if (it_j + 1 >= sParcial.sequencia.end() - 1){
                        it_j = sParcial.sequencia.end() - 2;
                    }
                    sParcial.sequencia.insert(it_j + 1, temp_i);
                    sParcial.sequencia.insert(it_j + 2, temp_w);
                }
                else if (N == 3) {
                    auto it_i = std::next(sParcial.sequencia.begin(), best_i);
                    auto it_w = std::next(sParcial.sequencia.begin(), best_w);
                    auto it_k = std::next(sParcial.sequencia.begin(), best_k);
                    auto it_j = std::next(sParcial.sequencia.begin(), best_j);

                    auto temp_i = *it_i;
                    auto temp_w = *it_w;
                    auto temp_k = *it_k;

                    sParcial.sequencia.erase(it_i);
                    sParcial.sequencia.erase(it_i);
                    sParcial.sequencia.erase(it_i);

                    if (it_j + 1 >= sParcial.sequencia.end() - 1) {
                        it_j = sParcial.sequencia.end() - 2;
                    }

                    sParcial.sequencia.insert(it_j + 1, temp_i);
                    sParcial.sequencia.insert(it_j + 2, temp_w);
                    sParcial.sequencia.insert(it_j + 3, temp_k);

                }

                sParcial.valorObj += bestDelta;

                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;
                return true;
            }
        }
    }
    return false;
}



void BuscaLocal(Solution& sParcial, Data& data){
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    std::cout << "Iniciando busca local..." << std::endl;
    while (!NL.empty()) {
        int n = rand() % NL.size();

        switch (NL[n]){
            case 1:
                std::cout << "Swap" << std::endl;
                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << "antes" << std::endl;

                improved = bestImprovementSwap(sParcial, data);

                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << "depois" << std::endl;
                break;
            case 2:
                improved = bestImprovement2Opt(sParcial, data);
                break;
            case 3:
                std::cout << "N = 1" << std::endl;
                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << "antes" << std::endl;

                improved = bestImprovementOrOpt(sParcial, 1, data);

                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << "depois" << std::endl;
                break;
            case 4:
                std::cout << "N = 2" << std::endl;
                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << "antes" << std::endl;

                improved = bestImprovementOrOpt(sParcial, 2, data);

                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << "depois" << std::endl;
               break;
            case 5: 
                std::cout << "N = 3" << std::endl;
                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << "antes" << std::endl;

                improved = bestImprovementOrOpt(sParcial, 3, data);

                for (int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << "depois" << std::endl;
                break;
        }

        if(improved){
            NL = {1, 2, 3, 4, 5};
            std::cout << "melhorou" << std::endl;
        }else{  
            NL.erase(NL.begin() + n);
            std::cout << "piorou" << std::endl;
            for (int i = 0; i < sParcial.sequencia.size(); i++) {
                std::cout << sParcial.sequencia[i] << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "Busca local concluída." << std::endl;
}

