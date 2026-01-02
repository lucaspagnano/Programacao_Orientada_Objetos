#include "../../include/Comandos/Avanca.h"
#include "../../include/Core/Simulador.h"
#include <iostream>
#include <sstream>

Avanca::Avanca(const std::vector<std::string>& args): instantes(1)
{
    if (args.size() > 1) {
        std::cout << "Erro: Comando 'avanca' [n] so pode ter um argumento.\n";
        this->valido = false;
        return;
    }

    if (args.size() == 1) {
        std::stringstream ss(args[0]);
        int n;

        if (!(ss >> n)) {
            std::cout << "Erro: 'avanca [n]' - 'n' deve ser um numero inteiro.\n";
            this->valido = false;
            return;
        }

        if (n <= 0) {
            std::cout << "Erro: 'avanca [n]' - 'n' deve ser um inteiro positivo.\n";
            this->valido = false;
            return;
        }

        this->instantes = n;
    }

    this->valido = true;
    std::cout << "DEBUG: Comando 'avanca " << this->instantes << "' validado.\n";
}

bool Avanca::executa(Simulador& s) {
    if (!this->valido) {
        std::cout << "Comando 'avanca' falhou a validacao (ja reportado).\n";
        return false;
    }

    if (!s.isJardimCriado()) {
        std::cout << "Erro: Nao pode avancar. O jardim ainda nao foi criado.\n";
        return false;
    }

    s.avancaInstante(this->instantes);
    
    return true;
}