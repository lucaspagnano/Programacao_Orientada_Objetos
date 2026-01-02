#ifndef PROJETO_POO_JARDIMCMD_H
#define PROJETO_POO_JARDIMCMD_H

#include "Comando.h"

class JardimCmd : public Comando {
    int linhas;
    int colunas;

public:
    JardimCmd(const std::vector<std::string>& args);

    ~JardimCmd() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_JARDIMCMD_H