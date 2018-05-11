#ifndef FILASH
#define FILASH

#include "pente_types.h"

int count(int pente[MAX][MAX], int jugador);
int get_moves(int pente[MAX][MAX], int x, int y, int jugador);
int follow(int pente[MAX][MAX], int token_value, int x, int y, int dx, int dy, int level);

#endif
