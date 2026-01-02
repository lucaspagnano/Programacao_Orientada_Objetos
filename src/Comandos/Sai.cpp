#include "../../include/Comandos/Sai.h"
#include "../../include/Core/Simulador.h"
#include <iostream>

Sai::Sai(const std::vector<std::string>& args) {
    // CORREÇÃO: 'sai' não tem argumentos, por isso o vetor deve estar vazio
    if (!args.empty()) {
        std::cout << "Erro: Comando 'sai' nao aceita argumentos.\n";
        this->valido = false;
        return;
    }
    this->valido = true;
}

bool Sai::executa(Simulador& s) {
    if (!this->valido) return false;

    Jardineiro* jardineiro = s.getJardineiro();

    if (!jardineiro->estaNoJardim()) {
        std::cout << "Erro: O jardineiro nao esta no jardim.\n";
        return false;
    }

    if (!jardineiro->podeEntrarSair()) {
        std::cout << "Erro: O jardineiro ja esgotou as entradas/saidas deste turno.\n";
        return false;
    }

    jardineiro->sai();

    return true;
}