#ifndef PROJETO_POO_PLANTACMD_H
#define PROJETO_POO_PLANTACMD_H

#include "Comando.h"
#include <string>

class PlantaCmd : public Comando {
    std::string coord;
    char tipoPlanta;
    int linha, coluna;

public:
    PlantaCmd(const std::vector<std::string>& args);

    ~PlantaCmd() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_PLANTACMD_H