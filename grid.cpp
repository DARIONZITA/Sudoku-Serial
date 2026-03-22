#include "grid.h"

Grid *load_grid(const char *filename) {
    (void)filename;
    // TODO(Dário): ler ficheiro, alocar memoria e preencher Grid.
    return nullptr;
}

void free_grid(Grid *g) {
    (void)g;
    // TODO(Dário): libertar memoria de cells e da struct Grid.
}

int get_cell(Grid *g, int row, int col) {
    (void)g;
    (void)row;
    (void)col;
    // TODO(Dário): devolver valor da celula com validacao de limites.
    return -1;
}

void set_cell(Grid *g, int row, int col, int value) {
    (void)g;
    (void)row;
    (void)col;
    (void)value;
    // TODO(Dário): escrever valor na celula com validacao de limites.
}

void print_grid(Grid *g) {
    (void)g;
    // TODO(Dário): imprimir tabuleiro em formato legivel.
}
