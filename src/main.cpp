#include "Data.h"
#include <iostream>
#include <vector>
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"
using namespace std;

double calcularCusto(Data& data, vector<int>& v);

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

        Solution bestOfAll;
        Solution Parcial;
        bestOfAll.valorObj = INFINITY;
        int maxIterIls;
        int maxIter = 50;
    
        if(cidades >= 150){
            maxIterIls = (cidades/2);
        }else{
            maxIterIls = cidades;
        }          
        std::cout << "maxIterIls: " << maxIterIls << std::endl;

        for(int i = 0; i < maxIter; i++){
            Parcial = Construcao(cidades, data, Parcial); 
            cout << "CONSTRUCAO"<< endl;
            for(int i = 0; i < Parcial.sequencia.size() - 1; ++i){
                std::cout << Parcial.sequencia[i] << std::endl;
            }

            Solution best = Parcial;

            int iterIls = 0;

            while(iterIls <= maxIterIls){
                BuscaLocal(Parcial, data);
                
                if(Parcial.valorObj < best.valorObj){
                    std::cout << Parcial.valorObj << std::endl;
                    std::cout << "lalalalalalalala" << std::endl;
                    best = Parcial;
                    iterIls = 0;
                }
                Parcial = Perturbacao(best, data); // tem que ser o melhor
                iterIls = iterIls + 1;
                cout << iterIls << " <= " << maxIterIls << endl;
            }
            if (best.valorObj < bestOfAll.valorObj)
                bestOfAll = best;
        }

        std::cout << "  " <<std::endl;
        std::cout << "bestOffAll: " << std::endl;
        for (int i = 0; i < bestOfAll.sequencia.size(); i++) {
            std::cout << bestOfAll.sequencia[i] << " ";
        }
        std::cout << std::endl;
        std::cout << bestOfAll.valorObj << std::endl;
                       
        return 0;
    }

        
}

