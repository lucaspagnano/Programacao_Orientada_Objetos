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
    // 1. METABOLISMO (Perde recursos internos)
    this->aguaInterna -= Settings::Roseira::perda_agua;
    this->nutrientesInternos -= Settings::Roseira::perda_nutrientes;

    // 2. ABSORÇÃO (Tenta repor do solo)
    // Usa os novos métodos da Posicao para garantir que não tira o que não existe
    int bebeu = posAtual->retiraAgua(Settings::Roseira::absorcao_agua);
    int comeu = posAtual->retiraNutrientes(Settings::Roseira::absorcao_nutrientes);

    this->aguaInterna += bebeu;
    this->nutrientesInternos += comeu;

    // 3. VERIFICAR MORTE
    // Morre se água < 1, nutrientes < 1 ou nutrientes > 199
    if (this->aguaInterna < Settings::Roseira::morre_agua_menor ||
        this->nutrientesInternos < Settings::Roseira::morre_nutrientes_menor ||
        this->nutrientesInternos > Settings::Roseira::morre_nutrientes_maior) {

        std::cout << "Uma Roseira morreu de causas naturais.\n";
        delete posAtual->removePlanta(); // Remove-se a si própria e liberta memória
        return; // Sai da função imediatamente
        }

    // 4. REPRODUÇÃO (Opcional - Implementaremos a lógica de vizinhos depois)
    if (this->nutrientesInternos > Settings::Roseira::multiplica_nutrientes_maior) {
        Posicao* vizinho = jardim.getVizinhoLivreAleatorio(l, c);

        if (vizinho != nullptr) {
            std::cout << "Uma Roseira reproduziu-se para o lado!\n";

            // Cria uma nova Roseira no vizinho
            vizinho->setPlanta(new Roseira());

            // A mãe perde nutrientes ao criar o filho (custo da reprodução)
            // Geralmente volta ao valor base ou perde uma percentagem
            this->nutrientesInternos = Settings::Roseira::inicial_nutrientes;
        }
    }
}