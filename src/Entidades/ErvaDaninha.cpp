#include "../../include/Entidades/ErvaDaninha.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include <iostream>

ErvaDaninha::ErvaDaninha()
    : Planta(Settings::ErvaDaninha::inicial_agua,
             Settings::ErvaDaninha::inicial_nutrientes,
             "feia")
{
}

char ErvaDaninha::getChar() const { return 'e'; }

void ErvaDaninha::agir(Jardim& jardim, int l, int c) {
    this->instantesDeVida++;
    Posicao* posAtual = jardim.getPosicao(l, c);
    this->aguaInterna += posAtual->retiraAgua(Settings::ErvaDaninha::absorcao_agua);
    this->nutrientesInternos += posAtual->retiraNutrientes(Settings::ErvaDaninha::absorcao_nutrientes);

    if (this->instantesDeVida >= Settings::ErvaDaninha::morre_instantes) {
        std::cout << "Uma Erva Daninha morreu de velhice.\n";
        delete posAtual->removePlanta();
        return;
    }

    if (this->instantesDeVida % Settings::ErvaDaninha::multiplica_instantes == 0 &&
        this->nutrientesInternos > Settings::ErvaDaninha::multiplica_nutrientes_maior) {

        Posicao* vizinho = jardim.getVizinhoLivreAleatorio(l, c);

        if (vizinho != nullptr) {
            std::cout << "A Erva Daninha espalhou-se!\n";
            vizinho->setPlanta(new ErvaDaninha());

            this->nutrientesInternos -= 10;
        }
    }
}