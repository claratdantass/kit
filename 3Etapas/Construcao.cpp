#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

typedef struct Solution {
    std::vector<int> sequencia;
    double valorObj;
} Solution;

std::vector<int> selecionarAleatorios(const std::vector<int>& vetor, int quantidade) {
    std::vector<int> sParcial;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::sample(vetor.begin(), vetor.end(), std::back_inserter(sParcial), quantidade, gen);

    return sParcial;
}

double calcularCustoObj(Solution s, const std::vector<std::vector<double>> matrizAdj) {
    s.valorObj = 0.0;

    for (int a = 0; a < s.sequencia.size() - 1; ++a) {
        int i = s.sequencia[a];
        int j = s.sequencia[a + 1];
        s.valorObj += matrizAdj[i][j];
    }
    // fiquei com duvida se esse if era realmente necessário, mas ele seria funcional para checar se o trajeto esta começando e terminando no mesmo ponto
    if (s.sequencia.back() != s.sequencia.front()) {
        s.valorObj += matrizAdj[s.sequencia.back()][s.sequencia.front()];
    }

    return s.valorObj;
}

Solution Construcao(const Solution& s, const std::vector<std::vector<double>> matrizAdj){
    std::vector<int> CL;
    std::vector<int> vParcial;
    double cParcial;
    std::vector<std::pair<int, std::pair<int, int>>> alpha; //dúvida: o item de cl sera alocado em um lugar aleatorio de vParcial? ou onde tiver o melhor custo

    int quantidade = static_cast<size_t>(std::ceil(s.sequencia.size() * 0.4));
    // pensei que começar com cerca de 40% a 50% dos vertices seria um bom inicio para numeros menores, poderia mudar para 20% dependendo do tamanho
    
    vParcial = selecionarAleatorios(s.sequencia, quantidade);
    //vetorParcial.valorObj = calcularCustoObj(vetorPacial.sequencia, matrizAdj);

    for (int i : s.sequencia){
        bool encontrado = false;
        
        for (int j : vParcial){
            if (i == j) {
                encontrado = true;
                break; 
            }
        }
        if (!encontrado) 
            CL.push_back(i); 
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    //double custoAtual = s.valorObj;

    while (!CL.empty()) {
        std::uniform_int_distribution<> dist(0, CL.size() - 1);
        int randomIndexCL = dist(gen); // a funcao dist faz com que todos os numeros tenham a mesma chance de serem escolhidos
        int escolhidoCL = CL[randomIndexCL]; // gera um indice aleatorio
        
        CL.erase(CL.begin() + randomIndexCL); // retira o elemento alocado no indice determinado de CL

        
        std::uniform_int_distribution<> distInsert(0, vParcial.size()); // o mesmo uso da implementacao anterior
        int randomPosition = distInsert(gen); //gera uma posicao aleatoria para o numero previamente escolhido ser inserido
        
        vParcial.insert(vParcial.begin() + randomPosition, escolhidoCL); 


        int antecessor; // encontrando o par que se conecta com o numero novo
        if (randomPosition == 0) 
            antecessor = vParcial[vParcial.size() - 1];
         else 
            antecessor = vParcial[randomPosition - 1];
        
        int sucessor;
        if (randomPosition == vParcial.size() - 1) 
            sucessor = vParcial[0]; 
        else 
            sucessor = vParcial[randomPosition + 1];
  

        alpha.push_back({escolhidoCL, {antecessor, sucessor}});
        }
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
    Solution s;
    s.sequencia = {1, 2, 3, 4, 5, 6}; // Todos os vértices
    s.valorObj = 0;

    //auto alpha = Construcao(s, matrizAdj);

    /*std::cout << "Pares gerados em alpha:" << std::endl;
    for (const auto& par : alpha) {
        int k = par.first;
        int i = par.second.first;
        int j = par.second.second;
        std::cout << "k: " << k << ", i: " << i << ", j: " << j << std::endl;
    }

*/
   printf("Oi\n");

    return 0;
}
