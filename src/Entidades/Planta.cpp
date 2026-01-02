#include "../../include/Entidades/Planta.h"
#include <iostream>

// Construtor
Planta::Planta(int agua, int nutrientes, const std::string& beleza)
    : aguaInterna(agua),
      nutrientesInternos(nutrientes),
      beleza(beleza),
      instantesDeVida(0)
{
    std::cout << "DEBUG: Planta base criada.\n";
}

int Planta::getAguaInterna() const {
    return aguaInterna;
}

int Planta::getNutrientesInternos() const {
    return nutrientesInternos;
}

std::string Planta::getBeleza() const {
    return beleza;
}

int Planta::getInstantesDeVida() const {
    return instantesDeVida;
}

void Planta::setAguaInterna(int valor) {
    aguaInterna = valor;
}

void Planta::setNutrientesInternos(int valor) {
    nutrientesInternos = valor;
}

// Nota: O metodo 'agir' e 'getChar' não são implementados aqui
// porque são puramente virtuais (a planta base não sabe como agir).
