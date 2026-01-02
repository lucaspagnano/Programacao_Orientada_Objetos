#include "../../include/Comandos/JardimCmd.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Core/Settings.h"
#include <iostream>
#include <sstream>

JardimCmd::JardimCmd(const std::vector<std::string>& args): linhas(0), colunas(0)
{
    if (args.size() != 2) {
        std::cout << "Erro: Comando 'jardim' requer 2 argumentos (linhas colunas).\n";
        return;
    }

    std::stringstream ss_linhas(args[0]);
    std::stringstream ss_colunas(args[1]);

    if (!(ss_linhas >> linhas) || !(ss_colunas >> colunas)) {
        std::cout << "Erro: Dimensoes do jardim devem ser numeros inteiros.\n";
        return;
    }

    int maxDim = Settings::Jardim::max_dim;
    if (linhas <= 0 || colunas <= 0) {
        std::cout << "Erro: Dimensoes do jardim devem ser positivas.\n";
        return; //
    }

    if (linhas > maxDim || colunas > maxDim) {
        std::cout << "Erro: Dimensoes maximas sao " << maxDim << "x" << maxDim << ".\n";
        return;
    }

    this->valido = true;
    //std::cout << "DEBUG: Comando 'jardim " << linhas << " " << colunas << "' validado.\n";
}

bool JardimCmd::executa(Simulador& s) {
    if (!this->valido) {
        std::cout << "Comando 'jardim' falhou a validacao (ja reportado).\n";
        return false;
    }

    if (s.isJardimCriado()) {
        std::cout << "Erro: O jardim ja foi criado e nao pode ser alterado.\n";
        return false;
    }

    s.criaJardim(linhas, colunas);
    //std::cout << "Jardim " << linhas << "x" << colunas << " criado com sucesso.\n";
    
    return true;
}