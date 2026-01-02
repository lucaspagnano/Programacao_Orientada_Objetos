#include "../include/Core/Simulador.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {

    srand(static_cast<unsigned int>(time(NULL)));

    //std::cout << "DEBUG: Random seed inicializada.\n";

    Simulador simulador;
    simulador.run();

    return 0;
}