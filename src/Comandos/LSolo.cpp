#include "../../include/Comandos/LSolo.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Core/Jardim.h"   // <--- Faltava incluir
#include "../../include/Core/Posicao.h"  // <--- Faltava incluir
#include "../../include/Entidades/Planta.h" // Para mostrar detalhes da planta
#include "../../include/Items/Ferramenta.h" // Para mostrar detalhes da ferramenta
#include <iostream>
#include <sstream>

LSolo::LSolo(const std::vector<std::string>& args): raio(0)
{
    if (args.size() < 1 || args.size() > 2) {
        std::cout << "Erro: Comando 'lsolo' requer 1 ou 2 argumentos (lsolo <l><c> [n]).\n";
        this->valido = false;
        return;
    }

    if (args[0].length() != 2) {
        std::cout << "Erro: Coordenada '" << args[0] << "' invalida. Deve ter 2 letras (ex: df).\n";
        this->valido = false;
        return;
    }
    this->coord = args[0];

    if (args.size() == 2) {
        std::stringstream ss(args[1]);
        int n_raio;

        if (!(ss >> n_raio)) {
            std::cout << "Erro: 'lsolo [n]' - 'n' (raio) deve ser um numero inteiro.\n";
            this->valido = false;
            return;
        }

        if (n_raio < 0) {
            std::cout << "Erro: 'lsolo [n]' - 'n' (raio) nao pode ser negativo.\n";
            this->valido = false;
            return;
        }

        this->raio = n_raio;
    }

    this->valido = true;
    // std::cout << "DEBUG: Comando 'lsolo " << coord << " " << raio << "' validado.\n";
}

bool LSolo::executa(Simulador& s) {
    if (!this->valido) return false;

    if (!s.isJardimCriado()) {
        std::cout << "Erro: Nao pode listar. O jardim ainda nao foi criado.\n";
        return false;
    }

    Jardim* jardim = s.getJardim();

    // Converter a coordenada central (ex: "aa" -> 0, 0)
    int centroL = this->coord[0] - 'a';
    int centroC = this->coord[1] - 'a';

    std::cout << "--- Analise de Solo (Centro: " << coord << " | Raio: " << raio << ") ---\n";

    // Percorrer a área baseada no raio
    for (int l = centroL - raio; l <= centroL + raio; l++) {
        for (int c = centroC - raio; c <= centroC + raio; c++) {

            // Verifica se a coordenada existe no jardim
            if (jardim->isPosicaoValida(l, c)) {
                Posicao* p = jardim->getPosicao(l, c);

                // Formatar a coordenada para texto (ex: AA)
                char coordL = (char)('A' + l);
                char coordC = (char)('A' + c);

                std::cout << "[" << coordL << coordC << "] ";
                std::cout << "Agua: " << p->getAgua() << " | ";
                std::cout << "Nutri: " << p->getNutrientes();

                // Mostrar Planta se existir
                if (p->getPlanta() != nullptr) {
                    std::cout << " | Planta: " << p->getPlanta()->getBeleza()
                              << " (" << p->getPlanta()->getChar() << ")";
                } else {
                    std::cout << " | Planta: Nenhuma";
                }

                // Mostrar Ferramenta se existir
                if (p->getFerramenta() != nullptr) {
                    std::cout << " | Item: " << p->getFerramenta()->getNome();
                }

                std::cout << "\n";
            }
        }
    }
    std::cout << "--------------------------------------------------\n";

    return true;
}
