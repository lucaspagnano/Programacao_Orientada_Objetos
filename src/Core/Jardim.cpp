#include "../../include/Core/Jardim.h"
#include "../../include/Entidades/Jardineiro.h"
#include "../../include/Items/Regador.h"
#include "../../include/Items/Adubo.h"
#include "../../include/Items/Tesoura.h"
#include "../../include/Entidades/Roseira.h"
#include "../../include/Entidades/Cacto.h"
#include "../../include/Entidades/ErvaDaninha.h"
#include <vector>
#include <iostream>
#include <cstdlib>

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    grelha = new Posicao*[linhas]; // cria array de ponteiros
    for (int i = 0; i < linhas; i++) {
        grelha[i] = new Posicao[colunas]; // para cada linha vertical cria um array horizontal de objetos Posicao
    }

    //colocar 3 ferramentas aleatorias
    int ferrColocadas = 0;
    while (ferrColocadas < 3) {
        int rL = rand() % linhas; // gera uma linha aleatoria sem passar de linhas
        int rC = rand() % colunas; // gera uma coluna aleatoria sem passar de colunas
        Posicao* p = &grelha[rL][rC]; // obtem endereço da célula sorteada

        if (p->getFerramenta() == nullptr) {
            int sorteio = rand() % 3; // sorteia qual ferramenta vai criar
            if (sorteio == 0) p->setFerramenta(new Regador());
            else if (sorteio == 1) p->setFerramenta(new Adubo());
            else p->setFerramenta(new Tesoura());
            ferrColocadas++; // incrementa contador de ferramentas colocadas
        }
    }

    int numPlantas = (linhas * colunas) / 5; // 20% do mapa sao plantas 
    int plantasColocadas = 0;

    while (plantasColocadas < numPlantas) {
        int rL = rand() % linhas;
        int rC = rand() % colunas;
        Posicao* p = &grelha[rL][rC];

        if (p->getPlanta() == nullptr) {
            int sorteio = rand() % 3;
            if (sorteio == 0) p->setPlanta(new Roseira());
            else if (sorteio == 1) p->setPlanta(new Cacto());
            else p->setPlanta(new ErvaDaninha());

            plantasColocadas++;
        }
    }
}

Jardim::~Jardim() {
    for (int i = 0; i < linhas; i++) delete[] grelha[i]; // apaga linhas (arrays de coluna)
    delete[] grelha; // apaga array de ponteiros principal 
}

void Jardim::atualizarPlantas() {
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            Planta* p = grelha[l][c].getPlanta(); // utilizamos metodo para verificar se existe planta na posicao 
            if (p != nullptr) {
                p->agir(*this, l, c); // se existir, mandamos planta agir
            }
        }
    }
}

Posicao* Jardim::getVizinhoLivreAleatorio(int l, int c) {
    std::vector<Posicao*> livres; // cria ponteiro para guardar vizinhos possiveis

    for (int dl = -1; dl <= 1; dl++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dl == 0 && dc == 0) continue;

            // calcula coordenadas do vizinho
            int vizL = l + dl;
            int vizC = c + dc;

            if (isPosicaoValida(vizL, vizC)) { //  verifica se a posicao e valida pelo metodo 
                Posicao* p = getPosicao(vizL, vizC); // pega a posicao
                if (p->getPlanta() == nullptr) {
                    livres.push_back(p); // se nao houver planta guarda posicao no vetor 
                }
            }
        }
    }

    if (livres.empty()) return nullptr; // se n houver vizinhos candiatos return 

    int sorteio = rand() % livres.size(); // sorteia um indice do vetor de vizinhos 
    return livres[sorteio]; //retorna o vizinho sorteado
}

int Jardim::getLinhas() const { return linhas; }
int Jardim::getColunas() const { return colunas; }
bool Jardim::isPosicaoValida(int l, int c) const { return (l >= 0 && l < linhas && c >= 0 && c < colunas); } // return true se for valida 
Posicao* Jardim::getPosicao(int l, int c) const { if (!isPosicaoValida(l, c)) return nullptr; return &grelha[l][c]; } // forma de obter uma celula do tabuleiro

void Jardim::desenha(const Jardineiro& jardineiro) const {
    // desenha cabecalho das colunas
    std::cout << "  ";
    for (int c = 0; c < colunas; ++c) std::cout << (char)('A' + c);
    std::cout << "\n";

    // desenha linhas 
    for (int l = 0; l < linhas; ++l) {
        std::cout << (char)('A' + l) << " "; // cabecalho da linha
        for (int c = 0; c < colunas; ++c) {
            if (jardineiro.estaNoJardim() && jardineiro.getPosLinha() == l && jardineiro.getPosColuna() == c) { // verifica se o jardineiro esta na celula q vamos desenhar 
                std::cout << "*";
            } else {
                Posicao* pos = &grelha[l][c];
                std::cout << pos->getCharVisivel(false); // pede a classe posicao para desenhar o que deve estar na celula 
            }
        }
        std::cout << "\n";
    }
}

Jardim::Jardim(const Jardim &origem) : linhas(origem.linhas), colunas(origem.colunas) {
    grelha = new Posicao*[linhas]; // cria array onde cada elemento vai guardar o endereco de uma linha horizontal
    for (int i = 0; i < linhas; i++) {
        grelha[i] = new Posicao[colunas]; // aloca array horizontal de objetos Posicao
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            grelha[i][j].setAgua(origem.grelha[i][j].getAgua());
            grelha[i][j].setNutrientes(origem.grelha[i][j].getNutrientes());

            if (origem.grelha[i][j].getPlanta() != nullptr) {
                grelha[i][j].setPlanta(origem.grelha[i][j].getPlanta()->clone());
            }

            if (origem.grelha[i][j].getFerramenta() != nullptr) {
                grelha[i][j].setFerramenta(origem.grelha[i][j].getFerramenta()->clone());
            }
        }
    }
    std::cout << "Jogo gravado (Copia do Jardim criada).\\n";
}
