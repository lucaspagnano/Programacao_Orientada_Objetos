#ifndef PROJETO_POO_COMPRA_H
#define PROJETO_POO_COMPRA_H

#include "Comando.h"
#include <string>
#include <vector>

class Compra : public Comando {
    std::string tipo;
public:
    Compra(const std::vector<std::string>& args);
    ~Compra() override = default;
    bool executa(Simulador& s) override;
};
#endif