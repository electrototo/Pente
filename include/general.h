#ifndef GENERALH
#define GENERALH

#include "pente_types.h"

void clear_board(int **pente, game_info_t *data);
void board(int **pente, int x, int y, int jugador);
void print(int **pente);
void print_prueba(total_info_t *head);
int valid_position(int **pente, int x, int y);

void reverse_list(game_info_t *game_data);

void tick_image_board(plays_t *actual_coord, game_info_t *game_data);

#endif
