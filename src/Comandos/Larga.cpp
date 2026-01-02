#include "../../include/Comandos/Larga.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Entidades/Jardineiro.h"
#include <iostream>

Larga::Larga(const std::vector<std::string>& args) {
    if (!args.empty()) {
        std::cout << "Erro: O comando 'larga' nao aceita argumentos.\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool Larga::executa(Simulador& s) {
    if (!this->valido)
        return false;
    s.getJardineiro()->largaFerramenta();
    return true;
}