#ifndef JUGADASH
#define JUGADASH

#include "pente_types.h"

void coordinates(int **pente, int x, int y, int turno, game_info_t *head);
void file(char name[30]);
void load_plays(game_info_t *head);
void save_plays(game_info_t *head);
void enter_data(total_info_t **head);
plays_t *create_list(game_info_t *game_data);
void clear_history(game_info_t *head);
void erase_game(game_info_t *head);
void erase_plays(plays_t **head);

void load_from_list(game_info_t *game_data, plays_t *head);

#endif
