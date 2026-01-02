#include "../../include/Comandos/Entra.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Core/Jardim.h"
#include <iostream>

Entra::Entra(const std::vector<std::string>& args) {
    // CORREÇÃO: O vetor args contém apenas os argumentos, não o nome do comando.
    // Para 'entra aa', o tamanho deve ser 1.
    if (args.size() != 1) {
        std::cout << "Erro: Sintaxe 'entra <coordenada>' (ex: entra aa).\n";
        this->valido = false;
        return;
    }

    // CORREÇÃO: Acedemos ao índice 0 (o primeiro argumento)
    if (args[0].length() != 2) {
        std::cout << "Erro: Coordenada invalida (deve ter 2 letras).\n";
        this->valido = false;
        return;
    }

    this->coord = args[0]; // Guardamos a coordenada correta
    this->valido = true;
}

bool Entra::executa(Simulador& s) {
    if (!this->valido) return false;

    if (!s.isJardimCriado()) {
        std::cout << "Erro: O jardim ainda nao foi criado.\n";
        return false;
    }

    int l = this->coord[0] - 'a';
    int c = this->coord[1] - 'a';

    if (!s.getJardim()->isPosicaoValida(l, c)) {
        std::cout << "Erro: Coordenada '" << this->coord << "' fora dos limites!\n";
        return false;
    }

    if (!s.getJardineiro()->podeEntrarSair()) {
        std::cout << "Erro: O jardineiro ja esgotou as entradas/saidas deste turno.\n";
        return false;
    }

    s.getJardineiro()->entra(l, c);

    return true;
}