#include "../../include/Comandos/Move.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Core/Posicao.h" // Importante para aceder à Posicao
#include <iostream>

Move::Move(const std::vector<std::string>& args): direcao('?')
{
    if (args.size() != 1) {
        std::cout << "Erro: Comando 'move' (ou setas) requer direcao.\n";
        this->valido = false; return;
    }
    char dir = args[0][0];
    if (dir != 'e' && dir != 'd' && dir != 'c' && dir != 'b') {
        std::cout << "Erro: Direcao invalida.\n";
        this->valido = false; return;
    }
    this->direcao = dir;
    this->valido = true;
}

bool Move::executa(Simulador& s) {
    if (!this->valido) return false;
    if (!s.isJardimCriado()) { std::cout << "Erro: Jardim nao criado.\n"; return false; }

    Jardineiro* jardineiro = s.getJardineiro();
    Jardim* jardim = s.getJardim();

    if (!jardineiro->estaNoJardim()) {
        std::cout << "Erro: Jardineiro fora do jardim.\n"; return false;
    }
    if (!jardineiro->podeMover()) {
        std::cout << "Erro: Jardineiro cansado.\n"; return false;
    }

    // Calcular nova posição
    int l = jardineiro->getPosLinha();
    int c = jardineiro->getPosColuna();

    if (this->direcao == 'c') l--;
    else if (this->direcao == 'b') l++;
    else if (this->direcao == 'e') c--;
    else if (this->direcao == 'd') c++;

    if (!jardim->isPosicaoValida(l, c)) {
        std::cout << "Erro: Limite do jardim.\n"; return false;
    }

    // 1. Mover
    jardineiro->move(this->direcao);
    jardineiro->registarMovimento();
    std::cout << "Jardineiro moveu-se para " << l << " " << c << ".\n";

    // 2. --- LÓGICA DE APANHAR FERRAMENTA ---
    Posicao* pos = jardim->getPosicao(l, c);

    // Verifica se há ferramenta no chão
    if (pos->getFerramenta() != nullptr) {
        // Remove do chão e entrega ao jardineiro
        Ferramenta* f = pos->removeFerramenta();
        jardineiro->apanhaFerramenta(f);
    }

    return true;
}