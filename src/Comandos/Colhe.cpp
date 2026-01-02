#include "../../include/Comandos/Colhe.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Entidades/Jardineiro.h"
#include <iostream>

Colhe::Colhe(const std::vector<std::string>& args) {
    if (!args.empty()) {
        std::cout << "Erro: O comando 'colhe' nao aceita argumentos (colhe na posicao atual).\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool Colhe::executa(Simulador& s) {
    if (!this->valido) return false;
    s.getJardineiro()->colherPlanta(*s.getJardim());
    return true;
}