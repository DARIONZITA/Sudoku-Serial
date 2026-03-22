#include "solver.h"

#include "rules.h"

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
}
