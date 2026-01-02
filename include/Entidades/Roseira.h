#ifndef PROJETO_POO_ROSEIRA_H
#define PROJETO_POO_ROSEIRA_H

#include "Planta.h"

class Roseira : public Planta {
public:
    Roseira();
    ~Roseira() override = default;
    char getChar() const override;
    void agir(Jardim& jardim, int l, int c) override;
    Roseira* clone() const override { return new Roseira(*this); }
};

#endif //PROJETO_POO_ROSEIRA_H