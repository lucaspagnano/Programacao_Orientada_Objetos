#include "../include/Core/Simulador.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

void menu() {
    const int cmdWidth = 25;
    std::cout << "\n" << std::string(85, '-') << "\n";
    std::cout << std::left << std::setw(cmdWidth) << "COMANDO" << " | " << "DESCRICAO" << "\n";
    std::cout << std::string(85, '-') << "\n";
    std::cout << std::setw(cmdWidth) << "jardim <l> <c>" << " | " << "Cria o jardim com 'l' linhas e 'c' colunas (1o comando).\n";
    std::cout << std::setw(cmdWidth) << "avanca [n]" << " | " << "Avanca 'n' instantes na simulacao (default: 1).\n";
    std::cout << std::setw(cmdWidth) << "executa <nome>" << " | " << "Executa lista de comandos de um ficheiro de texto.\n";
    std::cout << std::setw(cmdWidth) << "grava <nome>" << " | " << "Guarda o estado atual do jardim em memoria.\n";
    std::cout << std::setw(cmdWidth) << "recupera <nome>" << " | " << "Recupera um estado do jardim guardado anteriormente.\n";
    std::cout << std::setw(cmdWidth) << "apaga <nome>" << " | " << "Apaga uma gravacao da memoria.\n";
    std::cout << std::setw(cmdWidth) << "fim" << " | " << "Termina a simulacao e liberta recursos.\n";
    std::cout << std::setw(cmdWidth) << "entra <l><c>" << " | " << "Jardineiro entra no jardim na posicao (linha, coluna).\n";
    std::cout << std::setw(cmdWidth) << "sai" << " | " << "Jardineiro sai do jardim.\n";
    std::cout << std::setw(cmdWidth) << "e / d / c / b" << " | " << "Move jardineiro (Esq, Dir, Cima, Baixo). Max 10/turno.\n";
    std::cout << std::setw(cmdWidth) << "lplantas" << " | " << "Lista todas as plantas vivas e seus atributos.\n";
    std::cout << std::setw(cmdWidth) << "lplanta <l><c>" << " | " << "Mostra detalhes da planta numa posicao especifica.\n";
    std::cout << std::setw(cmdWidth) << "larea" << " | " << "Lista conteudo/propriedades de posicoes nao vazias.\n";
    std::cout << std::setw(cmdWidth) << "lsolo <l><c> [n]" << " | " << "Detalhes do solo (opcional: quadrado de raio n).\n";
    std::cout << std::setw(cmdWidth) << "lferr" << " | " << "Lista as ferramentas na posse do jardineiro.\n";
    std::cout << std::setw(cmdWidth) << "colhe" << " | " << "Colhe a planta na posicao atual (Max 5 por turno).\n";
    std::cout << std::setw(cmdWidth) << "planta <l><c> <t>" << " | " << "Planta especie (c,r,e,x) na posicao (Max 2 por turno).\n";
    std::cout << std::setw(cmdWidth) << "compra <t>" << " | " << "Compra uma ferramenta do tipo g, a, t ou z.\n";
    std::cout << std::setw(cmdWidth) << "pega <id>" << " | " << "Coloca na mao a ferramenta com o numero de serie id.\n";
    std::cout << std::setw(cmdWidth) << "larga" << " | " << "Larga a ferramenta que esta atualmente na mao.\n";
    std::cout << std::string(85, '-') << "\n";
}

int main() {

    srand(static_cast<unsigned int>(time(NULL)));
    menu();
    Simulador simulador;
    simulador.run();

    return 0;
}