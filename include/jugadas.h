#ifndef JUGADASH
#define JUGADASH

#include "pente_types.h"

void coordinates(int **pente, int x, int y, int turno, game_info_t *head);
void file(char name[30]);
void load_plays(int **pente, game_info_t *head);
void save_plays(game_info_t *head);
void enter_data(game_info_t *head, int comida1, int comida2, int contador1, int contador2, int jugador);
plays_t *create_list(int **pente, int *total);
void clear_history(game_info_t *head);
void erase_game(game_info_t *head);
void erase_plays(plays_t **head);

#endif
