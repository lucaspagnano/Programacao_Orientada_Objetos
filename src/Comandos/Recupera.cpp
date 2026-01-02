#include "../../include/Comandos/Recupera.h"
#include "../../include/Core/Simulador.h"
#include <iostream>

Recupera::Recupera(const std::vector<std::string>& args) {
    if (args.empty()) { std::cout << "Erro: Indique o nome da gravacao a recuperar.\n"; valido = false; return; }
    nomeSave = args[0];
    valido = true;
}

bool Recupera::executa(Simulador& s) {
    if (!valido) return false;
    s.recuperarJogo(nomeSave);
    return true;
}