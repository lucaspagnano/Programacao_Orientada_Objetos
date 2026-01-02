#include "../../include/Entidades/ErvaDaninha.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include <iostream>

ErvaDaninha::ErvaDaninha()
    : Planta(Settings::ErvaDaninha::inicial_agua,
             Settings::ErvaDaninha::inicial_nutrientes,
             "feia") // Importante ser "feia" para a Tesoura
{
}

char ErvaDaninha::getChar() const { return 'e'; }

void ErvaDaninha::agir(Jardim& jardim, int l, int c) {
    this->instantesDeVida++;
    Posicao* posAtual = jardim.getPosicao(l, c);
    // 1. ABSORÇÃO
    this->aguaInterna += posAtual->retiraAgua(Settings::ErvaDaninha::absorcao_agua);
    this->nutrientesInternos += posAtual->retiraNutrientes(Settings::ErvaDaninha::absorcao_nutrientes);

    // 2. MORTE POR VELHICE
    if (this->instantesDeVida >= Settings::ErvaDaninha::morre_instantes) {
        std::cout << "Uma Erva Daninha morreu de velhice.\n";
        delete posAtual->removePlanta();
        return;
    }

    // 3. REPRODUÇÃO (Lógica Simplificada)
    // Multiplica a cada 5 instantes E se tiver nutrientes > 30
    if (this->instantesDeVida % Settings::ErvaDaninha::multiplica_instantes == 0 &&
        this->nutrientesInternos > Settings::ErvaDaninha::multiplica_nutrientes_maior) {

        Posicao* vizinho = jardim.getVizinhoLivreAleatorio(l, c);

        if (vizinho != nullptr) {
            std::cout << "PRAGA! A Erva Daninha espalhou-se!\n";
            vizinho->setPlanta(new ErvaDaninha());

            // Custo pequeno ou nulo para a erva daninha
            this->nutrientesInternos -= 10;
        }
    }
}