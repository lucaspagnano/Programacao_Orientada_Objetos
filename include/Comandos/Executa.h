#ifndef PROJETO_POO_EXECUTA_H
#define PROJETO_POO_EXECUTA_H

#include "Comando.h"
#include <string>

class Executa : public Comando {
    std::string nomeFicheiro;

public:
    Executa(const std::vector<std::string>& args);

    ~Executa() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_EXECUTA_H