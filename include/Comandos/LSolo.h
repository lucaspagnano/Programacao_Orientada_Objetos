#ifndef PROJETO_POO_LSOLO_H
#define PROJETO_POO_LSOLO_H

#include "Comando.h"

class LSolo : public Comando {
    std::string coord;
    int raio;
    int linha, coluna;

public:
    LSolo(const std::vector<std::string>& args);

    ~LSolo() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_LSOLO_H