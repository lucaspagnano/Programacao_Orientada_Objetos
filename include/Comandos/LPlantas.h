#ifndef PROJETO_POO_LPLANTAS_H
#define PROJETO_POO_LPLANTAS_H

#include "Comando.h"

class LPlantas : public Comando {
public:
    LPlantas(const std::vector<std::string>& args);

    ~LPlantas() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_LPLANTAS_H