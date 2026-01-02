#include "../../include/Items/Regador.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Jardim.h"   // <--- Necessário
#include "../../include/Core/Posicao.h"  // <--- Necessário
#include <iostream>

Regador::Regador()
    : Ferramenta("Regador"),
      capacidade(Settings::Regador::capacidade) // 200
{
    std::cout << "DEBUG: Um Regador (S/N " << getNumSerie() << ") foi criado.\n";
}

char Regador::getChar() const {
    return 'g';
}

void Regador::usar(Jardim& j, int l, int c) {
    // 1. Definir quanto gasta (10 unidades)
    int custo = 10;

    // 2. Verificar capacidade
    if (capacidade < custo) {
        std::cout << "O Regador (S/N " << getNumSerie() << ") nao tem agua suficiente!\n";
        return;
    }

    std::cout << "O Regador (S/N " << getNumSerie() << ") esta a ser usado...\n";

    // 3. Obter a posição e aplicar a água
    Posicao* pos = j.getPosicao(l, c);
    if (pos != nullptr) {
        pos->addAgua(custo);       // Aumenta água no solo
        this->capacidade -= custo; // Gasta do regador

        std::cout << "-> Regou a posicao (" << l << "," << c << "). "
                  << "Agua no solo: " << pos->getAgua()
                  << " | Resta no regador: " << capacidade << "\n";
    }
}

bool Regador::deveQuebrar() const {
    // Se tiver menos de 10 unidades, considera-se vazio/partido
    return capacidade < 10;
}