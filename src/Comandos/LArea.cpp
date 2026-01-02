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

    std::cout << "--- Relatorio da Area ---\n";
    bool encontrouAlgo = false;

    for (int l = 0; l < j->getLinhas(); l++) {
        for (int c = 0; c < j->getColunas(); c++) {

            Posicao* p = j->getPosicao(l, c);
            bool temCoisa = false;
            std::string conteudoStr = "";

            if (p->getPlanta() != nullptr) {
                conteudoStr += "[Planta: " + p->getPlanta()->getBeleza() + " (" + p->getPlanta()->getChar() + ")] ";
                temCoisa = true;
            }

            if (p->getFerramenta()) { // Exemplo hipotético
                 conteudoStr += "[Ferramenta] ";
                 temCoisa = true;
            }

            if (jardineiro->estaNoJardim() && jardineiro->getPosLinha() == l && jardineiro->getPosColuna() == c) {
                conteudoStr += "[Jardineiro] ";
                temCoisa = true;
            }

            if (temCoisa) {
                encontrouAlgo = true;
                char coordL = 'A' + l;
                char coordC = 'A' + c;

                std::cout << "Posicao " << coordL << coordC << ": " << conteudoStr << "\n";
                std::cout << "    Solo: Agua=" << p->getAgua() << " | Nutri=" << p->getNutrientes() << "\n";
            }
        }
    }

    if (!encontrouAlgo) {
        std::cout << "O jardim esta completamente vazio de objetos.\n";
    }
    std::cout << "----------------------------------------------\n";

    return true;
}