#ifndef PROJETO_POO_JARDIM_H
#define PROJETO_POO_JARDIM_H

#include "Posicao.h"

class Jardineiro;

class Jardim {
    int linhas;
    int colunas;

    Posicao** grelha;

public:
    Jardim(int l, int c);
    ~Jardim();

    Jardim(const Jardim &origem);

    int getLinhas() const;
    int getColunas() const;
    Posicao* getPosicao(int l, int c) const;
    bool isPosicaoValida(int l, int c) const;
    void desenha(const Jardineiro& jardineiro) const;
    void atualizarPlantas();
    Posicao* getVizinhoLivreAleatorio(int l, int c);
};

#endif //PROJETO_POO_JARDIM_H