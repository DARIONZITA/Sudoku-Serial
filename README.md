# Projeto Sudoku em C++

## Objetivo
Construir um resolvedor de Sudoku modular, com 3 módulos independentes (Grid, Rules e Solver), para que cada pessoa trabalhe em paralelo sem bloquear as outras.

## Arquitetura
- Entrada e integração: [main.cpp](main.cpp)
- Módulo de tabuleiro: [grid.hpp](grid.hpp) e [grid.cpp](grid.cpp)
- Módulo de validação: [rules.hpp](rules.hpp) e [rules.cpp](rules.cpp)
- Módulo de resolução: [solver.hpp](solver.hpp) e [solver.cpp](solver.cpp)

## Princípio principal
Trabalhar por contrato.
Cada módulo expõe assinaturas estáveis no .hpp, e a implementação no .cpp pode evoluir sem quebrar os outros.

## Contratos fixos

Grid (Dário)
- load_grid(filename)
- free_grid(g)
- get_cell(g, row, col)
- set_cell(g, row, col, value)
- print_grid(g)

Rules (Bernardo)
- is_valid(g, row, col, num)

Solver (William)
- solve(g)

Importante:
- Não mudar nomes de funções nem parâmetros sem acordo do grupo.
- Não editar ficheiros de outro módulo.

## O que cada pessoa deve fazer

### Dário (Grid)
Responsável por estrutura e acesso ao tabuleiro.

Checklist:
- [ ] Implementar leitura do ficheiro em load_grid
- [ ] Alocar memória dinâmica para cells
- [ ] Inicializar n e L corretamente
- [ ] Validar limites em get_cell e set_cell
- [ ] Implementar free_grid sem leaks
- [ ] Implementar print_grid legível para debug

Entregável:
- [grid.cpp](grid.cpp) funcional, mantendo o contrato de [grid.hpp](grid.hpp)

### Bernardo (Rules)
Responsável pelas regras do Sudoku.

Checklist:
- [ ] Criar funções internas check_row
- [ ] Criar funções internas check_col
- [ ] Criar funções internas check_block
- [ ] Implementar is_valid combinando as 3 validações
- [ ] Garantir que valores fora do intervalo são rejeitados

Entregável:
- [rules.cpp](rules.cpp) funcional, mantendo o contrato de [rules.hpp](rules.hpp)

### William (Solver)
Responsável pelo backtracking.

Checklist:
- [ ] Encontrar próxima célula vazia
- [ ] Testar candidatos de 1 até n
- [ ] Usar is_valid para validar jogada
- [ ] Usar set_cell para avançar e recuar
- [ ] Retornar sucesso quando não houver células vazias

Entregável:
- [solver.cpp](solver.cpp) funcional, mantendo o contrato de [solver.hpp](solver.hpp)

### Integração final (grupo)
Responsável por ligar tudo no fluxo principal.

Checklist:
- [ ] Em [main.cpp](main.cpp), carregar grid a partir de argumento
- [ ] Chamar solve
- [ ] Imprimir solução quando existir
- [ ] Mostrar mensagem de sem solução quando necessário
- [ ] Libertar memória no final

## Fluxo esperado em main
1. Carregar tabuleiro
2. Resolver
3. Imprimir resultado
4. Libertar recursos

## Como compilar
Comando direto:
- g++ main.cpp grid.cpp rules.cpp solver.cpp -o sudoku

Ou via Makefile:
- make

## Regras de colaboração
- Cada pessoa trabalha no seu módulo
- Commits pequenos e frequentes
- Antes de merge, compilar o projeto completo
- Se precisar mudar contrato, discutir primeiro

## Critério de concluído
O projeto está concluído quando:
- Os 3 módulos estão implementados
- O executável compila sem erros
- Um Sudoku válido de entrada é resolvido corretamente
- Não há vazamentos de memória na execução normal
