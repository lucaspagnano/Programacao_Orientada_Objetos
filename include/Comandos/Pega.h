#ifndef PROJETO_POO_PEGA_H
#define PROJETO_POO_PEGA_H

#include "Comando.h"

class Pega : public Comando {
    int numSerie;

public:
    Pega(const std::vector<std::string>& args);

    ~Pega() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_PEGA_H