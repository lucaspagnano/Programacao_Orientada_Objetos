#include "../../include/Comandos/LFerr.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Entidades/Jardineiro.h"
#include <iostream>

LFerr::LFerr(const std::vector<std::string>& args) {
    if (!args.empty()) {
        std::cout << "Erro: Comando 'lferr' nao aceita argumentos.\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool LFerr::executa(Simulador& s) {
    if (!this->valido)
        return false;
    Jardineiro* jardineiro = s.getJardineiro();
    jardineiro->listarFerramentas();
    return true;
}