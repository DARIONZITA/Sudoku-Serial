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
Responsável por: grid.hpp e grid.cpp

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
Responsável por: rules.hpp e rules.cpp

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

## Questionário 3 - William (Solver)
Responsável por: solver.hpp e solver.cpp

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
