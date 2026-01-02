#ifndef PROJETO_POO_POSICAO_H
#define PROJETO_POO_POSICAO_H

class Planta;
class Ferramenta;

class Posicao {
    int agua;
    int nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    Posicao();
    ~Posicao();

    int getAgua() const;
    int getNutrientes() const;
    Planta* getPlanta() const;
    Ferramenta* getFerramenta() const;
    char getCharVisivel(bool temJardineiro) const;
    void addAgua(int valor);
    void addNutrientes(int valor);
    void setAgua(int valor);
    void setNutrientes(int valor);
    void setPlanta(Planta* p);
    void setFerramenta(Ferramenta* f);
    int retiraAgua(int qtd);
    int retiraNutrientes(int qtd);

    Planta* removePlanta();
    Ferramenta* removeFerramenta();
};

#endif //PROJETO_POO_POSICAO_H