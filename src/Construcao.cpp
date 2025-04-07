#include "Construcao.h"
#include "Data.h"
#include <iostream>
#include <algorithm>
using namespace std;

std::vector<int> selecionar3NosAleatorios(const std::vector<int>& vetor){
    // std::cout << "Iniciando seleção de 3 nós aleatórios com mistura significativa" << std::endl;
    std::vector<int> vetorEmbaralhado = vetor; 
    std::vector<int> sParcial;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(vetorEmbaralhado.begin(), vetorEmbaralhado.end(), gen);
    
    for (int i = 0; i < 3 && i < vetorEmbaralhado.size(); ++i) {
        sParcial.push_back(vetorEmbaralhado[i]);
    }

    // std::cout << "Nós selecionados: ";
    // for (int no : sParcial) std::cout << no << " ";
    // std::cout << std::endl;

    return sParcial;
}


std::vector<InsertionInfo> ordenarEmOrdemCrescente(std::vector<InsertionInfo>& beta) {
    std::sort(beta.begin(), beta.end(), [](const InsertionInfo& a, const InsertionInfo& b) {
        return a.custo < b.custo; 
    });

    return beta; 
}



std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL, Data& data){
    // std::cout << "Iniciando cálculo de custo de inserção" << std::endl;
    std::vector<InsertionInfo> custoInsercao = std::vector<InsertionInfo>((s.sequencia.size() - 1) * CL.size());
    
    int l = 0;
    for(int a = 0; a < s.sequencia.size() - 1; a++){
        int i = s.sequencia[a];
        int j = s.sequencia[a + 1];
        for(auto k : CL){
            custoInsercao[l].custo = data.getDistance(i, k) + data.getDistance(k, j) - data.getDistance(i, j);
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    // std::cout << "Custo de inserção calculado" << std::endl;
    return custoInsercao;
}

std::vector<int> inserirNaSolucao(Solution& sParcial, const std::vector<InsertionInfo>& custoInsercao, int selecionado){
    int noAdicionado = custoInsercao[selecionado].noInserido;
    int arestaRetirada = custoInsercao[selecionado].arestaRemovida;
    std::vector<int> novaSequencia;

    for (int i = 0; i < sParcial.sequencia.size(); ++i){
        novaSequencia.push_back(sParcial.sequencia[i]);
        if (i == arestaRetirada)
            novaSequencia.push_back(noAdicionado);
    }
    return novaSequencia;
}

double calculaValorTotal(Solution& sParcial, Data& data){
    // std::cout << "Calculando valor total da solução" << std::endl;
    sParcial.valorObj = 0.0;
    
    for(int a = 0; a < sParcial.sequencia.size() - 1; ++a){
        int i = sParcial.sequencia[a];
        int j = sParcial.sequencia[a + 1];
        sParcial.valorObj += data.getDistance(i, j);
    }

    if(sParcial.sequencia[0] != sParcial.sequencia[sParcial.sequencia.size() - 1]){
        sParcial.valorObj += data.getDistance(sParcial.sequencia[0], sParcial.sequencia[sParcial.sequencia.size() - 1]);
    }
    
    // std::cout << "Valor total calculado: " << sParcial.valorObj << std::endl;
    return sParcial.valorObj;
}

Solution Construcao(int cidades, Data& data, Solution& vParcial){
    std::vector<int> CL;
    std::vector<int> s; 
    std::vector<int> nS;

    for(int i = 1; i <= cidades; ++i){
        s.push_back(i);
    }

    for(int i = 0; i < s.size(); ++i){
        if(s[i] != 1)
            nS.push_back(s[i]);
    }    

    vParcial.sequencia = selecionar3NosAleatorios(nS);    
    s.push_back(s[0]);

    vParcial.sequencia.insert(vParcial.sequencia.begin(), 1); 
    vParcial.sequencia.push_back(1); 

    // std::cout << "Sequência inicial: ";
    // for (int no : vParcial.sequencia) std::cout << no << " ";
    // std::cout << std::endl;

    for (int i : nS) {
        if(std::find(vParcial.sequencia.begin(), vParcial.sequencia.end(), i) == vParcial.sequencia.end() &&
           std::find(CL.begin(), CL.end(), i) == CL.end()){
            CL.push_back(i);
        }
    }

    // std::cout << "Lista CL: ";
    // for(int no : CL) std::cout << no << " ";
    // std::cout << std::endl;

    while(!CL.empty()){
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(vParcial, CL, data);
        custoInsercao = ordenarEmOrdemCrescente(custoInsercao);
        //std::sort(custoInsercao.begin(), custoInsercao.end());

        double alpha = ((double)rand() / RAND_MAX) * 0.5; 
        int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size()));
        
        // std::cout << "!!!Nó selecionado para inserção:!!! " << custoInsercao[selecionado].noInserido << std::endl;
        vParcial.sequencia = inserirNaSolucao(vParcial, custoInsercao, selecionado);

        for (int no : vParcial.sequencia){
            CL.erase(std::remove(CL.begin(), CL.end(), no), CL.end());
        }
    }  
    
    vParcial.valorObj = calculaValorTotal(vParcial, data); 
    // std::cout << "Solução final construída" << std::endl;
    
    return vParcial;
}
