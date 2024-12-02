#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

typedef struct Solution {
    std::vector<int> sequencia;
    double valorObj;
} Solution;

typedef struct InsertionInfo
{
    int noInserido; // nó k a ser inserido
    int arestaRemovida; // aresta {i,j} na qual o nó k será inserido
    double custo; // delta ao inserir k na aresta {i,j}
} InsertionInfo;

std::vector<int> selecionar3NosAleatorios(const std::vector<int>& vetor){
    std::vector<int> sParcial;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::sample(vetor.begin(), vetor.end(), std::back_inserter(sParcial), 3, gen);

    return sParcial;
}

std::vector<InsertionInfo> ordenarEmOrdemCrescente(std::vector<InsertionInfo>& beta) {
    for (int i = 0; i < beta.size() - 1; ++i) {
        for (int j = i + 1; j < beta.size(); ++j) {
            if (beta[i].custo > beta[j].custo)
                std::swap(beta[i], beta[j]);
        }
    }
    
    return beta;
}

std::vector<InsertionInfo> calcularCustoInsercao(Solution& m, std::vector<int>& CL, const std::vector<std::vector<double>>& matrizAdj){

    std::vector<InsertionInfo> custoInsercao = std::vector<InsertionInfo>(
        (m.sequencia.size() - 1) * CL.size());
    int l = 0;
    for (int a = 0; a < m.sequencia.size() - 1; a++) {
        int i = m.sequencia[a];
        int j = m.sequencia[a + 1];
        for (auto k : CL) {
            custoInsercao[l].custo = matrizAdj[i][k] + matrizAdj[j][k] - matrizAdj[i][j];
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    return custoInsercao;
}

std::vector<int> inserirNaSolucao(Solution& sParcial, const std::vector<InsertionInfo>& custoInsercao, int selecionado) {
    int noAdicionado = custoInsercao[selecionado].noInserido;
    int arestaRetirada = custoInsercao[selecionado].arestaRemovida;

    std::vector<int> novaSequencia;

    for (int i = 0; i < sParcial.sequencia.size(); ++i) {
        novaSequencia.push_back(sParcial.sequencia[i]);
        if (i == arestaRetirada) {
            novaSequencia.push_back(noAdicionado);
        }
    }

    return novaSequencia;
}

double calculaValorTotal(Solution& sParcial, const std::vector<std::vector<double>>& matrizAdj){
    sParcial.valorObj = 0.0;
    
    for (int a = 0; a < sParcial.sequencia.size() - 1; ++a) {
        int i = sParcial.sequencia[a];
        int j = sParcial.sequencia[a + 1];
        sParcial.valorObj += matrizAdj[i][j];
    }
    // fiquei com duvida se esse if era realmente necessário, mas ele seria funcional para checar se o trajeto esta começando e terminando no mesmo ponto
    if (sParcial.sequencia[0] != sParcial.sequencia[sParcial.sequencia.size() - 1]) {
        sParcial.valorObj += matrizAdj[sParcial.sequencia[0]][sParcial.sequencia[sParcial.sequencia.size() - 1]];
    }

    return sParcial.valorObj;
}

Solution Construcao(const Solution& s, const std::vector<std::vector<double>> matrizAdj){
    Solution vParcial;
    std::vector<int> CL;
    
    vParcial.sequencia = selecionar3NosAleatorios(s.sequencia);
    
    for(int i : s.sequencia){
        bool encontrado = false;
        
        for(int j : vParcial.sequencia){
            if (i == j) {
                encontrado = true;
                break; 
            }
        }
        if (!encontrado) 
            CL.push_back(i); 
    }

    while (!CL.empty()) {
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(vParcial, CL, matrizAdj);
        
        std::vector<InsertionInfo> omega = ordenarEmOrdemCrescente(custoInsercao);
        
        double alpha = (double)rand() / RAND_MAX; 
        int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size())); 
        
        vParcial.sequencia = inserirNaSolucao(vParcial, custoInsercao, selecionado);
        vParcial.valorObj = calculaValorTotal(vParcial, matrizAdj);
}

return vParcial;
}



int main() {
    // Matriz de adjacência
    std::vector<std::vector<double>> matrizAdj = {
        {0, 245, 174, 118, 59, 129},
        {245, 0, 250, 226, 186, 147},
        {174, 250, 0, 274, 169, 114},
        {118, 226, 274, 0, 105, 185},
        {59, 186, 169, 105, 0, 85},
        {129, 147, 114, 185, 85, 0}
    };
}
