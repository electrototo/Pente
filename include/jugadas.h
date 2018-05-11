#ifndef JUGADASH
#define JUGADASH

#include "pente_types.h"

void coordinates(int pente[MAX][MAX], game_info_t **head);
void file(char name[30]);
void load_plays(int pente[MAX][MAX], game_info_t **head);
void save_plays(game_info_t *head);
void enter_data(game_info_t **head, int comida1, int comida2, int contador1, int contador2, int jugador);
plays_t *create_list(int pente[MAX][MAX], int *total);
void undo(game_info_t **head);
void redo(game_info_t **head);
void clear_history(game_info_t **head);
void erase_game(game_info_t **head);
void erase_plays(plays_t **head);

#endif
