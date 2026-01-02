#ifndef PROJETO_POO_FERRAMENTAZ_H
#define PROJETO_POO_FERRAMENTAZ_H

#include "Ferramenta.h"

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ();
    ~FerramentaZ() override = default;
    char getChar() const override;
    void usar(Jardim& j, int l, int c) override;
    FerramentaZ* clone() const override { return new FerramentaZ(*this); }
};

#endif //PROJETO_POO_FERRAMENTAZ_H