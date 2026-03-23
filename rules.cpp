
#include "rules.h"
#include <vector>

using namespace std;

// Verifica se o número já existe na linha
bool check_row(const vector<vector<int>>& board, int row, int num, int n) {
    for (int col = 0; col < n; col++) {
        if (board[row][col] == num) {
            return false; // Número já existe na linha
        }
    }
    return true; // Número não encontrado na linha
}

// Verifica se o número já existe na coluna
bool check_col(const vector<vector<int>>& board, int col, int num, int n) {
    for (int row = 0; row < n; row++) {
        if (board[row][col] == num) {
            return false; // Número já existe na coluna
        }
    }
    return true; // Número não encontrado na coluna
}

// Verifica se o número já existe no bloco LxL
bool check_block(const vector<vector<int>>& board, int row, int col, int num, int L) {
    // Calcula o canto superior esquerdo do bloco
    int block_row = (row / L) * L;
    int block_col = (col / L) * L;
    
    // Verifica todo o bloco LxL
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            if (board[block_row + i][block_col + j] == num) {
                return false; // Número já existe no bloco
            }
        }
    }
    return true; // Número não encontrado no bloco
}

// Combina as três verificações para validar se um número pode ser colocado
// em uma determinada posição
bool is_valid(vector<vector<int>>& board, int row, int col, int num, int L) {
    int n = L * L; // n = L^2, tamanho total do tabuleiro
    
    // Validação do intervalo do número
    if (num < 1 || num > n) {
        return false; // Número fora do intervalo válido
    }
    
    // Verifica se a posição já está preenchida
    if (board[row][col] != 0) {
        return false; // Posição já ocupada
    }
    
    // Verifica as três regras do Sudoku
    bool row_valid = check_row(board, row, num, n);
    bool col_valid = check_col(board, col, num, n);
    bool block_valid = check_block(board, row, col, num, L);
    
    // Retorna verdadeiro apenas se todas as três validações forem bem-sucedidas
    return (row_valid && col_valid && block_valid);
}