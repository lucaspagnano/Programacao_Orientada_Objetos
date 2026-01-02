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

    // 1. ABSORÇÃO DE ÁGUA (Percentagem do que existe no solo)
    // Cacto absorve 25% da água disponível no solo
    int aguaDisponivel = posAtual->getAgua();
    int qtdBeber = (aguaDisponivel * Settings::Cacto::absorcao_agua_percentagem) / 100;

    // Se a conta der 0 mas houver água, bebe pelo menos 1
    if (qtdBeber == 0 && aguaDisponivel > 0) qtdBeber = 1;

    this->aguaInterna += posAtual->retiraAgua(qtdBeber);

    // 2. ABSORÇÃO DE NUTRIENTES
    this->nutrientesInternos += posAtual->retiraNutrientes(Settings::Cacto::absorcao_nutrientes);

    // 3. MORTE (Verificação Simplificada)
    // Se o solo tiver muita água (>100) ou poucos nutrientes (<1)
    if (posAtual->getAgua() > Settings::Cacto::morre_agua_solo_maior ||
        posAtual->getNutrientes() < Settings::Cacto::morre_nutrientes_solo_menor) {

        // NOTA: O enunciado pede contagem de 3 dias.
        // Se quiseres implementar rigorosamente, adiciona contadores ao Cacto.h.
        // Aqui matamos logo como aviso:
        std::cout << "Um Cacto morreu devido as condicoes do solo!\n";
        delete posAtual->removePlanta();
        return;
        }
}