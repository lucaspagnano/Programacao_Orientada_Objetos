#ifndef PROJETO_POO_LAREA_H
#define PROJETO_POO_LAREA_H

#include "Comando.h"

class LArea : public Comando {
public:
    LArea(const std::vector<std::string>& args);

    ~LArea() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_LAREA_H