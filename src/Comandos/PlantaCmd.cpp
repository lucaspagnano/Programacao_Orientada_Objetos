#include "../../include/Comandos/PlantaCmd.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include "../../include/Entidades/Planta.h"
#include "../../include/Entidades/Jardineiro.h"
#include "../../include/Entidades/Roseira.h"
#include "../../include/Entidades/Cacto.h"
#include "../../include/Entidades/ErvaDaninha.h"
// #include "../../include/Entidades/Plantas/PlantaExotica.h" // Se tiveres
#include <iostream>

PlantaCmd::PlantaCmd(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        std::cout << "Erro: Comando 'planta' requer 2 argumentos (ex: planta fb c).\n";
        this->valido = false;
        return;
    }
    // Validacoes de tamanho
    if (args[0].length() != 2 || args[1].length() != 1) {
        this->valido = false; return;
    }

    this->coord = args[0];
    this->tipoPlanta = args[1][0];

    // Validar tipo
    if (tipoPlanta != 'c' && tipoPlanta != 'r' && tipoPlanta != 'e' && tipoPlanta != 'x') {
        std::cout << "Erro: Tipo invalido. Use (c, r, e, x).\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool PlantaCmd::executa(Simulador& s) {
    if (!this->valido) return false;
    if (!s.isJardimCriado()) { std::cout << "Jardim nao existe.\n"; return false; }

    Jardineiro* jardineiro = s.getJardineiro();

    // 1. Verifica Quota de Plantacao
    if (!jardineiro->podePlantar()) {
        std::cout << "Ja atingiste o limite de plantacoes por turno (Max: 2). Avanca o tempo.\n";
        return false;
    }

    // 2. Converte e Valida Coordenadas
    int l = this->coord[0] - 'a';
    int c = this->coord[1] - 'a';
    Jardim* j = s.getJardim();

    if (!j->isPosicaoValida(l, c)) {
        std::cout << "Coordenada fora do jardim.\n";
        return false;
    }

    Posicao* p = j->getPosicao(l, c);

    // 3. Verifica se ja tem planta
    if (p->getPlanta() != nullptr) {
        std::cout << "Ja existe uma planta nessa posicao!\n";
        return false;
    }

    // 4. Cria a Planta
    Planta* novaPlanta = nullptr;
    switch (this->tipoPlanta) {
        case 'r': novaPlanta = new Roseira(); break;
        case 'c': novaPlanta = new Cacto(); break;
        case 'e': novaPlanta = new ErvaDaninha(); break;
        // case 'x': novaPlanta = new PlantaExotica(); break;
        default: std::cout << "Erro interno.\n"; return false;
    }

    // 5. Coloca no Solo e Desconta Quota
    p->setPlanta(novaPlanta);
    jardineiro->registarPlantacao();

    std::cout << "Plantaste uma " << novaPlanta->getBeleza() << " (" << tipoPlanta << ") em " << this->coord << ".\n";
    return true;
}