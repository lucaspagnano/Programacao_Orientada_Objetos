#include "../../include/Items/Adubo.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h"
#include <iostream>

Adubo::Adubo()
    : Ferramenta("Pacote de Adubo"),
      capacidade(Settings::Adubo::capacidade) // Deve ser 100 inicialmente
{
    std::cout << "DEBUG: Adubo (S/N " << getNumSerie() << ") criado.\n";
}

char Adubo::getChar() const {
    return 'a';
}

void Adubo::usar(Jardim& j, int l, int c) {
    // Valor fixo de 10 unidades por uso
    int dose = 10;

    if (capacidade < dose) {
        std::cout << "O Pacote de Adubo esta vazio!\n";
        // Nota: A lógica de deitar fora o pacote vazio pode ser feita aqui
        // ou no Jardineiro, mas para já avisamos o utilizador.
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