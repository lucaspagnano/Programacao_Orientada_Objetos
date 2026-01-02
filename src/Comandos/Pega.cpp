#include "../../include/Comandos/Pega.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Entidades/Jardineiro.h"
#include <iostream>
#include <vector>
#include <string>

// Inicializa 'numSerie' em vez de 'idFerramenta'
Pega::Pega(const std::vector<std::string>& args) : numSerie(-1) {
    if (args.size() != 1) {
        std::cout << "Erro: Sintaxe 'pega <id>' (ex: pega 1).\n";
        this->valido = false;
        return;
    }

    try {
        // Guarda o valor na variável que já tinhas no header
        this->numSerie = std::stoi(args[0]);
        this->valido = true;
    } catch (...) {
        std::cout << "Erro: O ID da ferramenta tem de ser um numero.\n";
        this->valido = false;
    }
}

bool Pega::executa(Simulador& s) {
    if (!this->valido) return false;

    // Usa 'numSerie' para chamar a função do jardineiro
    s.getJardineiro()->pegaFerramenta(this->numSerie);

    return true;
}