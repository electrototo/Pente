#ifndef GENERALH
#define GENERALH

void clear_board(int **pente, game_info_t *data);
void board(int **pente, int x, int y, int jugador);
void print(int **pente);
void print_prueba(total_info_t *head);
int valid_position(int **pente, int x, int y);

#endif
