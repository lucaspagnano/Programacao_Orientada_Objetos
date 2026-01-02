#ifndef PROJETO_POO_PLANTA_H
#define PROJETO_POO_PLANTA_H

#include <string>

class Jardim;
class Posicao;

class Planta {
protected:
    int aguaInterna;
    int nutrientesInternos;
    std::string beleza;
    int instantesDeVida;

public:
    Planta(int agua, int nutrientes, const std::string& beleza);
    virtual ~Planta() {}
    virtual char getChar() const = 0;
    virtual void agir(Jardim& jardim, int l, int c) = 0;
    virtual Planta* clone() const = 0;

    int getAguaInterna() const;
    int getNutrientesInternos() const;
    std::string getBeleza() const;
    int getInstantesDeVida() const;

    void setAguaInterna(int valor);
    void setNutrientesInternos(int valor);
};

#endif //PROJETO_POO_PLANTA_H