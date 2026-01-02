#ifndef PROJETO_POO_COMANDO_H
#define PROJETO_POO_COMANDO_H

#include <string>
#include <vector>

class Simulador;

class Comando {
protected:
    bool valido;

public:
    Comando() : valido(false) {}

    virtual ~Comando() {}

    virtual bool executa(Simulador& s) = 0;

    bool estaValido() const { return valido; }
};

#endif //PROJETO_POO_COMANDO_H