#ifndef PROJETO_POO_FERRAMENTA_H
#define PROJETO_POO_FERRAMENTA_H

#include <string>

class Jardim;

class Ferramenta {
protected:
    const int numSerie;
    std::string nome;

private:
    static int proxNumSerie;

public:
    Ferramenta(const std::string& nome);
    virtual ~Ferramenta() {}

    virtual char getChar() const = 0;
    virtual void usar(Jardim& j, int l, int c) = 0;
    virtual Ferramenta* clone() const = 0;

    virtual bool deveQuebrar() const { return false; }

    int getNumSerie() const;
    std::string getNome() const;
};

#endif //PROJETO_POO_FERRAMENTA_H