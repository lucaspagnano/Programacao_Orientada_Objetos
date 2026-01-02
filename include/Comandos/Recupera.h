#ifndef PROJETO_POO_RECUPERA_H
#define PROJETO_POO_RECUPERA_H

#include "Comando.h"
#include <string>

class Recupera : public Comando {
    std::string nomeSave;
public:
    Recupera(const std::vector<std::string>& args);
    ~Recupera() override = default;
    bool executa(Simulador& s) override;
};
#endif