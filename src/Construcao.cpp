#include "Construcao.h"
#include "Data.h"

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
    
    /*
    std::sort(beta.begin(), beta.end(), [](const InsertionInfo& a, const InsertionInfo& b) {
    return a.custo < b.custo;
    */
   return beta;
}

std::vector<InsertionInfo> calcularCustoInsercao(Solution& m, std::vector<int>& CL, Data data){

    std::vector<InsertionInfo> custoInsercao = std::vector<InsertionInfo>(
        (m.sequencia.size() - 1) * CL.size());
    int l = 0;
    for (int a = 0; a < m.sequencia.size() - 1; a++) {
        int i = m.sequencia[a];
        int j = m.sequencia[a + 1];
        for (auto k : CL) {
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

    for (int i = 0; i < sParcial.sequencia.size(); ++i) {
        novaSequencia.push_back(sParcial.sequencia[i]);
        if (i == arestaRetirada) {
            novaSequencia.push_back(noAdicionado);
        }
    }

    /*
    std::vector<int> novaSequencia = sParcial.sequencia;
    novaSequencia.insert(novaSequencia.begin() + arestaRetirada + 1, noAdicionado);
    
    return novaSequencia;

    */    

    return novaSequencia;
}

double calculaValorTotal(Solution& sParcial, Data &data){
    sParcial.valorObj = 0.0;
    
    for (int a = 0; a < sParcial.sequencia.size() - 1; ++a) {
        int i = sParcial.sequencia[a];
        int j = sParcial.sequencia[a + 1];
        sParcial.valorObj += data.getDistance(i, j);
    }
    // fiquei com duvida se esse if era realmente necessário, mas ele seria funcional para checar se o trajeto esta começando e terminando no mesmo ponto
    if (sParcial.sequencia[0] != sParcial.sequencia[sParcial.sequencia.size() - 1]) {
        sParcial.valorObj += data.getDistance(sParcial.sequencia[0], sParcial.sequencia[sParcial.sequencia.size() - 1]);
    }

    return sParcial.valorObj;
}

Solution Construcao(const int cidades,Data &data){ // era tipo solution
    Solution vParcial;
    std::vector<int> CL;
    std::vector<int> s(cidades); 
    
    for(int i = 0; i < cidades; i++){
        s[i] = i;
    } 

    vParcial.sequencia = selecionar3NosAleatorios(s);

    for(int i = 0; i < vParcial.sequencia.size(); i++){
        cout << vParcial.sequencia[i] << " ";
    }
    cout << endl;

    for(int i : s){
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
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(vParcial, CL, data);
        
        std::vector<InsertionInfo> omega = ordenarEmOrdemCrescente(custoInsercao);
        double alpha = (double)rand() / RAND_MAX; 
        int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size())); 
        
        vParcial.sequencia = inserirNaSolucao(vParcial, custoInsercao, selecionado);
        vParcial.valorObj = calculaValorTotal(vParcial, data);
    }

    return vParcial;
}
