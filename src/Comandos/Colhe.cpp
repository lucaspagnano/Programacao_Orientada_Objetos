#include "../../include/Comandos/Colhe.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Entidades/Jardineiro.h"
// O include Planta.h pode nao ser necessario aqui se a logica esta no Jardineiro
#include <iostream>

Colhe::Colhe(const std::vector<std::string>& args) {
    // O comando colhe aplica-se ONDE o jardineiro esta, por isso nao aceita coordenadas
    if (!args.empty()) {
        std::cout << "Erro: O comando 'colhe' nao aceita argumentos (colhe na posicao atual).\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool Colhe::executa(Simulador& s) {
    if (!this->valido) return false;

    // A logica pesada fica no Jardineiro
    s.getJardineiro()->colherPlanta(*s.getJardim());

    return true;
}