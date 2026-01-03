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
    //std::cout << "DEBUG: Jardineiro criado.\n";
}

Jardineiro::~Jardineiro() {
    if (ferramentaNaMao != nullptr) {
        delete ferramentaNaMao;
    }
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
    //std::cout << "Jardineiro entrou em (" << l << ", " << c << ")\n";
}

void Jardineiro::sai() {
    noJardim = false;
    posLinha = -1;
    posColuna = -1;
    registarEntradaSaida();
    //std::cout << "Jardineiro saiu do jardim.\n";
}

void Jardineiro::move(char direcao) {
    if (direcao == 'c') posLinha--;
    else if (direcao == 'b') posLinha++;
    else if (direcao == 'e') posColuna--;
    else if (direcao == 'd') posColuna++;
}

void Jardineiro::apanhaFerramenta(Ferramenta* f) {
    if (f == nullptr) return;

    if (ferramentaNaMao == nullptr) {
        ferramentaNaMao = f;
        std::cout << "Jardineiro apanhou " << f->getNome() << " (ID: " << f->getNumSerie() << ") e ficou com ela na mao.\n";
    } else {
        ferramentasTransportadas.push_back(f);
        std::cout << "Jardineiro guardou " << f->getNome() << " (ID: " << f->getNumSerie() << ") na mochila.\n";
    }
}

Ferramenta* Jardineiro::getFerramentaNaMao() {
    return ferramentaNaMao;
}

void Jardineiro::usarFerramenta(Jardim& jardim) {
    if (!noJardim || ferramentaNaMao == nullptr) {
        return;
    }

    std::cout << "Jardineiro esta usando " << ferramentaNaMao->getNome() << "\n";

    ferramentaNaMao->usar(jardim, posLinha, posColuna);

    if (ferramentaNaMao->deveQuebrar()) {
        std::cout << "A ferramenta " << ferramentaNaMao->getNome()
                  << " (ID: " << ferramentaNaMao->getNumSerie() << ") quebrou/acabou e foi deitada fora\n";

        delete ferramentaNaMao;
        ferramentaNaMao = nullptr;
    }
}

void Jardineiro::listarFerramentas() const {
    std::cout << "--- Inventario do Jardineiro ---\n";
    if (ferramentaNaMao != nullptr) {
        std::cout << "NA MAO: " << "\n    " << ferramentaNaMao->getNome() << " (ID: " << ferramentaNaMao->getNumSerie() << ")\n";
    } else {
        std::cout << "NA MAO: \n    (vazio)\n";
    }

    std::cout << "MOCHILA:\n";
    if (ferramentasTransportadas.empty()) {
        std::cout << "    (vazia)\n";
    } else {
        for (Ferramenta* f : ferramentasTransportadas) {
            std::cout << "    " << f->getNome() << " (ID: " << f->getNumSerie() << ")\n";
        }
    }
    std::cout << "-------------------------------- \n";
}

void Jardineiro::largaFerramenta() {
    if (ferramentaNaMao == nullptr) {
        std::cout << "Nao tens nenhuma ferramenta na mao para largar.\n";
        return;
    }

    ferramentasTransportadas.push_back(ferramentaNaMao);
    std::cout << ferramentaNaMao->getNome() << " guardada/o na mochila.\n";

    ferramentaNaMao = nullptr;
}

void Jardineiro::pegaFerramenta(int numSerie) {
    auto it = std::find_if(ferramentasTransportadas.begin(), ferramentasTransportadas.end(),
        [numSerie](Ferramenta* f) { return f->getNumSerie() == numSerie; });

    if (it == ferramentasTransportadas.end()) {
        std::cout << "Nao existe ferramenta com ID " << numSerie << " na mochila.\n";
        return;
    }

    Ferramenta* novaFerramenta = *it;

    ferramentasTransportadas.erase(it);

    if (ferramentaNaMao != nullptr) {
        std::cout << ferramentaNaMao->getNome() << "guardada/o na mochila.\n";
        ferramentasTransportadas.push_back(ferramentaNaMao);
    }

    ferramentaNaMao = novaFerramenta;

    std::cout << "Pegou em " << ferramentaNaMao->getNome() << " (ID: " << numSerie << ").\n";
}

void Jardineiro::compraFerramenta(Ferramenta* f) {
    if (f == nullptr) return;

    ferramentasTransportadas.push_back(f);

    std::cout << "O Jardineiro comprou " << f->getNome()
              << ". Total de itens: " << ferramentasTransportadas.size() << "\n";
}

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
    if (!estaNoJardim()) {
        std::cout << "O jardineiro ainda nao esta no jardim.\n";
        return;
    }

    if (!podeColher()) {
        std::cout << "Ja atingiu limite de " << Settings::Jardineiro::max_colheitas
                  << " colheitas por turno. Avanca o tempo para recarregar.\n";
        return;
    }

    Posicao* p = jardim.getPosicao(posLinha, posColuna);
    Planta* planta = p->getPlanta();

    if (planta == nullptr) {
        std::cout << "Nao ha planta nenhuma aqui para colher.\n";
        return;
    }

    std::string beleza = planta->getBeleza();
    if (beleza == "Feia" || beleza == "feia") {
        std::cout << "Nao deves colher Ervas Daninhas a mao. Pegue a Tesoura e avanca o tempo.\n";
        return;
    }

    registarColheita();

    std::cout << "Planta colhida: " << beleza << " (" << planta->getChar() << ").\n";
    std::cout << "Restam " << this->colheitasTurno << " colheitas neste turno.\n";

    delete p->removePlanta();
}