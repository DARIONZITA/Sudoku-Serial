
#ifndef RULES_H
#define RULES_H
#include "grid.hpp"
int is_valid(Grid *g, int row, int col, int num);
int check_row(Grid *g, int row, int num);
int check_col(Grid *g, int col, int num);
int check_block(Grid *g, int row, int col, int num);

#endif