#ifndef FILASH
#define FILASH

#include "pente_types.h"

int count(int **pente, int jugador);
int get_moves(int **pente, int x, int y, int jugador);
int follow(int **pente, int token_value, int x, int y, int dx, int dy, int level);

#endif
