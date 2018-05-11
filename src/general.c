#include <stdio.h>
#include "pente_types.h"
#include "general.h"
#define MAX 20


void Pente() {
    int pente[MAX][MAX];
    int i;
    game_info_t *head = NULL;

    clear_board(pente);

    printf("\n¿Desea cargar algun juego? [Si = 0/ No = 1]\n> "); //Igual a resume playing
    scanf("%d", &i);
    if (i == 0)
        load_plays(pente, &head);
    coordinates(pente, &head); //funcion encargada de la parte funcional del juego
}

void clear_board(int pente[MAX][MAX]) {
    memset(pente, 0, sizeof(int) * MAX * MAX);
}

void board(int pente[MAX][MAX], int x, int y, int jugador) {
    pente[y][x] = jugador;
}

void print(int pente[MAX][MAX])  {
    int i, j;
    printf("    ");
    for (i = 0; i < MAX; i++)
    {
        printf(" %d ", i);
    }
    printf("\n");
    for (i = 0; i < MAX; i++)
    {
        printf(" %d |", i);
        for (j = 0; j < MAX; j++)
        {
            printf(" %d|", pente[i][j]);
        }
        printf("\n");
    }
}

void pause() {
    printf("\n\n\t<Pulsee ENTER para continuar...>\n");
    while (getchar() != '\n');
    system("clear");
}

void print_prueba(plays_t *head){
    while (head != NULL) {
        printf("Nodo %p\n", head);
        printf("  sig: %p\n", head->sig);
        printf("X = %d, Y = %d\n", head->coor_x, head->coor_y);
        head = head->sig;
    }       
}

int valid_position(int pente[MAX][MAX], int x, int y) {
    return valid_range(x, y) && pente[y][x] != VAL1 && pente[y][x] != VAL2;
}
