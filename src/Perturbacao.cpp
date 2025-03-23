#include <iostream>
#include <vector>
#include <algorithm>
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

//double bridge
Solution Perturbacao(Solution& best, Data& data){
    Solution sParcial; 
    sParcial = best;
    std::cout << " " << std::endl;
    std::cout << "Iniciando a Perturbacao..." << std::endl;
    std::vector<int> bloco1;
    std::vector<int> bloco2;
    int aleatorio;
    bool clara = false;
    int tam1, tam2;
    int index1, index2;
    int tamanho = sParcial.sequencia.size();

    

    int minT = 2; 
    int maxT = std::ceil((tamanho - 2)/10.0);
    if(maxT == 1)
        maxT = 2;

    std::srand(std::time(0));
    
    while(!clara){
        std::rand();
        index1 = 1 + (rand() % (tamanho - 3));
        index2 = 1 + (rand() % (tamanho - 3));
        
        tam1 = (rand() % (maxT - minT - 1)) + minT;
        tam2 = (rand() % (maxT - minT - 1)) + minT;
    
        if(isValidSwap(index1, tam1, index2, tam2, tamanho)){
            clara = true;
            std::cout << "tam1: " << tam1 << std::endl;
            std::cout << "tam2: " << tam2 << std::endl; 
            std::cout << "index1: " << index1 << std::endl;
            std::cout << "index2: " << index2 << std::endl;
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

    for (int i = 0; i < sParcial.sequencia.size(); i++){
        std::cout << sParcial.sequencia[i] << " ";
    }
    std::cout << std::endl;

    sParcial.valorObj = calculaValorTotal(sParcial, data);

    return sParcial;
}


