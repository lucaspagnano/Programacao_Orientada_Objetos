#ifndef PROJETO_POO_LPLANTA_H
#define PROJETO_POO_LPLANTA_H

#include "Comando.h"

class LPlanta : public Comando {
    std::string coord;

public:
    LPlanta(const std::vector<std::string>& args);

    ~LPlanta() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_LPLANTA_H