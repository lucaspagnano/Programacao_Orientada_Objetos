#include "../../include/Items/Adubo.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include <iostream>

Adubo::Adubo()
    : Ferramenta("Pacote de Adubo"),
      capacidade(Settings::Adubo::capacidade)
{
    std::cout << "DEBUG: Adubo (S/N " << getNumSerie() << ") criado.\n";
}

char Adubo::getChar() const {
    return 'a';
}

void Adubo::usar(Jardim& j, int l, int c) {
    int dose = 10;
    if (capacidade < dose) {
        std::cout << "O Pacote de Adubo esta vazio!\n";
        return;
    }

    Posicao* p = j.getPosicao(l, c);

    if (p != nullptr) {
        p->addNutrientes(dose);
        this->capacidade -= dose;

        std::cout << "Fertilizou a posicao " << l << " " << c
                  << ". Nutrientes: " << p->getNutrientes()
                  << " | Resta no pacote: " << capacidade << "\n";
    }
}

bool Adubo::deveQuebrar() const {
    return capacidade < 10;
}