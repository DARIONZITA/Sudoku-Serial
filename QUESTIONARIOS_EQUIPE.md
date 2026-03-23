# Questionários da Equipe - Projeto Sudoku C++

## Objetivo
Garantir que todos do grupo tenham 100% de noção do projeto, não apenas do próprio módulo.

## Como usar este documento
- Cada pessoa responde ao seu questionário técnico.
- Depois, cada pessoa responde ao questionário de entendimento global.
- As respostas devem ser objetivas e com exemplos do código.
- Sempre que possível, indicar função e ficheiro relacionado.

## Regras de preenchimento
- Responder com base na implementação atual.
- Se algo não estiver implementado, explicar o plano.
- Não deixar respostas vagas como "funciona" ou "normal".
- Em cada resposta, incluir "Risco" e "Como testar" quando aplicável.

---

## Questionário 1 - Dário (Grid)
Responsável por: grid.h e grid.cpp

### A. Estrutura e memória
1. Como a estrutura Grid foi desenhada e por que os campos n, L e cells são suficientes?
2. Como a memória de cells é alocada e libertada?
3. Que estratégia foi usada para evitar memory leaks e double free?
4. O que acontece se load_grid falhar a meio da leitura?

### B. Leitura e consistência dos dados
5. Qual é o formato de entrada esperado no ficheiro?
6. Como validas que o tabuleiro lido é coerente (dimensão e valores)?
7. Como calculas L a partir de n e quais casos inválidos existem?
8. Que erro é retornado quando o ficheiro é inválido?

### C. API pública
9. Quais os contratos de get_cell e set_cell para índices fora de limite?
10. print_grid é apenas debug ou formato final de saída?
11. Que garantias o módulo Grid dá aos módulos Rules e Solver?
12. Que alterações futuras no Grid não podem quebrar os outros módulos?

### D. Testes mínimos esperados
13. Teste de carregamento válido.
14. Teste de carregamento inválido.
15. Teste de get/set dentro e fora dos limites.
16. Teste de free_grid em casos nulos e casos normais.

---

## Questionário 2 - Bernardo (Rules)
Responsável por: rules.h e rules.cpp

### A. Lógica de validação
1. O que significa exatamente is_valid(g, row, col, num)?
2. Como check_row, check_col e check_block se complementam?
3. Como garantes que num está no intervalo permitido?
4. Como lidas com células já preenchidas?

### B. Bloco do Sudoku
5. Como calculas o bloco de uma posição (row, col)?
6. Esse cálculo funciona para 4x4, 9x9 e 16x16?
7. Que pré-condições o módulo Rules assume sobre Grid?
8. Quais são os erros mais comuns nesta parte e como os evitaste?

### C. Integração com os outros módulos
9. Que funções de Grid são usadas diretamente por Rules?
10. O que acontece se get_cell devolver valor inesperado?
11. Como teu módulo ajuda o Solver a tomar decisões corretas?
12. Quais mudanças em Rules poderiam quebrar o Solver?

### D. Testes mínimos esperados
13. Número inválido (0, negativo, maior que n).
14. Conflito por linha.
15. Conflito por coluna.
16. Conflito por bloco.
17. Caso totalmente válido.

---
1. O que significa exatamente is_valid(g, row, col, num)?

is_valid verifica se é possível colocar o número num na posição (row, col) do tabuleiro g respeitando todas as regras do Sudoku. Retorna true se:

    O número está no intervalo válido [1, n]

    A posição está vazia (valor 0)

    O número não aparece na mesma linha

    O número não aparece na mesma coluna

    O número não aparece no mesmo bloco L×L

2. Como check_row, check_col e check_block se complementam?

As três funções verificam restrições ortogonais do Sudoku:

    check_row: Garante unicidade horizontal

    check_col: Garante unicidade vertical

    check_block: Garante unicidade no subquadrante

A combinação das três assegura que todas as regras do jogo são satisfeitas. Se qualquer uma falhar, o movimento é inválido.
3. Como garantes que num está no intervalo permitido?
cpp

if (num < 1 || num > n) {
    return false;
}

Onde n = L * L. Esta verificação é feita no início de is_valid, rejeitando imediatamente números fora do intervalo.
4. Como lidas com células já preenchidas?
cpp

if (board[row][col] != 0) {
    return false;
}

Qualquer tentativa de modificar uma célula já preenchida (valor diferente de 0) é imediatamente rejeitada. O Solver só chama is_valid para posições vazias, mas esta verificação serve como salvaguarda.
B. Bloco do Sudoku
5. Como calculas o bloco de uma posição (row, col)?
cpp

int block_row = (row / L) * L;
int block_col = (col / L) * L;

    (row / L) identifica o índice do bloco na vertical (0, 1, 2...)

    Multiplicando por L obtém a linha inicial do bloco

    O mesmo raciocínio para colunas

Exemplo para L=3, posição (4,5):

    block_row = (4/3)*3 = 1*3 = 3

    block_col = (5/3)*3 = 1*3 = 3

    Bloco começa em (3,3)

6. Esse cálculo funciona para 4x4, 9x9 e 16x16?

Sim, funciona para qualquer L entre 2 e 9:

    4x4 (L=2): (row/2)*2 dá blocos 2×2

    9x9 (L=3): (row/3)*3 dá blocos 3×3

    16x16 (L=4): (row/4)*4 dá blocos 4×4

O cálculo é genérico e independente do tamanho, desde que L seja fornecido corretamente.
7. Que pré-condições o módulo Rules assume sobre Grid?

    board é uma matriz n × n com n = L × L

    Valores válidos são 0 (vazio) ou [1, n]

    row e col estão dentro dos limites [0, n-1]

    L é um inteiro no intervalo [2, 9]

    O tabuleiro está consistente (não tem conflitos nas posições preenchidas)

8. Quais são os erros mais comuns nesta parte e como os evitaste?
Erro Comum	Como Evitei
Cálculo errado do bloco	Fórmula (row/L)*L com divisão inteira
Esquecer validação de intervalo	Verificação num < 1 || num > n no início
Modificar células preenchidas	if (board[row][col] != 0) return false;
Confundir L com n	Uso consistente: n = L*L para tamanho, L para blocos
Off-by-one nos loops	Loops de 0 a n-1 (exclusivo)
C. Integração com os outros módulos
9. Que funções de Grid são usadas diretamente por Rules?

Nesta implementação, Rules não usa funções de Grid separadas. O acesso é direto à matriz board:

    board[row][col] para leitura/escrita

    board[row][col] == num para comparações

Isso mantém o módulo Rules independente e mais eficiente.
10. O que acontece se get_cell devolver valor inesperado?

Como não usamos get_cell, não há esse problema. Se a matriz contiver valores inválidos (ex: -1, 10 em Sudoku 9x9), a validação pode falhar:

    Número negativo: num < 1 → rejeitado

    Número > n: num > n → rejeitado

    Valor 0: Tratado como vazio, permitido

11. Como teu módulo ajuda o Solver a tomar decisões corretas?

Rules fornece ao Solver:

    Validação determinística: Mesma entrada sempre mesma saída

    Feedback imediato: Se is_valid retorna false, o Solver tenta outro número

    Backtracking eficiente: Permite poda da árvore de busca

    Garantia de correção: Só aceita movimentos que respeitam regras

12. Quais mudanças em Rules poderiam quebrar o Solver?
Mudança	Impacto
Alterar validação de intervalo	Pode aceitar números inválidos ou rejeitar válidos
Modificar cálculo do bloco	Conflitos não detetados ou falsos positivos
Remover verificação de célula preenchida	Solver pode sobrescrever números fixos
Mudar assinatura das funções	Código do Solver não compila
Tornar funções não const	Pode causar modificações acidentais
D. Testes mínimos esperados
13. Número inválido (0, negativo, maior que n)
cpp

// Teste implementado em test_sudoku_4x4()
is_valid(board, 0, 1, 0, L)   → false  // zero
is_valid(board, 0, 1, 5, L)   → false  // > n (n=4)

14. Conflito por linha
cpp

// Teste implementado em test_sudoku_9x9()
// Linha 6: [1,7,5,9,3,4,2,0,0]
is_valid(board, 6, 7, 7, L)   → false  // 7 já na linha

15. Conflito por coluna
cpp

// Teste implementado em test_sudoku_9x9()
// Coluna 0 tem 1 na posição (6,0)
is_valid(board, 7, 0, 1, L)   → false  // 1 já na coluna

16. Conflito por bloco
cpp

// Teste implementado em test_sudoku_9x9()
// Bloco (6,0) contém 1,7,5,9,3,4,2
is_valid(board, 6, 1, 1, L)   → false  // 1 já no bloco

17. Caso totalmente válido
cpp

// Teste implementado em test_complete_valid_solution()
// Verifica todas as 81 posições da solução completa
// Resultado: A solução é VÁLIDA! ✓

Resumo de Validação
Componente	Status	Verificação
check_row	✅	Percorre linha, retorna false se encontra igual
check_col	✅	Percorre coluna, retorna false se encontra igual
check_block	✅	Cálculo (row/L)*L, varre L×L células
is_valid	✅	Combina as 3 + validação intervalo + célula vazia
Valores fora intervalo	✅	num < 1 || num > n → false
Posições preenchidas	✅	board[row][col] != 0 → false
Funciona com L=2,3,4	✅	Fórmula genérica

---
## Questionário 3 - William (Solver)
Responsável por: solver.h e solver.cpp

### A. Estratégia de resolução
1. Explica o algoritmo de backtracking usado no solve.
2. Como escolhes a próxima célula vazia?
3. Qual é a condição de paragem com sucesso?
4. Qual é a condição de retrocesso (backtrack)?

### B. Integração com Rules e Grid
5. Em que momento is_valid é chamado e por quê?
6. Como set_cell é usado para avançar e desfazer jogadas?
7. O que o Solver assume sobre o comportamento de is_valid?
8. O que acontece se o tabuleiro inicial já for inválido?

### C. Complexidade e robustez
9. Qual a complexidade no pior caso e impacto prático?
10. Que otimizações futuras podem ser adicionadas (ex.: MRV)?
11. Como garantir que não há recursão infinita?
12. Como o Solver comunica "sem solução"?

### D. Testes mínimos esperados
13. Sudoku simples resolvível.
14. Sudoku já resolvido.
15. Sudoku sem solução.
16. Sudoku com entrada inválida.

---

## Questionário 4 - Entendimento Global (todos respondem)
Cada membro deve responder sem consultar o colega.

1. Quais são as assinaturas públicas de Grid, Rules e Solver?
2. Descreve o fluxo completo desde main até imprimir a solução.
3. Onde podem ocorrer leaks de memória e como evitar?
4. Em que ordem os módulos devem ser chamados e por quê?
5. O que acontece se load_grid retornar nulo?
6. O que acontece se solve retornar 0?
7. Como validar rapidamente se uma alteração quebrou integração?
8. Que testes são obrigatórios antes de fazer merge?

---

## Questionário 5 - Revisão Cruzada (peer review)
Cada pessoa revisa o módulo de outro colega e responde:

1. O contrato público foi respeitado?
2. Há validações de entrada suficientes?
3. Há risco de crash por ponteiros nulos?
4. Há risco de acesso fora de limites?
5. Há risco de leak de memória?
6. O código está legível para manutenção?
7. Que melhoria imediata recomendas?

---

## Critério de "100% noção do projeto"
O grupo só fecha a entrega quando:
- Todos conseguem explicar o fluxo completo sem ler código.
- Todos sabem os contratos públicos dos 3 módulos.
- Todos sabem como compilar e testar o projeto completo.
- Todos conseguem apontar ao menos 2 riscos técnicos e como mitigá-los.

---

## Ata de reunião técnica (preencher em cada checkpoint)
Data:
Participantes:

### Decisões tomadas
- 

### Dúvidas em aberto
- 

### Próximos passos
- 

### Responsáveis e prazo
- 
