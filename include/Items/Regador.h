#ifndef PROJETO_POO_REGADOR_H
#define PROJETO_POO_REGADOR_H

#include "Ferramenta.h"

class Regador : public Ferramenta {
    int capacidade;

public:
    Regador();
    ~Regador() override = default;
    char getChar() const override;
    void usar(Jardim& j, int l, int c) override;
    bool deveQuebrar() const override;
    Regador* clone() const override { return new Regador(*this); }
};

#endif //PROJETO_POO_REGADOR_H