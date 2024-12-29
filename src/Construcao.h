#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"

struct Solution {
    std::vector<int> sequencia;
    double valorObj;
};

struct InsertionInfo {
    int noInserido;       // Nó a ser inserido
    int arestaRemovida;   // Aresta {i, j} na qual o nó será inserido
    double custo;         // Delta ao inserir o nó na aresta
};

std::vector<int> selecionar3NosAleatorios(const std::vector<int>& vetor);

std::vector<InsertionInfo> ordenarEmOrdemCrescente(std::vector<InsertionInfo>& beta);

std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL, Data& data);

std::vector<int> inserirNaSolucao(Solution& sParcial, const std::vector<InsertionInfo>& custoInsercao, int selecionado);

double calculaValorTotal(Solution& sParcial, Data& data);

Solution Construcao(int cidades, Data& data, Solution& Parcial);

#endif 

