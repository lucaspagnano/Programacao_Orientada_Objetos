#include "../../include/Core/Simulador.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Settings.h"
#include "../../include/Comandos/Comando.h"

#include "../../include/Comandos/JardimCmd.h"
#include "../../include/Comandos/Avanca.h"
#include "../../include/Comandos/LPlantas.h"
#include "../../include/Comandos/LPlanta.h"
#include "../../include/Comandos/LArea.h"
#include "../../include/Comandos/LSolo.h"
#include "../../include/Comandos/LFerr.h"
#include "../../include/Comandos/Colhe.h"
#include "../../include/Comandos/PlantaCmd.h"
#include "../../include/Comandos/Larga.h"
#include "../../include/Comandos/Pega.h"
#include "../../include/Comandos/Compra.h"
#include "../../include/Comandos/Move.h"
#include "../../include/Comandos/Entra.h"
#include "../../include/Comandos/Sai.h"
#include "../../include/Comandos/Grava.h"
#include "../../include/Comandos/Recupera.h"
#include "../../include/Comandos/Apaga.h"
#include "../../include/Comandos/Executa.h"


#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> splitString(const std::string& str) {
    std::stringstream ss(str);
    std::string palavra; // var temporaria vazia
    std::vector<std::string> palavras; // vetor para acumular resultado final 
    while (ss >> palavra) { // ciclo que extrai do stream ss para palavra
        palavras.push_back(palavra); // adiciona a palavra no final do vetor 
    }
    return palavras;
}

Simulador::Simulador(): jardim(nullptr),jardineiro(),instanteAtual(0),running(true)
{
    //std::cout << "Simulador iniciado.\n";
}

Simulador::~Simulador() {
    delete jardim; // aciona destrutor do jardim

    for (auto const& [nome, saveJardim] : saves) { // ciclo para percorrer todos os jogos guardados no mapa 
        delete saveJardim;
    }
    saves.clear();

    //std::cout << "Simulador encerrado. Toda a memoria foi limpa.\n";
}

Jardim* Simulador::getJardim() {
    return jardim;
}

Jardineiro* Simulador::getJardineiro() {
    return &jardineiro;
}

bool Simulador::isJardimCriado() const {
    return jardim != nullptr;
}

void Simulador::criaJardim(int l, int c) {
    if (jardim == nullptr) {
        jardim = new Jardim(l, c); // so executa se o ponteiro jardim estiver vazio 
    }
}

// passagem de instantes e faz plantas agirem
void Simulador::avancaInstante(int n) {
    for (int i = 0; i < n; ++i) { // avanca n instantes
        instanteAtual++;
        //std::cout << "\n Avancando para o Instante " << instanteAtual << " \n";

        jardineiro.resetContadoresTurno(); // reinicia energia do jardineiro

        if (jardim != nullptr) { // se jardim existir
            jardineiro.usarFerramenta(*jardim); // utiliza ferramente
            jardim->atualizarPlantas(); // faz planta agir 
        }
    }
}

void Simulador::shutdown() {
    running = false;
}

//funcao que pede ao jardim para se desenhar 
void Simulador::mostraJardim() const {
    if (jardim != nullptr) {
        jardim->desenha(jardineiro); // envia jardineiro para saber onde o mesmo esta e desenhar *
    }
}

bool Simulador::converteCoord(const std::string& coord, int& l, int& c) const {
    if (coord.length() != 2) return false;

    l = coord[0] - 'a';
    c = coord[1] - 'a';

    return (l >= 0 && l < 26 && c >= 0 && c < 26);
}

Comando* Simulador::criaComando(const std::string& linha) {
    std::vector<std::string> palavras = splitString(linha); // parte a frase em palavras
    if (palavras.empty()) {
        return nullptr;
    }

    std::string nomeCmd = palavras[0]; // copia primeira palavra em nomeCmd
    std::vector<std::string> args(palavras.begin() + 1, palavras.end()); // cria vetor para args

    // chama contrutores e passa args
    if (nomeCmd == "jardim") return new JardimCmd(args);
    if (nomeCmd == "avanca") return new Avanca(args);
    if (nomeCmd == "lplantas") return new LPlantas(args);
    if (nomeCmd == "lplanta") return new LPlanta(args);
    if (nomeCmd == "larea") return new LArea(args);
    if (nomeCmd == "lsolo") return new LSolo(args);
    if (nomeCmd == "lferr") return new LFerr(args);
    if (nomeCmd == "colhe") return new Colhe(args);
    if (nomeCmd == "planta") return new PlantaCmd(args);
    if (nomeCmd == "larga") return new Larga(args);
    if (nomeCmd == "pega") return new Pega(args);
    if (nomeCmd == "compra") return new Compra(args);
    if (nomeCmd == "e" || nomeCmd == "d" || nomeCmd == "c" || nomeCmd == "b") {return new Move({nomeCmd}); }
    if (nomeCmd == "entra") return new Entra(args);
    if (nomeCmd == "sai") return new Sai(args);
    if (nomeCmd == "grava") return new Grava(args);
    if (nomeCmd == "recupera") return new Recupera(args);
    if (nomeCmd == "apaga") return new Apaga(args);
    if (nomeCmd == "executa") return new Executa(args);

    std::cout << "Erro: Comando '" << nomeCmd << "' desconhecido.\n";
    return nullptr;
}

void Simulador::processaComando(const std::string& linha) {
    Comando* cmd = criaComando(linha);

    if (cmd == nullptr) {
        return;
    }

    bool eJardimCmd = (dynamic_cast<JardimCmd*>(cmd) != nullptr);
    bool eExecutaCmd = (dynamic_cast<Executa*>(cmd) != nullptr);

    if (!isJardimCriado() && !eJardimCmd && !eExecutaCmd) {
        std::cout << "Erro: O jardim ainda nao foi criado. Comece por usar o comando 'jardim'.\n";
        delete cmd;
        return;
    }

    cmd->executa(*this); // manda comando executar a acao, passamos esse simulador como arg 

    delete cmd;
}

//ciclo principal do jogo
void Simulador::run() {
    std::string linha;

    while (running) {
        mostraJardim();

        std::cout << "\n" << "Instante " << instanteAtual << " > ";

        if (!std::getline(std::cin, linha)) { // programa fica a espera do utilizador escrever comando
            break;
        }

        if (linha == "fim") {
            shutdown(); // running = false
            continue;
        }

        processaComando(linha); // envia texto para processaComando que chama a fabrica criaComando
    }
}


void Simulador::salvarJogo(const std::string& nome) {
    if (jardim == nullptr) {
        std::cout << "Erro: Nao ha jardim para gravar.\n";
        return;
    }

    if (saves.find(nome) != saves.end()) { // caso ja tenha um save com esse nome apaga o antigo
        delete saves[nome];
    }

    saves[nome] = new Jardim(*jardim);
    std::cout << "Jogo gravado com sucesso: '" << nome << "'.\n";
}

// so podemos recuperar uma vez
void Simulador::recuperarJogo(const std::string& nome) {
    if (saves.find(nome) == saves.end()) {
        std::cout << "Erro: Save '" << nome << "' nao encontrado.\n";
        return;
    }

    delete jardim; // apaga jogo atual

    jardim = new Jardim(*saves[nome]); //cria novo jogo a partir da copia 

    // apaga save original
    delete saves[nome]; 
    saves.erase(nome);

    std::cout << "Jogo recuperado de '" << nome << "'. (Save original apagado da memoria)\n";
}

// mantem a logica de apagar do recupera 
void Simulador::apagarSave(const std::string& nome) {
    if (saves.find(nome) == saves.end()) {
        std::cout << "Erro: A copia de seguranca '" << nome << "' nao existe.\n";
        return;
    }

    delete saves[nome];

    saves.erase(nome);

    std::cout << "Copia '" << nome << "' foi apagada da memoria com sucesso.\n";
}
