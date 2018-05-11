#ifndef GENERALH
#define GENERALH

void Pente();
void clear_board(int pente[MAX][MAX]);
void board(int pente[MAX][MAX], int x, int y, int jugador);
void print(int pente[MAX][MAX]);
void pause();
void print_prueba(plays_t *head);
int valid_position(int pente[MAX][MAX], int x, int y);

#endif
