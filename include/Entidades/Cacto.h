#ifndef PROJETO_POO_CACTO_H
#define PROJETO_POO_CACTO_H

#include "Planta.h"

class Cacto : public Planta {
public:
    Cacto();
    ~Cacto() override = default;

    char getChar() const override;
    void agir(Jardim& jardim, int l, int c) override;
    Cacto* clone() const override { return new Cacto(*this); }
};

#endif //PROJETO_POO_CACTO_H