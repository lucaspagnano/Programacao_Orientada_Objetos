#include "../../include/Comandos/LPlantas.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include "../../include/Entidades/Planta.h"
#include <iostream>

LPlantas::LPlantas(const std::vector<std::string>& args) {
    if (!args.empty()) {
        std::cout << "Erro: Comando 'lplantas' nao aceita argumentos.\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool LPlantas::executa(Simulador& s) {
    if (!this->valido) return false;

    if (!s.isJardimCriado()) {
        std::cout << "Erro: O jardim ainda nao foi criado.\n";
        return false;
    }

    Jardim* j = s.getJardim();
    std::cout << "--- Relatorio Geral de Plantas ---\n";

    bool encontrou = false;
    // Percorre todas as linhas e colunas
    for (int l = 0; l < j->getLinhas(); l++) {
        for (int c = 0; c < j->getColunas(); c++) {
            Posicao* p = j->getPosicao(l, c);
            Planta* planta = p->getPlanta();

            if (planta != nullptr) {
                encontrou = true;
                // Converte indices para letras (0->A, 1->B...) para ficar bonito
                char coordL = 'A' + l;
                char coordC = 'A' + c;

                std::cout << "[" << coordL << coordC << "] "
                          << planta->getBeleza() << " (" << planta->getChar() << ") "
                          << "| Idade: " << planta->getInstantesDeVida()
                          << " | Saude: " << planta->getNutrientesInternos() << "\n";
            }
        }
    }

    if (!encontrou) {
        std::cout << "O jardim nao tem plantas vivas de momento.\n";
    }
    std::cout << "----------------------------------\n";

    return true;
}