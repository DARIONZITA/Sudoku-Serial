
#ifndef RULES_H
#define RULES_H

#include <vector>

// Verifica se um número pode ser colocado em uma determinada posição
bool is_valid(std::vector<std::vector<int>>& board, int row, int col, int num, int L);

// Funções internas (declaradas para uso interno)
bool check_row(const std::vector<std::vector<int>>& board, int row, int num, int n);
bool check_col(const std::vector<std::vector<int>>& board, int col, int num, int n);
bool check_block(const std::vector<std::vector<int>>& board, int row, int col, int num, int L);

#endif