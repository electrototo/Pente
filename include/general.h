#ifndef GENERALH
#define GENERALH

void clear_board(int **pente);
void board(int **pente, int x, int y, int jugador);
void print(int **pente);
void print_prueba(plays_t *head);
int valid_position(int **pente, int x, int y);

#endif
