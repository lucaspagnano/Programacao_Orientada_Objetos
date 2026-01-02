#ifndef PROJETO_POO_AVANCA_H
#define PROJETO_POO_AVANCA_H

#include "Comando.h"

class Avanca : public Comando {
    int instantes;

public:
    Avanca(const std::vector<std::string>& args);

    ~Avanca() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_AVANCA_H