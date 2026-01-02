#ifndef PROJETO_POO_TESOURA_H
#define PROJETO_POO_TESOURA_H

#include "Ferramenta.h"

class Tesoura : public Ferramenta {
public:
    Tesoura();
    ~Tesoura() override = default;
    char getChar() const override;
    void usar(Jardim& j, int l, int c) override;
    Tesoura* clone() const override { return new Tesoura(*this); }
};

#endif //PROJETO_POO_TESOURA_H