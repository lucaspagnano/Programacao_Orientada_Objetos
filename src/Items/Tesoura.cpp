#include "../../include/Items/Tesoura.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include "../../include/Entidades/Planta.h"
#include <iostream>

Tesoura::Tesoura(): Ferramenta("Tesoura de Poda") {
    // Tesoura não tem capacidade, dura para sempre
}

char Tesoura::getChar() const {
    return 't';
}

void Tesoura::usar(Jardim& j, int l, int c) {
    Posicao* p = j.getPosicao(l, c);

    if (p == nullptr) return;

    Planta* planta = p->getPlanta();

    if (planta != nullptr) {
        // Verifica se a planta é "feia"
        // Nota: Certifica-te que na ErvaDaninha.cpp definiste a beleza como "Feia" ou "feia"
        if (planta->getBeleza() == "Feia" || planta->getBeleza() == "feia") {

            // Remove a planta da posição e apaga a memória
            delete p->removePlanta();
            std::cout << "CORTADA! Uma planta feia foi removida da posicao " << l << " " << c << ".\n";

        } else {
            std::cout << "A tesoura so corta plantas feias. Esta (" << planta->getBeleza() << ") foi poupada.\n";
        }
    } else {
        std::cout << "Nao ha planta nenhuma aqui para cortar.\n";
    }
}