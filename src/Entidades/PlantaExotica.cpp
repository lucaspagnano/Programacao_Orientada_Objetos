#include "../../include/Entidades/PlantaExotica.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include "../../include/Core/Settings.h"
#include <iostream>

PlantaExotica::PlantaExotica()
    : Planta(Settings::PlantaExotica::inicial_agua,
             Settings::PlantaExotica::inicial_nutrientes,
             "Exotica")
{
}

char PlantaExotica::getChar() const {
    return 'x';
}

void PlantaExotica::agir(Jardim& jardim, int l, int c) {
    Posicao* solo = jardim.getPosicao(l, c);

    int agua = solo->retiraAgua(Settings::PlantaExotica::bebe_agua);
    int nutri = solo->retiraNutrientes(Settings::PlantaExotica::bebe_nutrientes);

    this->aguaInterna += agua;
    this->nutrientesInternos += nutri;

    this->aguaInterna -= Settings::PlantaExotica::consumo_agua;
    this->nutrientesInternos -= Settings::PlantaExotica::consumo_nutrientes;

    this->instantesDeVida++;

    if (this->aguaInterna <= 0) {
        this->aguaInterna = 0;
        return;
    }

    if (this->aguaInterna > Settings::PlantaExotica::min_agua_reproduz) {
        int dL[] = {-1, 1, 0, 0};
        int dC[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nL = l + dL[i];
            int nC = c + dC[i];

            if (jardim.isPosicaoValida(nL, nC)) {
                Posicao* vizinho = jardim.getPosicao(nL, nC);
                if (vizinho->getPlanta() == nullptr) {
                    Planta* filho = this->clone();
                    vizinho->setPlanta(filho);

                    this->aguaInterna -= Settings::PlantaExotica::custo_agua_reproduz;
                    std::cout << "Bambu expandiu-se para (" << nL << ", " << nC << ")!\n";
                    break;
                }
            }
        }
    }
}