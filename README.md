# 🌿 Simulador de Jardim - POO

> **Unidade Curricular:** Programação Orientada a Objetos (POO)  
> **Instituição:** ISEC - Instituto Superior de Engenharia de Coimbra  
> **Linguagem:** C++  

## 📖 Visão Geral

Este projeto consiste num **Simulador de Jardim** baseado em consola. O simulador gere um ecossistema retangular onde coexistem solo com propriedades variáveis, diversas espécies de plantas, ferramentas e um jardineiro controlado pelo utilizador.

A simulação não ocorre em tempo real, mas sim através de **instantes** (turnos). O tempo avança apenas por ordem do utilizador, momento em que as plantas crescem, reproduzem-se ou morrem, e as ferramentas sofrem desgaste.

## ⚙️ Funcionalidades e Regras

### 🗺️ O Jardim
**Grelha:** O jardim é uma área retangular (máximo 26x26) representada por caracteres na consola.
**Solo:** Cada posição da grelha possui níveis independentes de **Água** e **Nutrientes**.
**Visualização:** O sistema de "renderização" dá prioridade de visualização na ordem: Jardineiro > Planta > Ferramenta.

### 🌱 As Plantas
As plantas interagem com o solo e possuem ciclos de vida específicos. Existem 4 espécies implementadas:

1.  **Cato (`c`):** Beleza neutra. Absorve muita água. Morre por excesso de água ou falta de nutrientes.
2.  **Roseira (`r`):** Planta bonita. Delicada, morre se ficar sem reservas ou se estiver rodeada de outras plantas.
3.  **Erva-daninha (`e`):** Planta feia. Invade posições vizinhas agressivamente, matando a planta que lá estiver.
4.  **Planta Exótica (`x`):** Espécie com comportamento único definido especificamente para esta implementação.

### 🛠️ As Ferramentas
O jardineiro pode encontrar ou comprar ferramentas. Cada ferramenta possui um número de série único.

1.  **Regador (`g`):** Adiciona água ao solo. Capacidade limitada. <br>
2.  **Pacote de Adubo (`a`):** Adiciona nutrientes ao solo. Descartável após uso. <br>
3.  **Tesoura de Poda (`t`):** Remove plantas consideradas "feias" na posição atual. <br>
4.  **FerramentaZ (`z`):** Ferramenta especial com funcionalidades exclusivas - Drone de Rega. <br>

---

## 💻 Detalhes Técnicos

** C++ Standard.
** Consola (CLI).
**Estruturas de Dados:** A gestão da grelha do jardim foi implementada sem recurso a contentores da biblioteca standard (ex: `std::vector` ou `std::list` não são usados para a matriz do solo), utilizando estruturas dinâmicas próprias[cite: 35].
**Configuração:** Todos os parâmetros de simulação (vida inicial, taxas de absorção, limites) são carregados através da classe `Settings`[cite: 55].

---

## ⌨️ Manual de Comandos

O simulador é controlado através de comandos de texto introduzidos na consola. Os comandos são validados quanto à sintaxe e coerência.

### 🕹️ Controlo da Simulação
| Comando | Descrição |
| :--- | :--- |
| `jardim <l> <c>` | Cria o jardim com `l` linhas e `c` colunas. **Obrigatório ser o 1º comando**. |
| `avanca [n]` | Avança `n` instantes na simulação (default: 1). |
| `executa <nome>` | Executa uma lista de comandos a partir de um ficheiro de texto. |
| `grava <nome>` | Guarda o estado atual do jardim em memória. |
| `recupera <nome>` | Recupera um estado do jardim guardado anteriormente. |
| `apaga <nome>` | Apaga uma gravação da memória. |
| `fim` | Termina a simulação e liberta recursos. |

### 🚶 Movimento e Jardineiro
| Comando | Descrição |
| :--- | :--- |
| `entra <l><c>` | Jardineiro entra no jardim na posição (linha, coluna). |
| `sai` | Jardineiro sai do jardim. |
| `e` / `d` / `c` / `b` | Move o jardineiro (Esquerda, Direita, Cima, Baixo). Limite de 10 movimentos por turno. |

### 🌿 Ações no Jardim
| Comando | Descrição |
| :--- | :--- |
| `colhe <l><c>` | Colhe a planta na posição indicada. Máx 5 por turno. |
| `planta <l><c> <t>`| Planta uma espécie (`c`, `r`, `e`, `x`) na posição indicada. Máx 2 por turno. |
| `compra <t>` | Compra uma ferramenta do tipo `g`, `a`, `t` ou `z`. |
| `pega <id>` | Coloca na mão a ferramenta com o número de série `id`. |
| `larga` | Larga a ferramenta que está atualmente na mão. |

### 📊 Consultas e Logs
| Comando | Descrição |
| :--- | :--- |
| `lplantas` | Lista todas as plantas vivas e os seus atributos. |
| `lplanta <l><c>` | Mostra detalhes da planta numa posição específica. |
| `larea` | Lista conteúdo e propriedades de todas as posições não vazias. |
| `lsolo <l><c> [n]`| Mostra detalhes do solo na posição (opcional: quadrado de raio `n`). |
| `lferr` | Lista as ferramentas na posse do jardineiro. |

---

### 📝 Notas de Compilação

Este projeto foi desenvolvido para ser compilado em ambiente C++.
Recomenda-se a utilização de um IDE como o **CLion** ou compilação via terminal garantindo suporte a C++11 ou superior.
