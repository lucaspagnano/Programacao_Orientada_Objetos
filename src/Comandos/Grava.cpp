#include "../../include/Comandos/Grava.h"
#include "../../include/Core/Simulador.h"
#include <iostream>
Grava::Grava(const std::vector<std::string>& args) {
    if (args.empty()) { std::cout << "Erro: Indique um nome para a gravacao.\n"; valido = false; return; }
    nomeSave = args[0];
    valido = true;
}
bool Grava::executa(Simulador& s) {
    if (!valido) return false;
    s.salvarJogo(nomeSave);
    return true;
}