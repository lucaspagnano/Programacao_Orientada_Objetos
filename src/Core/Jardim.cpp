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
    grelha = new Posicao*[linhas];
    for (int i = 0; i < linhas; i++) {
        grelha[i] = new Posicao[colunas];
    }

    int ferrColocadas = 0;
    while (ferrColocadas < 3) {
        int rL = rand() % linhas;
        int rC = rand() % colunas;
        Posicao* p = &grelha[rL][rC];

        if (p->getFerramenta() == nullptr) {
            int sorteio = rand() % 3;
            if (sorteio == 0) p->setFerramenta(new Regador());
            else if (sorteio == 1) p->setFerramenta(new Adubo());
            else p->setFerramenta(new Tesoura());
            ferrColocadas++;
        }
    }

    int numPlantas = (linhas * colunas) / 5;
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
    for (int i = 0; i < linhas; i++) delete[] grelha[i];
    delete[] grelha;
}

void Jardim::atualizarPlantas() {
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            Planta* p = grelha[l][c].getPlanta();
            if (p != nullptr) {
                p->agir(*this, l, c);
            }
        }
    }
}

Posicao* Jardim::getVizinhoLivreAleatorio(int l, int c) {
    std::vector<Posicao*> livres;

    for (int dl = -1; dl <= 1; dl++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dl == 0 && dc == 0) continue;

            int vizL = l + dl;
            int vizC = c + dc;

            if (isPosicaoValida(vizL, vizC)) {
                Posicao* p = getPosicao(vizL, vizC);
                if (p->getPlanta() == nullptr) {
                    livres.push_back(p);
                }
            }
        }
    }

    if (livres.empty()) return nullptr;

    int sorteio = rand() % livres.size();
    return livres[sorteio];
}

int Jardim::getLinhas() const { return linhas; }
int Jardim::getColunas() const { return colunas; }
bool Jardim::isPosicaoValida(int l, int c) const { return (l >= 0 && l < linhas && c >= 0 && c < colunas); }
Posicao* Jardim::getPosicao(int l, int c) const { if (!isPosicaoValida(l, c)) return nullptr; return &grelha[l][c]; }

void Jardim::desenha(const Jardineiro& jardineiro) const {
    std::cout << "  ";
    for (int c = 0; c < colunas; ++c) std::cout << (char)('A' + c);
    std::cout << "\n";
    for (int l = 0; l < linhas; ++l) {
        std::cout << (char)('A' + l) << " ";
        for (int c = 0; c < colunas; ++c) {
            if (jardineiro.estaNoJardim() && jardineiro.getPosLinha() == l && jardineiro.getPosColuna() == c) {
                std::cout << "*";
            } else {
                Posicao* pos = &grelha[l][c];
                std::cout << pos->getCharVisivel(false);
            }
        }
        std::cout << "\n";
    }
}

Jardim::Jardim(const Jardim &origem) : linhas(origem.linhas), colunas(origem.colunas) {
    grelha = new Posicao*[linhas];
    for (int i = 0; i < linhas; i++) {
        grelha[i] = new Posicao[colunas];
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