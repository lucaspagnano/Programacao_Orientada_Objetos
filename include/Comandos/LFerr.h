#ifndef PROJETO_POO_LFERR_H
#define PROJETO_POO_LFERR_H

#include "Comando.h"

class LFerr : public Comando {
public:
    LFerr(const std::vector<std::string>& args);

    ~LFerr() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_LFERR_H