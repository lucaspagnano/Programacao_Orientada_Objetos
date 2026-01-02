#include "../../include/Items/Regador.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include <iostream>

Regador::Regador()
    : Ferramenta("Regador"),
      capacidade(Settings::Regador::capacidade)
{
    //std::cout << "DEBUG: Um Regador (S/N " << getNumSerie() << ") foi criado.\n";
}

char Regador::getChar() const {
    return 'g';
}

void Regador::usar(Jardim& j, int l, int c) {
    int custo = 10;
    if (capacidade < custo) {
        std::cout << "O Regador (ID: " << getNumSerie() << ") nao tem agua suficiente.\n";
        return;
    }

    //std::cout << "O Regador (ID: " << getNumSerie() << ") esta a ser usado\n";

    Posicao* pos = j.getPosicao(l, c);
    if (pos != nullptr) {
        pos->addAgua(custo);
        this->capacidade -= custo;

        std::cout << "Regou a posicao (" << l << "," << c << "). "
                  << "Agua no solo: " << pos->getAgua()
                  << " | Resta no regador: " << capacidade << "\n";
    }
}

bool Regador::deveQuebrar() const {
    return capacidade < 10;
}