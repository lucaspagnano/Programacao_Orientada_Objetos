#include "../../include/Entidades/PlantaExotica.h"
#include <iostream>

PlantaExotica::PlantaExotica()
    : Planta(0, 0, "neutra") 
{
    std::cout << "DEBUG: Uma Planta Exotica foi plantada.\n";
}

char PlantaExotica::getChar() const {
    return 'x';
}

void PlantaExotica::agir(Jardim& jardim, int l, int c) {
    std::cout << "A Planta Exotica na posicao [?, ?] esta a agir...\n";
}