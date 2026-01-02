#ifndef PROJETO_POO_GRAVA_H
#define PROJETO_POO_GRAVA_H
#include "Comando.h"
#include <string>
class Grava : public Comando {
    std::string nomeSave;
public:
    Grava(const std::vector<std::string>& args);
    ~Grava() override = default;
    bool executa(Simulador& s) override;
};
#endif