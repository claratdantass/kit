#include "Data.h"
#include <iostream>
#include <vector>
#include "Construcao.h"

using namespace std;

double calcularCusto(Data& data, vector<int>& v);

void exibirSolucao(Solution *s)
{
 for(int i = 0; i < s->sequencia.size() - 1; i++)
 std::cout << s->sequencia[i] << " -> ";
 std::cout << s->sequencia.back() << std::endl;
}

//Comando para executar o codigo: ./tsp instances/"nome_da_instancia".tsp
//ex: ./tsp instances/teste.tsp

int main(int argc, char *argv[]) {

    if(argc < 2){
        cout << "Passe caminho para a instancia" << endl;
        exit(0);
    }
    
    auto data = Data(argc, argv[1]);
    data.read();


    const int cidades = data.getDimension();
    cout << cidades << endl;
    
    Solution Parcial;
    Parcial = Construcao(cidades, data);

    for (int i : Parcial.sequencia){
    std::cout << i << " ";
    }

    std::cout << "Oi" << std::endl;

}


