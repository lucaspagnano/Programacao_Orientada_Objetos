#ifndef PROJETO_POO_COLHE_H
#define PROJETO_POO_COLHE_H

#include "Comando.h"

class Colhe : public Comando {
    std::string coord;
    int linha, coluna;

public:
    Colhe(const std::vector<std::string>& args);

    ~Colhe() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_COLHE_H