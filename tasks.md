# Tarefas - Parte 2: Implementação OpenMP (sudoku-omp)

Este documento divide as tarefas da segunda fase do projeto (paralelização com OpenMP) entre os membros do grupo. **O objetivo é que os três membros escrevam diretivas OpenMP e trabalhem ativamente com paralelização**, em vez de concentrar o OpenMP apenas numa só pessoa. Cada um aplicará conceitos diferentes do OpenMP no seu próprio módulo.

Os três devem desenvolver no novo ficheiro principal `sudoku-omp.c` ou `sudoku-omp.cpp`, mas com responsabilidades perfeitamente divididas na paralelização.

---

## 🙋‍♂️ Dário: Paralelização da Base (Grid) e Infraestrutura OpenMP
**Foco:** Paralelização de loops, alocação de memória privada por thread (cópia de tabuleiros) e medição de tempo (`omp_get_wtime`).

**Checklist (OpenMP & Grid):**
- [X] Implementar a cópia profunda do tabuleiro (Grid) em paralelo (`#pragma omp parallel for`), já que a pesquisa paralela precisará de tabuleiros isolados por *thread/task* para não haver colisões de escrita.
- [X] Paralelizar funções utilitárias pesadas (ex: procura de todas as células vazias iniciais com `#pragma omp parallel for` e cláusulas `reduction` ou preenchimento de índices).
- [X] Integrar no `main` as funções de tempo globais: `#include <omp.h>` e `omp_get_wtime()`, garantindo que o tempo vá para `stderr` (`fprintf(stderr, "%.1fs\n", tempo);`) e os resultados do Sudoku para `stdout`.
- [X] Modificar o `Makefile` para usar `-fopenmp`.

---

## 🙋‍♂️ Bernardo: Paralelização das Regras e Validações Simultâneas
**Foco:** Diretivas de secção (`sections`), paralelismo estruturado e thread-safety.

**Checklist (OpenMP & Rules):**
- [ ] Analisar o módulo "Rules": Como validar o estado atual usando múltiplas *threads*?
- [ ] Paralelizar a verificação (`is_valid`) do Sudoku utilizando diretivas de seções (`#pragma omp parallel sections` e `#pragma omp section`).
  - Uma *thread* pode validar a linha correspondente em paralelo.
  - Outra *thread* valida a coluna.
  - Outra *thread* valida o bloco 3x3 (ou NxN).
- [ ] Assegurar a sincronização adequada: A função deve retornar que o movimento é inválido caso **qualquer uma** das secções detete um erro (usando variáveis com `#pragma omp atomic` ou `reduction`).
- [ ] Analisar *overhead*: Fazer com que o código escolha entre a verificação paralela ou sequencial com base num limiar (`if` na diretiva pragma) para não perder desempenho.

---

## 🙋‍♂️ William: Paralelização do Solver (Backtracking com Tasks OpenMP)
**Foco:** Tasking (`#pragma omp task`), sincronização (`taskwait`), balanceamento e *early exit* (cancelamento).

**Checklist (OpenMP & Solver):**
- [ ] Transformar o DFS/Backtracking sequencial numa árvore paralela com `Tasks`.
- [ ] **Integração com o módulo Grid (Dário):** 
  - Utilizar a função `clone_grid` do Dário sempre que criar uma nova *task* de ramificação (cada *task* precisa do seu próprio tabuleiro para não haver colisões). Não esquecer o `free_grid` no fim!
  - **Utilizar a função `count_empty_cells` do Dário** como condição de paragem: se retornar `0`, significa que o tabuleiro inteiro já não tem espaços vazios, logo a tua *thread* encontrou a solução final e deve sinalizar as outras para pararem.
- [ ] Substituir loops de pesquisa (tentar dígitos de 1 até n) por `#pragma omp task`. Caso a célula precise de testar 9 números diferentes, gerar tarefas independentes para cada dígito válido.
- [ ] Sincronizar as *tasks* geradas no ponto certo usando `#pragma omp taskwait`.
- [ ] Tratar de um dos maiores desafios em OpenMP: **Cancelamento / Paragem Antecipada**. Quando uma *task* (ou *thread*) encontra a solução do Sudoku, deve avisar todas as outras *threads* para pararem de pesquisar ou cancelar ramificações inúteis. Usar variáveis partilhadas atómicas como flag de paragem (`#pragma omp flush` ou `#pragma omp atomic read/write`).
- [ ] Lidar com o balanceamento de carga garantindo que não cria excesso de tarefas (ex:. condicionando o `omp task` a apenas `depth < LIMIT`).

---

## 🔄 Reunião de Integração e Testes de Escalabilidade
Todo o grupo deve reunir-se para:
- [ ] Correr o programa manipulando `OMP_NUM_THREADS` (ex: `1`, `2`, `4`, `8`).
- [ ] Avaliar a escalabilidade. Garantam que os vossos ganhos de tempo num PC multicore são consistentes com a teoria, ajustando a paralelização nas Regras ou no Solver caso o programa fique mais lento com mais *threads*.
