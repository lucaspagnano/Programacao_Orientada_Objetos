#include "../../include/Comandos/Compra.h"
#include "../../include/Core/Simulador.h"
#include "../../include/Items/Regador.h"
#include "../../include/Items/Adubo.h"
#include "../../include/Items/Tesoura.h"
#include "../../include/Items/FerramentaZ.h"
#include <iostream>

Compra::Compra(const std::vector<std::string>& args) {
    if (args.size() != 1) {
        std::cout << "Erro: Sintaxe 'compra <tipo>' (g=regador, a=adubo, t=tesoura, z=ferramentaZ).\n";
        valido = false;
        return;
    }
    tipo = args[0];
    valido = true;
}
bool Compra::executa(Simulador& s) {
    if (!valido) return false;
    Ferramenta* f = nullptr;
    if (tipo == "g") f = new Regador();
    else if (tipo == "a") f = new Adubo();
    else if (tipo == "t") f = new Tesoura();
    else if (tipo == "z") f = new FerramentaZ();
    else { std::cout << "Erro: Tipo de ferramenta '" << tipo << "' desconhecido.\n"; return false; }
    s.getJardineiro()->compraFerramenta(f);
    return true;
}