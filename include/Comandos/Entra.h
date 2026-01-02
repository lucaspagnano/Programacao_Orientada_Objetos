#ifndef PROJETO_POO_ENTRA_H
#define PROJETO_POO_ENTRA_H

#include "Comando.h"

class Entra : public Comando {
    std::string coord;
    int linha, coluna;

public:
    Entra(const std::vector<std::string>& args);

    ~Entra() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_ENTRA_H