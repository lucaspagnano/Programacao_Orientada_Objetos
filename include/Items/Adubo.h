#ifndef PROJETO_POO_ADUBO_H
#define PROJETO_POO_ADUBO_H

#include "Ferramenta.h"

class Adubo : public Ferramenta {
    int capacidade;

public:
    Adubo();
    ~Adubo() override = default;
    char getChar() const override;
    void usar(Jardim& j, int l, int c) override;
    bool deveQuebrar() const override;
    Adubo* clone() const override { return new Adubo(*this); }
};

#endif //PROJETO_POO_ADUBO_H