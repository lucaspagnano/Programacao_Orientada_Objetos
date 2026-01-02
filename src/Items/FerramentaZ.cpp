#include "../../include/Items/FerramentaZ.h"
#include <iostream>

FerramentaZ::FerramentaZ(): Ferramenta("Ferramenta Exotica Z")
{
    std::cout << "DEBUG: Uma FerramentaZ (S/N " << getNumSerie() << ") foi criada.\n";
}

char FerramentaZ::getChar() const {
    return 'z';
}

void FerramentaZ::usar(Jardim& j, int l, int c) {
    std::cout << "A FerramentaZ (S/N " << getNumSerie() << ") esta a ser usada...\n";

}