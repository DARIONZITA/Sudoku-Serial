#include "grid.hpp"
#include <fstream>
#include <iostream>

Grid *load_grid(const char *filename) {
    // TODO(Dário): ler ficheiro, alocar memoria e preencher Grid.
    std::ifstream file(filename);
    
    if (!file.is_open()) 
        std::cerr << "Error opening file: " << filename << std::endl;
    int  L;
    file >> L;
    if(L < 2 || L > 9) {
        std::cerr << "Invalid block size: " << L << std::endl;
        return nullptr;
    }
    int n = L * L;
    int **cells = new int*[n];
    for (int i = 0; i < n; ++i) {
        cells[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            if (!(file >> cells[i][j])) {
                std::cerr << "Error reading cell value at (" << i << ", " << j << ")" << std::endl;
                 for (int k = 0; k <= i; ++k) {
                    delete[] cells[k];
                }
                delete[] cells;
                return nullptr;
            }
        }
    }
    
    Grid *g = new Grid{n, L, cells};
    
    return g;
}

void free_grid(Grid *g) {
    // TODO(Dário): libertar memoria de cells e da struct Grid.
    for (int i = 0; i < g->n; ++i) {
        delete[] g->cells[i];
    }
    delete[] g->cells;
    delete g;
}

int get_cell(Grid *g, int row, int col) {
    // TODO(Dário): devolver valor da celula com validacao de limites.

    if (row < 0 || row >= g->n || col < 0 || col >= g->n) {
        std::cerr << "Invalid cell coordinates: (" << row << ", " << col << ")" << std::endl;
        return -1;
    }
    return g->cells[row][col];
}

void set_cell(Grid *g, int row, int col, int value) {
    // TODO(Dário): escrever valor na celula com validacao de limites.
    if (row < 0 || row >= g->n || col < 0 || col >= g->n) {
        std::cerr << "Invalid cell coordinates: (" << row << ", " << col << ")" << std::endl;
        return;
    }
    g->cells[row][col] = value;

}

void print_grid(Grid *g) {
    // TODO(Dário): imprimir tabuleiro em formato legivel.
    std::cout << "Grid (n=" << g->n << ", L=" << g->L << "):" << std::endl;
    for (int i = 0; i < g->n; ++i) {
        for (int j = 0; j < g->n; ++j) {
            std::cout << g->cells[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
