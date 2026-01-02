#include "../../include/Comandos/Apaga.h"
#include "../../include/Core/Simulador.h"
#include <iostream>

Apaga::Apaga(const std::vector<std::string>& args) {
    if (args.size() != 1) {
        std::cout << "Erro: Indique o nome da copia a apagar (ex: apaga teste).\n";
        this->valido = false;
        return;
    }
    this->nomeCopia = args[0];
    this->valido = true;
}

bool Apaga::executa(Simulador& s) {
    if (!this->valido) return false;
    s.apagarSave(this->nomeCopia);
    return true;
}