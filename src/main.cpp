#include "Data.h"
#include <iostream>
#include <vector>
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"
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

const int maxIter = 50;     

int main(int argc, char *argv[]) {
    if(argc < 2){
        std::cout << "Passe caminho para a instancia" << std::endl;
        exit(0);
    }
    {
        auto data = Data(argc, argv[1]);  // Cria o objeto
        data.read();

        const int cidades = data.getDimension();
        std::cout << cidades << std::endl;

        Solution Parcial;
        Solution bestOfAll;
        bestOfAll.valorObj = 0;
        int maxIterIls;

        Parcial = Construcao(cidades, data, Parcial);
        for(int i = 0; i < Parcial.sequencia.size() ; ++i){
             std::cout << Parcial.sequencia[i] << " ";
        }
        std::cout << std::endl;

        BuscaLocal(Parcial, data);

            /*
        for(int i = 0; i < maxIter; i++){
            Parcial = Construcao(cidades, data, Parcial);
            for(int i = 0; i < Parcial.sequencia.size() - 1; ++i){
                std::cout << Parcial.sequencia[i] << std::endl;
            }

            Solution best = Parcial;

            int iterIls = 0;

            int tamanho = Parcial.sequencia.size();

            std::cout << "tamanho: " << tamanho << std::endl;
                
            if(tamanho >= 150){
                maxIterIls = (tamanho/2);
            }else{
                maxIterIls = tamanho;
            }          
            std::cout << "maxIterIls: " << maxIterIls << std::endl;

            while(iterIls <= maxIterIls){
                BuscaLocal(Parcial, data);
                
                if(Parcial.valorObj < best.valorObj){
                    best = Parcial;
                    iterIls = 0;
            }
                Parcial = Perturbacao(Parcial, data);
                iterIls++;
            }
            if (best.valorObj < bestOfAll.valorObj)
                bestOfAll = best;
            
            */
        }

        /*
        std::cout << "Melhor valor objetivo: " << bestOfAll.valorObj << std::endl;
        for(int i = 0; i < bestOfAll.sequencia.size() - 1; ++i){
            std::cout << bestOfAll.sequencia[i] << std::endl;
        }
        
        */        
        return 0;
    }


