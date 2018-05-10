/*
 * autor: cristobal liendo i
 * fecha: Tue 24 Apr 2018 06:48:32 PM CDT
 * descripcion: 
*/

#include <stdio.h>

#define MAX 10

void print_tablero(int tablero[MAX][MAX]);
void check_winner(int tablero[MAX][MAX], int aux[MAX][MAX], int x, int y, int level, int dir);

int contador = 0;

int follow(int tablero[MAX][MAX], int ficha, int x, int y, int dx, int dy, int level);
int get_moves(int tablero[MAX][MAX], int x, int y);

int main() {
    int tablero[MAX][MAX];
    int aux[MAX][MAX];

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            tablero[i][j] = 0;
            aux[i][j] = 0;
        }
    }

    tablero[1][1] = 1;
    tablero[1][3] = 1;
    tablero[2][1] = 1;
    tablero[2][4] = 1;
    tablero[3][1] = 1;
    tablero[3][5] = 1;
    tablero[4][1] = 1;
    tablero[4][2] = 1;
    tablero[4][3] = 1;
    tablero[4][4] = 1;
    tablero[4][6] = 1;
    tablero[5][4] = 1;
    tablero[6][4] = 1;
    tablero[7][4] = 1;

    print_tablero(tablero);

    for (int y = 0; y < MAX; y++)
        for (int x = 0; x < MAX; x++)
            contador += get_moves(tablero, x, y);

    printf("contador: %d\n", contador);

    return 0;
}

void print_tablero(int tablero[MAX][MAX]) {
    for (int y = 0; y < MAX; y++) {
        for (int x = 0; x < MAX; x++) {
            if (x % 9 == 0)
                printf("|");

            if (tablero[y][x] == 1)
                printf("O");
            else if (tablero[y][x] == -1)
                printf("X");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int follow(int tablero[MAX][MAX], int ficha, int x, int y, int dx, int dy, int level) {
    if (x < 0 || x >= MAX || y < 0 || y >= MAX)
        return level;

    if (tablero[y][x] != ficha || level == 5)
        return level;

    level = follow(tablero, ficha, x + dx, y + dy, dx, dy, level + 1);

    return level;
}

int get_moves(int tablero[MAX][MAX], int x, int y) {
    int total = 0, actual, ficha;
    int dirs[4][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}};

    ficha = tablero[y][x];
    if (ficha != 1 && ficha != -1)
        return 0;


    for (int i = 0; i < 4; i++) {
        actual = follow(tablero, ficha, x, y, dirs[i][0], dirs[i][1], 0);

        if (actual == 4 || actual == 5)
            total++;
    }

    return total;
}

void check_winner_n(int tablero[MAX][MAX],int aux[MAX][MAX], int x, int y) {
    int tempx, tempy;
    int level;

    tempx = x;
    tempy = y;

    while(aux[++tempx][y] && tablero[tempx][y]) {
        aux[tempx][y] = 1;
        level++;
    }

    if(level == 3){
        contador++;
    }
}
