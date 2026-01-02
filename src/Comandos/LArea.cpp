#include "../../include/Comandos/LArea.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include "../../include/Entidades/Planta.h"
#include "../../include/Entidades/Jardineiro.h"
#include "../../include/Items/Ferramenta.h"
#include <iostream>

LArea::LArea(const std::vector<std::string>& args) {
    if (!args.empty()) {
        std::cout << "Erro: Comando 'larea' nao aceita argumentos.\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool LArea::executa(Simulador& s) {
    if (!this->valido) return false;
    if (!s.isJardimCriado()) {
        std::cout << "Erro: O jardim ainda nao foi criado.\n";
        return false;
    }

    Jardim* j = s.getJardim();
    Jardineiro* jardineiro = s.getJardineiro();

    std::cout << "--- Relatorio da Area (Conteudo Nao-Vazio) ---\n";
    bool encontrouAlgo = false;

    for (int l = 0; l < j->getLinhas(); l++) {
        for (int c = 0; c < j->getColunas(); c++) {

            Posicao* p = j->getPosicao(l, c);
            bool temCoisa = false;
            std::string conteudoStr = "";

            // 1. Verifica Planta
            if (p->getPlanta() != nullptr) {
                conteudoStr += "[Planta: " + p->getPlanta()->getBeleza() + " (" + p->getPlanta()->getChar() + ")] ";
                temCoisa = true;
            }

            // 2. Verifica Ferramenta (se existir no chão - assumindo que getFerramenta devolve algo)
            // Se ainda nao implementaste getFerramenta no Posicao, esta parte fica comentada ou vazia
            /*
            if (p->temFerramenta()) { // Exemplo hipotético
                 conteudoStr += "[Ferramenta] ";
                 temCoisa = true;
            }
            */

            // 3. Verifica Jardineiro
            if (jardineiro->estaNoJardim() && jardineiro->getPosLinha() == l && jardineiro->getPosColuna() == c) {
                conteudoStr += "[JARDINEIRO] ";
                temCoisa = true;
            }

            // Se encontrou alguma coisa nesta célula, imprime
            if (temCoisa) {
                encontrouAlgo = true;
                char coordL = 'A' + l;
                char coordC = 'A' + c;

                std::cout << "Posicao " << coordL << coordC << ": " << conteudoStr << "\n";
                // Mostra também os dados do solo dessa posição
                std::cout << "  -> Solo: Agua=" << p->getAgua() << " | Nutri=" << p->getNutrientes() << "\n";
            }
        }
    }

    if (!encontrouAlgo) {
        std::cout << "O jardim esta completamente vazio de objetos.\n";
    }
    std::cout << "----------------------------------------------\n";

    return true;
}