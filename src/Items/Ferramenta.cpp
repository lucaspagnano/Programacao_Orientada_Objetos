#include "../../include/Items/Ferramenta.h"
#include "../../include/Core/Settings.h"
#include <iostream>

int Ferramenta::proxNumSerie = 1;

Ferramenta::Ferramenta(const std::string& nome)
    : numSerie(proxNumSerie++), nome(nome) {
    
    //std::cout << "DEBUG: Ferramenta '" << this->nome << "' criada com numSerie " << this->numSerie << ".\n";
}

int Ferramenta::getNumSerie() const {
    return numSerie;
}

std::string Ferramenta::getNome() const {
    return nome;
}

