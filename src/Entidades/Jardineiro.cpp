#include "../../include/Entidades/Jardineiro.h"
#include "../../include/Core/Settings.h"
#include "../../include/Core/Posicao.h"
#include "../../include/Core/Jardim.h"
#include "../../include/Entidades/Planta.h"

#include <iostream>
#include <algorithm>

Jardineiro::Jardineiro()
    : noJardim(false),
      posLinha(-1),
      posColuna(-1),
      ferramentaNaMao(nullptr)
{
    resetContadoresTurno();
    std::cout << "DEBUG: Jardineiro criado.\n";
}

Jardineiro::~Jardineiro() {
    // Apaga a ferramenta da mão se existir
    if (ferramentaNaMao != nullptr) {
        delete ferramentaNaMao;
    }
    // Apaga as restantes do inventário (para evitar fugas de memória)
    for (Ferramenta* f : ferramentasTransportadas) {
        if (f != nullptr) delete f;
    }
    ferramentasTransportadas.clear();
}

bool Jardineiro::estaNoJardim() const { return noJardim; }
int Jardineiro::getPosLinha() const { return posLinha; }
int Jardineiro::getPosColuna() const { return posColuna; }

void Jardineiro::entra(int l, int c) {
    noJardim = true;
    posLinha = l;
    posColuna = c;
    registarEntradaSaida();
    std::cout << "Jardineiro entrou em (" << l << ", " << c << ")\n";
}

void Jardineiro::sai() {
    noJardim = false;
    posLinha = -1;
    posColuna = -1;
    registarEntradaSaida();
    std::cout << "Jardineiro saiu do jardim.\n";
}

void Jardineiro::move(char direcao) {
    if (direcao == 'c') posLinha--;
    else if (direcao == 'b') posLinha++;
    else if (direcao == 'e') posColuna--;
    else if (direcao == 'd') posColuna++;
}

void Jardineiro::apanhaFerramenta(Ferramenta* f) {
    if (f == nullptr) return;

    // Se não tiver nada na mão, fica logo com esta
    if (ferramentaNaMao == nullptr) {
        ferramentaNaMao = f;
        std::cout << "Jardineiro apanhou " << f->getNome() << " (ID: " << f->getNumSerie() << ") e ficou com ela na mao.\n";
    } else {
        // Senão, guarda na mochila
        ferramentasTransportadas.push_back(f);
        std::cout << "Jardineiro guardou " << f->getNome() << " (ID: " << f->getNumSerie() << ") na mochila.\n";
    }
}

Ferramenta* Jardineiro::getFerramentaNaMao() {
    return ferramentaNaMao;
}


// === IMPLEMENTAÇÃO DA LÓGICA DE USO ===

void Jardineiro::usarFerramenta(Jardim& jardim) {
    if (!noJardim || ferramentaNaMao == nullptr) {
        return; // Não faz nada se não estiver no jardim ou de mãos vazias
    }

    std::cout << "[Jardineiro] A usar " << ferramentaNaMao->getNome() << "...\n";

    // 1. Usa a ferramenta na posição atual
    ferramentaNaMao->usar(jardim, posLinha, posColuna);

    // 2. Verifica se a ferramenta quebrou/acabou
    if (ferramentaNaMao->deveQuebrar()) {
        std::cout << "!!! A ferramenta " << ferramentaNaMao->getNome()
                  << " (ID: " << ferramentaNaMao->getNumSerie() << ") quebrou/acabou e foi deitada fora! !!!\n";

        delete ferramentaNaMao;
        ferramentaNaMao = nullptr;
    }
}

// === GESTÃO DE INVENTÁRIO (Comandos lferr, larga, pega) ===

void Jardineiro::listarFerramentas() const {
    std::cout << "--- Inventario do Jardineiro ---\n";
    if (ferramentaNaMao != nullptr) {
        std::cout << "NA MAO: " << ferramentaNaMao->getNome()
                  << " (ID: " << ferramentaNaMao->getNumSerie() << ")\n";
    } else {
        std::cout << "NA MAO: (vazio)\n";
    }

    std::cout << "MOCHILA:\n";
    if (ferramentasTransportadas.empty()) {
        std::cout << "  (vazia)\n";
    } else {
        for (Ferramenta* f : ferramentasTransportadas) {
            std::cout << "  - " << f->getNome() << " (ID: " << f->getNumSerie() << ")\n";
        }
    }
}

void Jardineiro::largaFerramenta() {
    if (ferramentaNaMao == nullptr) {
        std::cout << "Nao tens nenhuma ferramenta na mao para largar.\n";
        return;
    }

    // Guarda na mochila (vector)
    ferramentasTransportadas.push_back(ferramentaNaMao);
    std::cout << "Guardaste " << ferramentaNaMao->getNome() << " na mochila.\n";

    // Esvazia a mão
    ferramentaNaMao = nullptr;
}

void Jardineiro::pegaFerramenta(int numSerie) {
    // 1. Procura na mochila
    auto it = std::find_if(ferramentasTransportadas.begin(), ferramentasTransportadas.end(),
        [numSerie](Ferramenta* f) { return f->getNumSerie() == numSerie; });

    if (it == ferramentasTransportadas.end()) {
        std::cout << "Nao tens nenhuma ferramenta com ID " << numSerie << " na mochila.\n";
        return;
    }

    // 2. Guardar temporariamente o ponteiro da ferramenta que queremos pegar
    Ferramenta* novaFerramenta = *it;

    // 3. Remover IMEDIATAMENTE da mochila (antes de fazer push_back de outra coisa)
    // Assim evitamos problemas com iteradores inválidos
    ferramentasTransportadas.erase(it);

    // 4. Se tiver algo na mão, guarda na mochila
    if (ferramentaNaMao != nullptr) {
        std::cout << "Guardaste " << ferramentaNaMao->getNome() << " na mochila.\n";
        ferramentasTransportadas.push_back(ferramentaNaMao);
    }

    // 5. Coloca a nova ferramenta na mão
    ferramentaNaMao = novaFerramenta;

    std::cout << "Pegaste em " << ferramentaNaMao->getNome() << " (ID: " << numSerie << ").\n";
}

void Jardineiro::compraFerramenta(Ferramenta* f) {
    if (f == nullptr) return;

    // Adiciona a ferramenta comprada diretamente a mochila
    ferramentasTransportadas.push_back(f);

    std::cout << "DEBUG: O Jardineiro guardou " << f->getNome()
              << " na mochila. Total de itens: " << ferramentasTransportadas.size() << "\n";
}

// Contadores (Mantêm-se iguais)
void Jardineiro::resetContadoresTurno() {
    movimentosTurno = Settings::Jardineiro::max_movimentos;
    plantacoesTurno = Settings::Jardineiro::max_plantacoes;
    colheitasTurno = Settings::Jardineiro::max_colheitas;
    entradasSaidasTurno = Settings::Jardineiro::max_entradas_saidas;
}
bool Jardineiro::podeMover() const { return movimentosTurno > 0; }
bool Jardineiro::podePlantar() const { return plantacoesTurno > 0; }
bool Jardineiro::podeColher() const { return colheitasTurno > 0; }
bool Jardineiro::podeEntrarSair() const { return entradasSaidasTurno > 0; }

void Jardineiro::registarMovimento() { if (movimentosTurno > 0) movimentosTurno--; }
void Jardineiro::registarPlantacao() { if (plantacoesTurno > 0) plantacoesTurno--; }
void Jardineiro::registarColheita() { if (colheitasTurno > 0) colheitasTurno--; }
void Jardineiro::registarEntradaSaida() { if (entradasSaidasTurno > 0) entradasSaidasTurno--; }

void Jardineiro::colherPlanta(Jardim& jardim) {
    // 1. Verificar se o jardineiro está dentro do jardim
    if (!estaNoJardim()) {
        std::cout << "O jardineiro nao esta no jardim.\n";
        return;
    }

    // 2. Verificar a QUOTA de colheitas (Decremento)
    // Usa o metodo que ja tens: return colheitasTurno > 0;
    if (!podeColher()) {
        std::cout << "Ja atingiste o limite de " << Settings::Jardineiro::max_colheitas
                  << " colheitas por turno! Avanca o tempo para recarregar.\n";
        return;
    }

    // 3. Obter a planta
    Posicao* p = jardim.getPosicao(posLinha, posColuna);
    Planta* planta = p->getPlanta();

    if (planta == nullptr) {
        std::cout << "Nao ha planta nenhuma aqui para colher.\n";
        return;
    }

    // 4. Verificar se é Erva Daninha (nao gasta quota)
    std::string beleza = planta->getBeleza();
    if (beleza == "Feia" || beleza == "feia") {
        std::cout << "Nao deves colher Ervas Daninhas a mao! Usa a Tesoura e avanca o tempo.\n";
        return;
    }

    // 5. AÇÃO DE COLHEITA (Sucesso)
    // Decrementa o contador: colheitasTurno--
    registarColheita();

    std::cout << "Colheste uma planta " << beleza << " (" << planta->getChar() << ")!\n";
    std::cout << "Restam " << this->colheitasTurno << " colheitas neste turno.\n";

    // Remove do jardim e limpa memória
    delete p->removePlanta();
}