#ifndef COMIDASH
#define COMIDASH

#include "pente_types.h"

int count_hit(int **pente, int next, int token_value, hit_t **head);
int get_hits(int **pente, int x, int y, int token_value, int next, hit_t **head);
int follow_hits(int **pente, int token_value, int next, int x, int y, int dx, int dy, int level, hit_t **head);
void enter_hit(hit_t **head, int y, int x, int **pente);
void clear_hit(hit_t **head, int **pente, int jugador, game_info_t *data);
void erase_hits(hit_t **head);

#endif
