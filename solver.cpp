/*#include "solver.hpp"

#include "rules.hpp"

int solve(Grid *g) {
    int row, col;
    int encontrou_vazio = 0;

    for(row = 0; row < g->n; row++) {
        for(col = 0; col < g->n; col++) {
            if(get_cell(g, row, col) == 0) {
                encontrou_vazio = 1;
                break;
            }
        }
        if(encontrou_vazio) break;
    }
    if(!encontrou_vazio) {
        return 1; 
    }
    for(int num = 1; num <= g->n; num++) {
        if (is_valid(g, row, col, num)) {
            set_cell(g, row, col, num);
            if (solve(g)) {
                return 1; 
            }
            set_cell(g, row, col, 0);
        }
    }
    return 0;
}*/
#include <omp.h>
#include "solver.hpp"
#include "rules.hpp"

// Adicionamos 'depth' para controlar a granularidade das tarefas
int solve_parallel(Grid *g, int depth) {
    int row, col;
    int encontrou_vazio = 0;

    // Busca a próxima célula vazia
    for(row = 0; row < g->n; row++) {
        for(col = 0; col < g->n; col++) {
            if(get_cell(g, row, col) == 0) {
                encontrou_vazio = 1;
                break;
            }
        }
        if(encontrou_vazio) break;
    }

    if(!encontrou_vazio) return 1; 

    int solution_found = 0;

    for(int num = 1; num <= g->n; num++) {
        if (is_valid(g, row, col, num)) {
            
            // Criamos tarefas apenas nos primeiros níveis (ex: depth < 2 ou 3)
            // para evitar overhead excessivo.
            if (depth < 2) { 
                #pragma omp task shared(solution_found) firstprivate(g, row, col, num, depth)
                {
                    // Cada tarefa precisa da sua própria cópia da grade para não haver conflito
                    Grid *copy_g = clone_grid(g); 
                    set_cell(copy_g, row, col, num);
                    
                    if (solve_parallel(copy_g, depth + 1)) {
                        #pragma omp atomic write
                        solution_found = 1;
                        // Aqui você precisaria de uma lógica para copiar a solução de volta
                    }
                    free_grid(copy_g);
                }
            } else {
                // Execução serial normal para níveis mais profundos
                set_cell(g, row, col, num);
                if (solve_parallel(g, depth + 1)) return 1;
                set_cell(g, row, col, 0);
            }
        }
        // Se alguma tarefa encontrou a solução, podemos parar
        #pragma omp flush(solution_found)
        if (solution_found) return 1;
    }
    
    #pragma omp taskwait
    return solution_found;
}

// No seu main, você deve iniciar a região paralela:
// #pragma omp parallel
// #pragma omp single
// solve_parallel(g, 0);
