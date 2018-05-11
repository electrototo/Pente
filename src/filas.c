#include <stdio.h>

#include "pente_types.h"
#include "filas.h"

int count(int **pente, int jugador) {
    int x, y, temp = 0;
    for (y = 0; y < PENTEMAX; y++)
        for (x = 0; x < PENTEMAX; x++)
            if ((get_moves(pente, x, y, jugador)) == -1)
                return -1;
            else
                temp += get_moves(pente, x, y, jugador);

    return temp;
}

int follow(int **pente, int token_value, int x, int y, int dx, int dy, int level) {
    if (!valid_range(x, y))
        return level;

    if (pente[y][x] != token_value || level == 5)
        return level;

    level = follow(pente, token_value, x + dx, y + dy, dx, dy, level + 1);

    return level;
}

//get_moves regresa 1 para una fila de 4, 0 si no hay filas y -1 para una fila de 5
int get_moves(int **pente, int x, int y, int jugador) {
    int total = 0, actual, token_value;

    token_value = pente[y][x];

    if (token_value != 1 && token_value != 2)
        return 0;

    int directions[4][2] = {
        {1, 0}, {1, 1},
        {0, 1}, {-1, 1}
    };

    for (int i = 0; i < 4; i++) {
        actual = follow(pente, jugador, x, y, directions[i][0], directions[i][1], 0);

        if (actual == 4)
            total++;

        if (actual == 5)
            return -1;
    }

    return total;
}
