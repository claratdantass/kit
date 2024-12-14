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

typedef struct InsertionInfo{
    int noInserido; // nó k a ser inserido
    int arestaRemovida; // aresta {i,j} na qual o nó k será inserido
    double custo; // delta ao inserir k na aresta {i,j}
} InsertionInfo;

std::vector<int> selecionar3NosAleatorios(const std::vector<int>& vetor);

std::vector<InsertionInfo> ordenarEmOrdemCrescente(std::vector<InsertionInfo>& beta);

std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL, Data data);

std::vector<int> inserirNaSolucao(Solution& sParcial, const std::vector<InsertionInfo>& custoInsercao, int selecionado);

double calculaValorTotal(Solution& sParcial, Data &data);

Solution Construcao(const int cidades,Data &data);
