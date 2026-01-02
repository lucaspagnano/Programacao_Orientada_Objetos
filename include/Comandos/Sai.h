#ifndef PROJETO_POO_SAI_H
#define PROJETO_POO_SAI_H

#include "Comando.h"

class Sai : public Comando {
public:
    Sai(const std::vector<std::string>& args);

    ~Sai() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_SAI_H