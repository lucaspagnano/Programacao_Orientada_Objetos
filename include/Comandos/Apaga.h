#ifndef PROJETO_POO_APAGA_H
#define PROJETO_POO_APAGA_H

#include "Comando.h"
#include <string>

class Apaga : public Comando {
    // Membro para guardar o nome da cópia
    std::string nomeCopia;

public:
    Apaga(const std::vector<std::string>& args);

    ~Apaga() override = default;

    bool executa(Simulador& s) override;
};

#endif //PROJETO_POO_APAGA_H