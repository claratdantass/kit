#include "Construcao.h"
#include "Data.h"
using namespace std;

// Seleciona 3 nós aleatórios a partir de um vetor fornecido
std::vector<int> selecionar3NosAleatorios(const std::vector<int>& vetor) {
    std::vector<int> sParcial;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::sample(vetor.begin(), vetor.end(), std::back_inserter(sParcial), 3, gen);
    return sParcial;
}

// Ordena o vetor de custos de inserção em ordem crescente
std::vector<InsertionInfo> ordenarEmOrdemCrescente(std::vector<InsertionInfo>& beta){
    for (int i = 0; i < beta.size() - 1; ++i) {
        for (int j = i + 1; j < beta.size(); ++j) {
            if (beta[i].custo > beta[j].custo)
                std::swap(beta[i], beta[j]);
        }
    }
    return beta;
}

// Calcula os custos de inserção de cada elemento da lista de candidatos (CL) na solução parcial
std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL, Data data){
    std::vector<InsertionInfo> custoInsercao = std::vector<InsertionInfo>((s.sequencia.size() - 1) * CL.size());
    int l = 0;
    for (int a = 0; a < s.sequencia.size() - 1; a++){
        int i = s.sequencia[a];
        int j = s.sequencia[a + 1];
        for (auto k : CL){
            custoInsercao[l].custo = data.getDistance(i, k) + data.getDistance(j, k) - data.getDistance(i, j);
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

    for(int i = 0; i < sParcial.sequencia.size(); ++i){
        novaSequencia.push_back(sParcial.sequencia[i]);
        if(i == arestaRetirada)
            novaSequencia.push_back(noAdicionado);
    }
    return novaSequencia;
}

double calculaValorTotal(Solution& sParcial, Data& data) {
    sParcial.valorObj = 0.0;
    for (int a = 0; a < sParcial.sequencia.size() - 1; ++a) {
        int i = sParcial.sequencia[a];
        int j = sParcial.sequencia[a + 1];
        sParcial.valorObj += data.getDistance(i, j);
    }
    
    if (sParcial.sequencia[0] != sParcial.sequencia[sParcial.sequencia.size() - 1]) {
        sParcial.valorObj += data.getDistance(sParcial.sequencia[0], sParcial.sequencia[sParcial.sequencia.size() - 1]);
    }
    return sParcial.valorObj;
}

Solution Construcao(const int cidades, Data& data) {
    Solution vParcial;
    std::vector<int> CL;
    std::vector<int> s(cidades); 

    for (int i = 1; i <= cidades; ++i) { //criar a lista das cidades 
        s[i - 1] = i;
    }

    vParcial.sequencia = selecionar3NosAleatorios(s); //seleciona 3 nos aleatorios da lista das cidades 
    
    for(int i = 0; i < vParcial.sequencia.size(); ++i){ 
        cout << "Nos: "<< vParcial.sequencia[i] << " ";
    }
    cout << endl;


    for (int i : s) { //forma a lista CL com base nos nós que nao foram selecionados
        if(std::find(vParcial.sequencia.begin(), vParcial.sequencia.end(), i) == vParcial.sequencia.end())
            CL.push_back(i);
    }
    
    for(int i = 0; i < CL.size(); ++i){
        cout << "CL: "<< CL[i] << " ";
    }
    cout << endl;

    while (!CL.empty()) {
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(vParcial, CL, data); //calcula o custo de inserir nos de CL em vParcial
        custoInsercao = ordenarEmOrdemCrescente(custoInsercao);
        
        for(int i = 0; i < custoInsercao.size(); ++i){
            cout << custoInsercao[i].custo << " ";
        }
        cout << endl;
        
        double alpha = (double)rand() / RAND_MAX; 
        int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size())); //pegar um indice dos primeiros colocados de custoInsercao ordenado

        vParcial.sequencia = inserirNaSolucao(vParcial, custoInsercao, selecionado);

        for(int i = 0; i < vParcial.sequencia.size(); ++i){
            cout << vParcial.sequencia[i] << " ";
        }
        cout << endl;
    
        for(int i = 0; i < vParcial.sequencia.size(); ++i) {
            int num = vParcial.sequencia[i]; 
            CL.erase(std::remove(CL.begin(), CL.end(), num), CL.end());
        }
    }

    
    //vParcial.valorObj = calculaValorTotal(vParcial, data);
    //printf("ValorT: %lf", vParcial.valorObj);
    
    return vParcial;

}

