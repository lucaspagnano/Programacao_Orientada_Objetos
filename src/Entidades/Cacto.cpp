#include "../../include/Entidades/Cacto.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include <iostream>


Cacto::Cacto()
    : Planta(0, 0, "neutra")
{
}

char Cacto::getChar() const { return 'c'; }

void Cacto::agir(Jardim& jardim, int l, int c) {
    this->instantesDeVida++;
    Posicao* posAtual = jardim.getPosicao(l, c);

    int aguaDisponivel = posAtual->getAgua();
    int qtdBeber = (aguaDisponivel * Settings::Cacto::absorcao_agua_percentagem) / 100;

    if (qtdBeber == 0 && aguaDisponivel > 0) qtdBeber = 1;

    this->aguaInterna += posAtual->retiraAgua(qtdBeber);

    this->nutrientesInternos += posAtual->retiraNutrientes(Settings::Cacto::absorcao_nutrientes);

    if (posAtual->getAgua() > Settings::Cacto::morre_agua_solo_maior ||
        posAtual->getNutrientes() < Settings::Cacto::morre_nutrientes_solo_menor) {

        std::cout << "Um Cacto morreu devido as condicoes do solo!\n";
        delete posAtual->removePlanta();
        return;
        }
}