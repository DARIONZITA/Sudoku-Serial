#ifndef GRID_H
#define GRID_H

struct Grid {
    int n;      // tamanho do tabuleiro (ex.: 9)
    int L;      // tamanho do bloco (ex.: 3)
    int **cells;
};

// Contrato fixo (Dário): API publica do tabuleiro.
Grid *load_grid(const char *filename);
void free_grid(Grid *g);
int get_cell(Grid *g, int row, int col);
void set_cell(Grid *g, int row, int col, int value);
void print_grid(Grid *g);

#endif
