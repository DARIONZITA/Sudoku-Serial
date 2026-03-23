#include "rules.hpp"

int is_valid(Grid *g, int row, int col, int num) {
    // TODO(Bernardo): criar check_row, check_col e check_block.
    // TODO(Bernardo): is_valid deve combinar as 3 validacoes.
    if (!check_row(g, row, num)) {
        return 0;
    }
    if (!check_col(g, col, num)) {
        return 0;
    }
    if (!check_block(g, row, col, num)) {
        return 0;
    }
    return 1;
}

int check_row(Grid *g, int row, int num) {
    // TODO(Bernardo): verificar se num ja existe na linha row.
    for (int i = 0; i < g->n; i++)
    {
        if (g->cells[row][i] == num)
            return 0;
    }
    
    return 1;
}

int check_col(Grid *g, int col, int num) {
    // TODO(Bernardo): verificar se num ja existe na coluna col.
    for (int i = 0; i < g->n; i++)
    {
        if (g->cells[i][col] == num)
            return 0;
    }
    return 1;
}

int check_block(Grid *g, int row, int col, int num) {
    // verificar se num ja existe no bloco que contem a celula (row,col).
    int L = g->L;
    int start_row = (row / L) * L;
    int start_col = (col / L) * L;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            if (g->cells[start_row + i][start_col + j] == num)
                return 0;
        }
    }

    return 1;
}

