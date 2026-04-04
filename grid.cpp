#include "grid.hpp"
#include "rules.hpp"
#include <fstream>
#include <iostream>
#include <omp.h>

Grid *clone_grid(const Grid *original) {
    if (!original) return nullptr;

    Grid *novo = new Grid;
    novo->n = original->n;
    novo->L = original->L;
    
    int n = original->n;
    novo->cells = new int*[n];

    // Cópia profunda em paralelo garantindo tabuleiros privados para cada branch
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        novo->cells[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            novo->cells[i][j] = original->cells[i][j];
        }
    }

    return novo;
}

int count_empty_cells(const Grid *g) {
    if (!g) return 0;
    
    int zeros = 0;
    int n = g->n;

    // Cláusula reduction junta as somas parciais de forma thread-safe
    #pragma omp parallel for collapse(2) reduction(+:zeros)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g->cells[i][j] == 0) {
                zeros++;
            }
        }
    }

    return zeros;
}

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


bool abortar = false;

#pragma omp parallel for collapse(2) shared(abortar)
for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
        // Verifica se outra thread já sinalizou o erro
        if (abortar) continue; 

        if (cells[i][j] > 0 && !is_valid(g, i, j, cells[i][j])) {
            abortar = true; // Não precisa de 'critical' se for apenas um booleano simples
        }
    }
}

    // O 'delete' deve ser feito APENAS FORA do bloco paralelo
    if (abortar) {
        std::cerr << "Não tem solução" << std::endl;
        for (int k = 0; k < n; ++k) delete[] cells[k];
        delete[] cells;
        delete g;
        return nullptr;
    }
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
