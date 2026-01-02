#ifndef PROJETO_POO_SIMULADOR_H
#define PROJETO_POO_SIMULADOR_H

#include "../Entidades/Jardineiro.h"
#include <map>
#include <string>

class Jardim;
class Comando;

class Simulador {

    Jardim* jardim;
    Jardineiro jardineiro;

    int instanteAtual;
    bool running;

    Comando* criaComando(const std::string& linha);
    void mostraJardim() const;

    std::map<std::string, Jardim*> saves;

public:
    Simulador();
    ~Simulador();
    void run();

    void processaComando(const std::string& linha);
    Jardim* getJardim();
    Jardineiro* getJardineiro();
    bool isJardimCriado() const;
    void criaJardim(int l, int c);
    void avancaInstante(int n);
    void shutdown();
    bool converteCoord(const std::string& coord, int& l, int& c) const;

    void salvarJogo(const std::string& nome);
    void recuperarJogo(const std::string& nome);
    void apagarSave(const std::string& nome);
};

#endif //PROJETO_POO_SIMULADOR_H