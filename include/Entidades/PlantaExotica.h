#ifndef PROJETO_POO_PLANTAEXOTICA_H
#define PROJETO_POO_PLANTAEXOTICA_H

#include "Planta.h"

class PlantaExotica : public Planta {
public:
    PlantaExotica();
    ~PlantaExotica() override = default;

    char getChar() const override;
    void agir(Jardim& jardim, int l, int c) override;
    PlantaExotica* clone() const override { return new PlantaExotica(*this); }
};

#endif //PROJETO_POO_PLANTAEXOTICA_H