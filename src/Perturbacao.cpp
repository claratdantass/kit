#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Data.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"

bool isValidSwap(int index1, int tam1, int index2, int tam2, int tamanho){
    if (index1 <= 0 || index2 <= 0 || index1 + tam1 >= tamanho || index2 + tam2 >= tamanho)
        return false; 
    
    return (index1 + tam1 <= index2 || index2 + tam2 <= index1);
}

// double bridge
Solution Perturbacao(Solution& best, Data& data){
    Solution sParcial; 
    sParcial = best;
    std::vector<int> bloco1;
    std::vector<int> bloco2;
    bool clara = false;
    int tam1, tam2;
    int index1, index2;
    int tamanho = sParcial.sequencia.size();
    
    int minT = 2; 
    int maxT = std::ceil((tamanho - 2) / 10.0); 
    //std::cout << "maxT: " << maxT << std::endl;
    if (maxT == 1)
        maxT = 2;
    
    //std::cout << "maxT: " << maxT << std::endl;

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(1, tamanho - 3); 
    
    std::uniform_int_distribution<> distribTam(minT, maxT);

    while(!clara){
        index1 = distrib(gen);
        index2 = distrib(gen);
        
        tam1 = distribTam(gen);
        tam2 = distribTam(gen);
    
        if (isValidSwap(index1, tam1, index2, tam2, tamanho)){
            clara = true;
            //std::cout << "tam1: " << tam1 << std::endl;
            //std::cout << "tam2: " << tam2 << std::endl; 
            //std::cout << sParcial.sequencia[index1] << std::endl;
            //std::cout << sParcial.sequencia[index2] << std::endl;
        }   
    }

    if (index1 > index2) {
        std::swap(index1, index2);
        std::swap(tam1, tam2);
    }

    bloco1.assign(sParcial.sequencia.begin() + index1, sParcial.sequencia.begin() + index1 + tam1);
    bloco2.assign(sParcial.sequencia.begin() + index2, sParcial.sequencia.begin() + index2 + tam2);
    
    
    sParcial.sequencia.erase(sParcial.sequencia.begin() + index2, sParcial.sequencia.begin() + index2 + tam2);
    sParcial.sequencia.erase(sParcial.sequencia.begin() + index1, sParcial.sequencia.begin() + index1 + tam1);
    sParcial.sequencia.insert(sParcial.sequencia.begin() + index1, bloco2.begin(), bloco2.end());
    sParcial.sequencia.insert(sParcial.sequencia.begin() + index2 - tam1 + tam2, bloco1.begin(), bloco1.end());

    sParcial.valorObj = calculaValorTotal(sParcial, data);

    return sParcial;
}



