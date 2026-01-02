#ifndef PROJETO_POO_JARDINEIRO_H
#define PROJETO_POO_JARDINEIRO_H

#include "../Items/Ferramenta.h"
#include <vector>

class Jardim;

class Jardineiro {
    bool noJardim;
    int posLinha;
    int posColuna;

    std::vector<Ferramenta*> ferramentasTransportadas;

    Ferramenta* ferramentaNaMao;

    int movimentosTurno;
    int plantacoesTurno;
    int colheitasTurno;
    int entradasSaidasTurno;

public:
    Jardineiro();
    ~Jardineiro();
    bool estaNoJardim() const;
    int getPosLinha() const;
    int getPosColuna() const;
    void entra(int l, int c);
    void sai();
    void move(char direcao);
    void apanhaFerramenta(Ferramenta* f);
    void pegaFerramenta(int numSerie);
    void largaFerramenta();
    void usarFerramenta(Jardim& jardim);
    void colherPlanta(Jardim& jardim);
    void compraFerramenta(Ferramenta* f);
    Ferramenta* getFerramentaNaMao();
    void listarFerramentas() const;
    bool podeMover() const;
    bool podePlantar() const;
    bool podeColher() const;
    bool podeEntrarSair() const;
    void registarMovimento();
    void registarPlantacao();
    void registarColheita();
    void registarEntradaSaida();
    void resetContadoresTurno();

};

#endif //PROJETO_POO_JARDINEIRO_H