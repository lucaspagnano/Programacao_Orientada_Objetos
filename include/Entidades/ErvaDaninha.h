#ifndef PROJETO_POO_ERVADANINHA_H
#define PROJETO_POO_ERVADANINHA_H

#include "Planta.h"
class ErvaDaninha : public Planta {
public:
    ErvaDaninha();
    ~ErvaDaninha() override = default;
    char getChar() const override;
    void agir(Jardim& jardim, int l, int c) override;
    ErvaDaninha* clone() const override { return new ErvaDaninha(*this); }
};

#endif //PROJETO_POO_ERVADANINHA_H