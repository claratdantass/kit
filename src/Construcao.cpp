#include "Construcao.h"
#include "Data.h"
#include <iostream>
using namespace std;

std::vector<int> selecionar3NosAleatorios(const std::vector<int>& vetor) {
    std::cout << "Iniciando seleção de 3 nós aleatórios" << std::endl;
    std::vector<int> sParcial;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::sample(vetor.begin(), vetor.end(), std::back_inserter(sParcial), 3, gen);

    std::cout << "Nós selecionados: ";
    for (int no : sParcial) std::cout << no << " ";
    std::cout << std::endl;

    return sParcial;
}

std::vector<InsertionInfo> ordenarEmOrdemCrescente(std::vector<InsertionInfo>& beta) {
    std::cout << "Iniciando ordenação de custos de inserção" << std::endl;
    
    for(int i = 0; i < beta.size() - 1; ++i){
        for(int j = i + 1; j < beta.size(); ++j){
            if (beta[i].custo > beta[j].custo)
                std::swap(beta[i], beta[j]);
        }
    }
    
    std::cout << "Custos ordenados: ";
    for (const auto& info : beta) std::cout << info.custo << " ";
    std::cout << std::endl;
    return beta;
}

std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL, Data data){
    std::cout << "Iniciando cálculo de custo de inserção" << std::endl;
    std::vector<InsertionInfo> custoInsercao = std::vector<InsertionInfo>((s.sequencia.size() - 1) * CL.size());
    
    int l = 0;
    for(int a = 0; a < s.sequencia.size() - 1; a++){
        int i = s.sequencia[a];
        int j = s.sequencia[a + 1];
        for (auto k : CL) {
            custoInsercao[l].custo = data.getDistance(i, k) + data.getDistance(j, k) - data.getDistance(i, j);
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }

    std::cout << "Custo de inserção calculado" << std::endl;
    return custoInsercao;
    
}

std::vector<int> inserirNaSolucao(Solution& sParcial, const std::vector<InsertionInfo>& custoInsercao, int selecionado){
    std::cout << "Inserindo nó na solução" << std::endl;
    int noAdicionado = custoInsercao[selecionado].noInserido;
    int arestaRetirada = custoInsercao[selecionado].arestaRemovida;
    std::vector<int> novaSequencia;

    for (int i = 0; i < sParcial.sequencia.size(); ++i){
        novaSequencia.push_back(sParcial.sequencia[i]);
        if (i == arestaRetirada)
            novaSequencia.push_back(noAdicionado);
    }

    std::cout << "Nova sequência após inserção: ";
    for (int no : novaSequencia) std::cout << no << " ";
    std::cout << std::endl;

    return novaSequencia;
}

double calculaValorTotal(Solution& sParcial, Data& data) {
    std::cout << "Calculando valor total da solução" << std::endl;
    sParcial.valorObj = 0.0;
    
    for(int a = 0; a < sParcial.sequencia.size() - 1; ++a){
        int i = sParcial.sequencia[a];
        int j = sParcial.sequencia[a + 1];
        sParcial.valorObj += data.getDistance(i, j);
    }

    if(sParcial.sequencia[0] != sParcial.sequencia[sParcial.sequencia.size() - 1]){
        sParcial.valorObj += data.getDistance(sParcial.sequencia[0], sParcial.sequencia[sParcial.sequencia.size() - 1]);
    }
    
    std::cout << "Valor total calculado: " << sParcial.valorObj << std::endl;
    return sParcial.valorObj;
}

Solution Construcao(const int cidades, Data& data){
    std::cout << "Iniciando construção da solução" << std::endl;
    Solution vParcial;
    std::vector<int> CL;
    std::vector<int> s; 

    for(int i = 1; i <= cidades; ++i) {
        s.push_back(i);
    }
    
    vParcial.sequencia = selecionar3NosAleatorios(s);    
    
    s.push_back(s[0]);
    
    std::cout << "Cidades: ";
    for(int ciclo : s) std::cout << ciclo << " ";
    std::cout << std::endl;

    std::cout << "Sequência inicial: ";
    for (int no : vParcial.sequencia) std::cout << no << " ";
    std::cout << std::endl;

    for (int i : s) {
    if (std::find(vParcial.sequencia.begin(), vParcial.sequencia.end(), i) == vParcial.sequencia.end() &&
        std::find(CL.begin(), CL.end(), i) == CL.end()) 
    {
        CL.push_back(i);
    }
}

    std::cout << "Lista CL inicial: ";
    for(int no : CL) std::cout << no << " ";
    std::cout << std::endl;

    while(!CL.empty()){
        std::cout << "Iniciando nova iteração do loop!!!!!" << std::endl;
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(vParcial, CL, data);
        custoInsercao = ordenarEmOrdemCrescente(custoInsercao);

        double alpha = (double)rand() / RAND_MAX; 
        int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size()));
        std::cout << "Nó selecionado para inserção: " << custoInsercao[selecionado].noInserido << std::endl;

        vParcial.sequencia = inserirNaSolucao(vParcial, custoInsercao, selecionado);

        std::cout << "Sequência após inserção: ";
        for (int no : vParcial.sequencia) std::cout << no << " ";
        std::cout << std::endl;

        for (int no : vParcial.sequencia){
            CL.erase(std::remove(CL.begin(), CL.end(), no), CL.end());
        }

        std::cout << "Lista CL após remoção de nós: ";
        for (int no : CL) std::cout << no << " ";
        std::cout << std::endl;
    }

    std::cout << "Solução final construída" << std::endl;
    return vParcial;
}
