#include "../../include/Comandos/LFerr.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Entidades/Jardineiro.h" // Necessário para aceder ao jardineiro
#include <iostream>

LFerr::LFerr(const std::vector<std::string>& args) {
    // O comando lferr não recebe argumentos
    if (!args.empty()) {
        std::cout << "Erro: Comando 'lferr' nao aceita argumentos.\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool LFerr::executa(Simulador& s) {
    if (!this->valido) return false;

    Jardineiro* jardineiro = s.getJardineiro();

    // Chama a função do Jardineiro que imprime o inventário
    jardineiro->listarFerramentas();

    return true;
}