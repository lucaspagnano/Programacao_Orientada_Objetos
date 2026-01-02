#include "../../include/Comandos/LPlanta.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Core/Jardim.h"   // Necessario para aceder ao jardim
#include "../../include/Core/Posicao.h"  // Necessario para aceder a posicao
#include "../../include/Entidades/Planta.h" // Necessario para ver os dados da planta
#include <iostream>

LPlanta::LPlanta(const std::vector<std::string>& args) {
    if (args.size() != 1) {
        std::cout << "Erro: Comando 'lplanta' requer 1 argumento (ex: lplanta ej).\n";
        this->valido = false;
        return;
    }

    if (args[0].length() != 2) {
        std::cout << "Erro: Coordenada '" << args[0] << "' invalida. Deve ter 2 letras (ex: ej).\n";
        this->valido = false;
        return;
    }

    this->coord = args[0];
    this->valido = true;
}

bool LPlanta::executa(Simulador& s) {
    if (!this->valido) return false;

    if (!s.isJardimCriado()) {
        std::cout << "Erro: O jardim ainda nao foi criado.\n";
        return false;
    }

    // 1. Converter coordenadas (ex: "aa" -> 0, 0)
    // Assumindo que sao letras minusculas conforme o padrao do projeto
    int l = this->coord[0] - 'a';
    int c = this->coord[1] - 'a';

    Jardim* jardim = s.getJardim();

    // 2. Validar se esta dentro do mapa
    if (!jardim->isPosicaoValida(l, c)) {
        std::cout << "Erro: Coordenada " << this->coord << " fora dos limites do jardim.\n";
        return false;
    }

    // 3. Obter a Planta
    Posicao* p = jardim->getPosicao(l, c);
    Planta* planta = p->getPlanta();

    if (planta == nullptr) {
        std::cout << "Nao existe nenhuma planta na posicao " << this->coord << ".\n";
        return true;
    }

    // 4. Mostrar Relatorio Completo
    std::cout << ">>> Relatorio da Planta em " << this->coord << " <<<\n";
    std::cout << "Especie: " << planta->getBeleza() << " (" << planta->getChar() << ")\n";
    std::cout << "Idade:   " << planta->getInstantesDeVida() << " instantes\n";
    std::cout << "Estado Interno:\n";
    std::cout << "  - Agua Interna: " << planta->getAguaInterna() << "\n";
    std::cout << "  - Nutrientes:   " << planta->getNutrientesInternos() << "\n";
    std::cout << "----------------------------------------\n";

    return true;
}