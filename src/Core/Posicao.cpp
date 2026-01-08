#include "../../include/Core/Posicao.h"
#include "../../include/Core/Settings.h"
#include "../../include/Entidades/Planta.h"
#include "../../include/Items/Ferramenta.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Posicao::Posicao() {
    planta = nullptr;
    ferramenta = nullptr;

    int minAgua = Settings::Jardim::agua_min;
    int maxAgua = Settings::Jardim::agua_max;
    int minNutri = Settings::Jardim::nutrientes_min;
    int maxNutri = Settings::Jardim::nutrientes_max;

    agua = rand() % (maxAgua - minAgua + 1) + minAgua; // gera um valor entre 0 e a diferenca de min e max e dps adiciona o min 
    nutrientes = rand() % (maxNutri - minNutri + 1) + minNutri; // gera um valor entre 0 e a diferenca de min e max e dps adiciona o min 
}

Posicao::~Posicao() {
    if (planta != nullptr) delete planta;
    if (ferramenta != nullptr) delete ferramenta;
}

int Posicao::getAgua() const { return agua; }
int Posicao::getNutrientes() const { return nutrientes; }
Planta* Posicao::getPlanta() const { return planta; }
Ferramenta* Posicao::getFerramenta() const { return ferramenta; }

void Posicao::setAgua(int valor) { agua = (valor < 0) ? 0 : valor; }
void Posicao::setNutrientes(int valor) { nutrientes = (valor < 0) ? 0 : valor; }

void Posicao::addAgua(int valor) {
    this->agua += valor;
    if (this->agua < 0) this->agua = 0;
}

void Posicao::addNutrientes(int valor) {
    this->nutrientes += valor;
    if (this->nutrientes < 0) this->nutrientes = 0;
}

int Posicao::retiraAgua(int qtd) {
    int disponivel = this->agua;
    int aRetirar = std::min(disponivel, qtd);
    this->agua -= aRetirar;
    return aRetirar;
}

int Posicao::retiraNutrientes(int qtd) {
    int disponivel = this->nutrientes;
    int aRetirar = std::min(disponivel, qtd);
    this->nutrientes -= aRetirar;
    return aRetirar;
}

void Posicao::setPlanta(Planta* p) {
    if (planta != nullptr) delete planta;
    planta = p;
}

void Posicao::setFerramenta(Ferramenta* f) {
    if (ferramenta != nullptr) delete ferramenta;
    ferramenta = f;
}

Planta* Posicao::removePlanta() {
    Planta* p = planta;
    planta = nullptr;
    return p;
}

Ferramenta* Posicao::removeFerramenta() {
    Ferramenta* f = ferramenta;
    ferramenta = nullptr;
    return f;
}

char Posicao::getCharVisivel(bool temJardineiro) const {
    if (temJardineiro) return '*';
    if (planta != nullptr) return planta->getChar(); // chama o metodo e a propria planta decide qual e o char 
    if (ferramenta != nullptr) return ferramenta->getChar();
    return ' ';
}
