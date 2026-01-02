#include "../../include/Entidades/Roseira.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include <iostream>

Roseira::Roseira()
    : Planta(Settings::Roseira::inicial_agua,
             Settings::Roseira::inicial_nutrientes,
             "bonita")
{
}

char Roseira::getChar() const { return 'r'; }

void Roseira::agir(Jardim& jardim, int l, int c) {
    this->instantesDeVida++;
    Posicao* posAtual = jardim.getPosicao(l, c);
    this->aguaInterna -= Settings::Roseira::perda_agua;
    this->nutrientesInternos -= Settings::Roseira::perda_nutrientes;

    int bebeu = posAtual->retiraAgua(Settings::Roseira::absorcao_agua);
    int comeu = posAtual->retiraNutrientes(Settings::Roseira::absorcao_nutrientes);

    this->aguaInterna += bebeu;
    this->nutrientesInternos += comeu;

    if (this->aguaInterna < Settings::Roseira::morre_agua_menor ||
        this->nutrientesInternos < Settings::Roseira::morre_nutrientes_menor ||
        this->nutrientesInternos > Settings::Roseira::morre_nutrientes_maior) {

        std::cout << "Uma Roseira morreu de causas naturais.\n";
        delete posAtual->removePlanta();
        return;
        }

    if (this->nutrientesInternos > Settings::Roseira::multiplica_nutrientes_maior) {
        Posicao* vizinho = jardim.getVizinhoLivreAleatorio(l, c);

        if (vizinho != nullptr) {
            std::cout << "Uma Roseira reproduziu-se para o lado.\n";

            vizinho->setPlanta(new Roseira());

            this->nutrientesInternos = Settings::Roseira::inicial_nutrientes;
        }
    }
}