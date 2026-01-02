#ifndef PROJETO_POO_MOVE_H
#define PROJETO_POO_MOVE_H

#include "Comando.h"

class Move : public Comando {
    char direcao;

public:
    Move(const std::vector<std::string>& args);

    ~Move() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_MOVE_H