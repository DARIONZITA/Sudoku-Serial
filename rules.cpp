/* #include "rules.hpp"

int is_valid(Grid *g, int row, int col, int num) {
    // TODO(Bernardo): criar check_row, check_col e check_block.
    // TODO(Bernardo): is_valid deve combinar as 3 validacoes.
    // Temporarily clear the cell being validated so the checks don't
    // detect the cell's own value as a duplicate (useful when validating
    // an already-filled initial grid).
    int orig = g->cells[row][col];
    g->cells[row][col] = 0;
    int ok = 1;
    if (!check_row(g, row, num)) ok = 0;
    if (!check_col(g, col, num)) ok = 0;
    if (!check_block(g, row, col, num)) ok = 0;
    g->cells[row][col] = orig;
    return ok;
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
 */
#include "rules.hpp"
#include <omp.h>

int is_valid(Grid *g, int row, int col, int num) {
    // Salvamos o original para o caso de validação de grid inicial
    int orig = g->cells[row][col];
    g->cells[row][col] = 0;

    int r_ok = 1, c_ok = 1, b_ok = 1;

    // Usamos um threshold (limiar). Para grids pequenos (n < 9), 
    // o overhead de criar threads supera o ganho.
    #pragma omp parallel sections if(g->n >= 9)
    {
        #pragma omp section
        {
            r_ok = check_row(g, row, num);
        }

        #pragma omp section
        {
            c_ok = check_col(g, col, num);
        }

        #pragma omp section
        {
            b_ok = check_block(g, row, col, num);
        }
    }

    g->cells[row][col] = orig;

    // Se qualquer uma das seções retornou 0 (inválido), o resultado final é 0.
    return (r_ok && c_ok && b_ok);
}

int check_row(Grid *g, int row, int num) {
    for (int i = 0; i < g->n; i++) {
        if (g->cells[row][i] == num) return 0;
    }
    return 1;
}

int check_col(Grid *g, int col, int num) {
    for (int i = 0; i < g->n; i++) {
        if (g->cells[i][col] == num) return 0;
    }
    return 1;
}

int check_block(Grid *g, int row, int col, int num) {
    int L = g->L;
    int start_row = (row / L) * L;
    int start_col = (col / L) * L;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            if (g->cells[start_row + i][start_col + j] == num) return 0;
        }
    }
    return 1;
}