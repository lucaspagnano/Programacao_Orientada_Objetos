#ifndef PROJETO_POO_LARGA_H
#define PROJETO_POO_LARGA_H

#include "Comando.h"

class Larga : public Comando {
public:
    Larga(const std::vector<std::string>& args);

    ~Larga() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_LARGA_H