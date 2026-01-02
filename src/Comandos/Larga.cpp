#include "../../include/Comandos/Larga.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Entidades/Jardineiro.h"
#include <iostream>

Larga::Larga(const std::vector<std::string>& args) {
    // O comando 'larga' não aceita argumentos
    if (!args.empty()) {
        std::cout << "Erro: O comando 'larga' nao aceita argumentos.\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool Larga::executa(Simulador& s) {
    if (!this->valido) return false;

    // Chama a função do Jardineiro
    s.getJardineiro()->largaFerramenta();

    return true;
}