#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"
#include "BuscaLocal.h"


bool funcaoAuxiliar(Solution& sParcial, Data& data, int valorAntes, int bestDelta){
    int valorDepois;
    int diferenca;

    valorDepois = calculaValorTotal(sParcial, data); 
    diferenca = valorDepois - valorAntes;
    std::cout << diferenca <<std::endl;
    
    return (diferenca == bestDelta);
}

bool bestImprovementSwap(Solution& sParcial, Data& data){
    double bestDelta = 0;
    int best_i, best_j;
    int valorAntes;

    for(int i = 1; i < sParcial.sequencia.size() - 1; i++){
        int vi = sParcial.sequencia[i];
        int vi_next = sParcial.sequencia[i + 1];
        int vi_prev = sParcial.sequencia[i - 1];

        for(int j = i + 1; j < sParcial.sequencia.size() - 1; j++){
            // como o i e o j são adj algumas arestas se sobrepõem antes e depois da troca  
            if (j == i + 1){
                int vi_prev = sParcial.sequencia[i - 1];
                int vi = sParcial.sequencia[i];
                int vj = sParcial.sequencia[j];
                int vj_next = sParcial.sequencia[j + 1];

                double delta = 
                    - data.getDistance(vi_prev, vi)
                    - data.getDistance(vj, vj_next)
                    + data.getDistance(vi_prev, vj)
                    + data.getDistance(vi, vj_next);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }else{
                int vj = sParcial.sequencia[j];
                int vj_next = sParcial.sequencia[j + 1];
                int vj_prev = sParcial.sequencia[j - 1];

                double delta = - data.getDistance(vi_prev, vi) 
                               - data.getDistance(vi, vi_next) 
                               - data.getDistance(vj_prev, vj) 
                               - data.getDistance(vj, vj_next)
                               + data.getDistance(vi_prev, vj)
                               + data.getDistance(vj, vi_next) 
                               + data.getDistance(vj_prev, vi) 
                               + data.getDistance(vi, vj_next);
                    
                    if(delta < bestDelta){
                        bestDelta = delta;
                        best_i = i;
                        best_j = j;
                    }    
                }
            }
    }
    if(bestDelta < 0){
        /*
        std::cout << "bestDelta: " << bestDelta << std::endl;

        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        valorAntes = calculaValorTotal(sParcial, data);
        /*
        std::cout << "best_i:" << sParcial.sequencia[best_i] << std::endl;
        std::cout << "best_j:" << sParcial.sequencia[best_j] << std::endl;
        */
        std::swap(sParcial.sequencia[best_i], sParcial.sequencia[best_j]);
        /*
        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        // bool vouf;
        // vouf = funcaoAuxiliar(sParcial, data, valorAntes, bestDelta);
        
        // if(vouf)
        // std::cout << "Iguais" << std::endl;
        // else
        // std::cout << "Diferentes" << std::endl;

        sParcial.valorObj += bestDelta;
        //std::cout << sParcial.valorObj << std::endl;

        return true;
    }
    return false;
}


// toda errada!!!!!!
bool bestImprovement2Opt(Solution& sParcial, Data& data){
    double bestDelta = 0;
    int best_i, best_j;
    int valorAntes;

    for(int i = 1; i < sParcial.sequencia.size() - 1; ++i){
        int vi = sParcial.sequencia[i];
        int vi_prev = sParcial.sequencia[i - 1];
        int vi_next = sParcial.sequencia[i + 1];

        for(int j = i + 2; j < sParcial.sequencia.size() - 1; ++j){ 
            int vj = sParcial.sequencia[j];
            int vj_prev = sParcial.sequencia[j - 1];
            int vj_next = sParcial.sequencia[j + 1]; 

            double delta = - data.getDistance(vi, vi_prev)
                            - data.getDistance(vj, vj_next)
                            + data.getDistance(vj, vi_prev)
                            + data.getDistance(vi, vj_next); 

            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestDelta < 0) {
        /*
        std::cout << "bestDelta: " << bestDelta << std::endl;

        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        valorAntes = calculaValorTotal(sParcial, data);
        /*
        std::cout << "best_i:" << sParcial.sequencia[best_i] << std::endl;
        std::cout << "best_j:" << sParcial.sequencia[best_j] << std::endl;
        */
        //std::swap(sParcial.sequencia[best_i + 1], sParcial.sequencia[best_j]);
        std::reverse(sParcial.sequencia.begin() + best_i, sParcial.sequencia.begin() + best_j + 1); 
        /*
        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        // bool vouf;
        // vouf = funcaoAuxiliar(sParcial, data, valorAntes, bestDelta);
        
        // if(vouf)
        // std::cout << "Iguais" << std::endl;
        // else
        // std::cout << "Diferentes" << std::endl;

        sParcial.valorObj += bestDelta;
        //std::cout << sParcial.valorObj << std::endl;

        return true;
    }
    return false; 
}

bool bestImprovementN1(Solution& sParcial, Data& data) {
    double bestDelta = 0, delta = 0;
    int best_i, best_j;
    int valorAntes;
    
    for (int i = 1; i < sParcial.sequencia.size() - 1; ++i) {
        int vi = sParcial.sequencia[i];
        int vi_next = sParcial.sequencia[i + 1];
        int vi_prev = sParcial.sequencia[i - 1];
        
        for (int j = i + 1; j < sParcial.sequencia.size() - 1; ++j) {
            int vj = sParcial.sequencia[j];
            int vj_next = sParcial.sequencia[j + 1];
            
            delta = - data.getDistance(vi, vi_prev) 
                    - data.getDistance(vi, vi_next) 
                    - data.getDistance(vj, vj_next) 
                    + data.getDistance(vi_prev, vi_next) 
                    + data.getDistance(vj, vi) 
                    + data.getDistance(vi, vj_next);

            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }
    
    if (bestDelta < 0) {
        /*
        std::cout << "bestDelta: " << bestDelta << std::endl;

        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        valorAntes = calculaValorTotal(sParcial, data);
        /*
        std::cout << "best_i:" << sParcial.sequencia[best_i] << std::endl;
        std::cout << "best_j:" << sParcial.sequencia[best_j] << std::endl;
        */
        int temp_i = sParcial.sequencia[best_i]; 
        sParcial.sequencia.erase(sParcial.sequencia.begin() + best_i);
        
        if(best_j > best_i){
            best_j -= 1;
        }
        sParcial.sequencia.insert(sParcial.sequencia.begin() + best_j + 1, temp_i);
        /*
        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        // bool vouf;
        // vouf = funcaoAuxiliar(sParcial, data, valorAntes, bestDelta);
        
        // if(vouf)
        // std::cout << "Iguais" << std::endl;
        // else
        // std::cout << "Diferentes" << std::endl;


        sParcial.valorObj += bestDelta;
        //std::cout << sParcial.valorObj << std::endl;

        return true;
    }
    return false;
}

bool bestImprovementN2(Solution& sParcial, Data& data) {
    double bestDelta = 0, delta = 0;
    int best_i, best_j, best_w;
    int valorAntes;
    
    for (int i = 1; i < sParcial.sequencia.size() - 1; ++i) {
        int vi = sParcial.sequencia[i];
        int vi_next = sParcial.sequencia[i + 1];
        int vi_prev = sParcial.sequencia[i - 1];
        
        for (int j = i + 2; j < sParcial.sequencia.size() - 1; ++j) {
            int vj = sParcial.sequencia[j];
            int vj_next = sParcial.sequencia[j + 1];
            
            delta = - data.getDistance(vi_prev, vi) 
                        - data.getDistance(vi_next, sParcial.sequencia[i + 2])
                        - data.getDistance(vj, vj_next)  
                        + data.getDistance(vi_prev, sParcial.sequencia[i + 2]) 
                        + data.getDistance(vj, vi) 
                        + data.getDistance(vi_next, vj_next);

            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_w = i + 1;
                best_j = j;
            
            }
        }
    }
    
    if (bestDelta < 0) {
        /*
        std::cout << "bestDelta: " << bestDelta << std::endl;

        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        valorAntes = calculaValorTotal(sParcial, data);
        /*
        std::cout << "best_i:" << sParcial.sequencia[best_i] << std::endl;
        std::cout << "best_w:" << sParcial.sequencia[best_w] << std::endl;
        std::cout << "best_j:" << sParcial.sequencia[best_j] << std::endl;
        */
        int temp_i = sParcial.sequencia[best_i]; 
        int temp_w = sParcial.sequencia[best_w];

        // Remove os elementos antes de inseri-los na nova posição
        sParcial.sequencia.erase(sParcial.sequencia.begin() + best_w);
        sParcial.sequencia.erase(sParcial.sequencia.begin() + best_i);
            
        if(best_j > best_i){
            best_j -= 2;
        }
                    
        sParcial.sequencia.insert(sParcial.sequencia.begin() + best_j + 1, temp_i);
        sParcial.sequencia.insert(sParcial.sequencia.begin() + best_j + 2, temp_w);
        /*
        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        // bool vouf;
        // vouf = funcaoAuxiliar(sParcial, data, valorAntes, bestDelta);
        
        // if(vouf)
        // std::cout << "Iguais" << std::endl;
        // else
        // std::cout << "Diferentes" << std::endl;

        sParcial.valorObj += bestDelta;
        //std::cout << sParcial.valorObj << std::endl;

        return true;
    }
    return false;
}


bool bestImprovementN3(Solution& sParcial, Data& data) {
    double bestDelta = 0, delta = 0;
    int best_i, best_j, best_w, best_k;
    int valorAntes;

    for (int i = 1; i < sParcial.sequencia.size() - 1; ++i) {
        int vi = sParcial.sequencia[i];
        int vi_next = sParcial.sequencia[i + 1];
        int vi_prev = sParcial.sequencia[i - 1];
        
        for (int j = i + 3; j < sParcial.sequencia.size() - 1; ++j) {
            int vj = sParcial.sequencia[j];
            int vj_next = sParcial.sequencia[j + 1];
            
            delta = - data.getDistance(vi_prev, vi)   
                        - data.getDistance(sParcial.sequencia[i + 2], sParcial.sequencia[i + 3])
                        - data.getDistance(vj, vj_next) 
                        + data.getDistance(vi_prev, sParcial.sequencia[i + 3])
                        + data.getDistance(vj, vi)  
                        + data.getDistance(sParcial.sequencia[i + 2], vj_next);

            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_w = i + 1;
                best_k = i + 2;
                best_j = j;
            }
        }
    }
    
    if(bestDelta < 0) {
        /*
        std::cout << "bestDelta: " << bestDelta << std::endl;

        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        valorAntes = calculaValorTotal(sParcial, data);
        /*
        std::cout << "best_i:" << sParcial.sequencia[best_i] << std::endl;
        std::cout << "best_w:" << sParcial.sequencia[best_w] << std::endl;
        std::cout << "best_k:" << sParcial.sequencia[best_k] << std::endl;
        std::cout << "best_j:" << sParcial.sequencia[best_j] << std::endl;
        */
        int temp_i = sParcial.sequencia[best_i]; 
        int temp_w = sParcial.sequencia[best_w];
        int temp_k = sParcial.sequencia[best_k];

        sParcial.sequencia.erase(sParcial.sequencia.begin() + best_k);
        sParcial.sequencia.erase(sParcial.sequencia.begin() + best_w);
        sParcial.sequencia.erase(sParcial.sequencia.begin() + best_i);
                
        if(best_j > best_i)
            best_j -= 3;

        sParcial.sequencia.insert(sParcial.sequencia.begin() + best_j + 1, temp_i);
        sParcial.sequencia.insert(sParcial.sequencia.begin() + best_j + 2, temp_w);
        sParcial.sequencia.insert(sParcial.sequencia.begin() + best_j + 3, temp_k);
        /*
        for (int i = 0; i < sParcial.sequencia.size(); i++) {
            std::cout << sParcial.sequencia[i] << " ";
        }
        std::cout << std::endl;
        */
        // bool vouf;
        // vouf = funcaoAuxiliar(sParcial, data, valorAntes, bestDelta);
        
        // if(vouf)
        // std::cout << "Iguais" << std::endl;
        // else
        // std::cout << "Diferentes" << std::endl;

        sParcial.valorObj += bestDelta;
        //std::cout << sParcial.valorObj << std::endl;
        
        return true;
    }
    return false;
}

void BuscaLocal(Solution& sParcial, Data& data){
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;
    
    sParcial.valorObj = calculaValorTotal(sParcial, data);

    while(!NL.empty()){
        int n = rand() % NL.size();

        switch (NL[n]){
            case 1:
                //std::cout << " " << std::endl;
                //std::cout << "Swap" << std::endl;
                improved = bestImprovementSwap(sParcial, data);
                break;
            case 2:
                //std::cout << " " << std::endl;
                //std::cout << "2Opt" << std::endl;
                improved = bestImprovement2Opt(sParcial, data);
                break;
            case 3:
                //std::cout << " " << std::endl;
                //std::cout << "N = 1" << std::endl;
                improved = bestImprovementN1(sParcial, data);
                break;
            case 4:
                //std::cout << " " << std::endl;
                //std::cout << "N = 2" << std::endl;
                improved = bestImprovementN2(sParcial, data);
                break;
            case 5:
                //std::cout << " " << std::endl; 
                //std::cout << "N = 3" << std::endl;
                improved = bestImprovementN3(sParcial, data);
                break;
        }

        if(improved){
            NL = {1, 2, 3, 4, 5};     
        } else {  
            NL.erase(NL.begin() + n);
            /*
            for (int i = 0; i < sParcial.sequencia.size(); i++) {
                std::cout << sParcial.sequencia[i] << " ";
            }
            std::cout << std::endl;
            */
        }
    }
}
