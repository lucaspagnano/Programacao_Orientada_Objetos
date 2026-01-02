#include "../../include/Comandos/Executa.h"
#include "../../include/Core/Simulador.h"
#include <iostream>
#include <fstream>

Executa::Executa(const std::vector<std::string>& args) {
    if (args.empty()) { std::cout << "Erro: Falta o nome do ficheiro.\n"; valido = false; return; }
    nomeFicheiro = args[0];
    valido = true;
}
bool Executa::executa(Simulador& s) {
    if (!valido) return false;
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) { std::cout << "Erro: Nao foi possivel abrir o ficheiro '" << nomeFicheiro << "'.\n"; return false; }
    std::cout << "A executar comandos do ficheiro: " << nomeFicheiro << "...\n";
    std::string linha;
    while (std::getline(ficheiro, linha)) {
        if (linha.empty()) continue;
        s.processaComando(linha); 
    }
    ficheiro.close();
    return true;
}