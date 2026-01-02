#include "../../include/Items/FerramentaZ.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include "../../include/Core/Settings.h"
#include <iostream>


FerramentaZ::FerramentaZ() : Ferramenta("Drone de Rega")
{
}

char FerramentaZ::getChar() const {
    return 'z';
}

void FerramentaZ::usar(Jardim& jardim, int l, int c) {
    std::cout << "[Drone] A regar area 3x3 em redor de (" << l << "," << c << ")...\n";

    int contador = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int linhaAlvo = l + i;
            int colAlvo = c + j;

            if (jardim.isPosicaoValida(linhaAlvo, colAlvo)) {
                Posicao* p = jardim.getPosicao(linhaAlvo, colAlvo);
                p->addAgua(Settings::FerramentaZ::agua_adicionada);
                contador++;
            }
        }
    }
    std::cout << "Drone regou " << contador << " posicoes (+20 agua cada).\n";
}