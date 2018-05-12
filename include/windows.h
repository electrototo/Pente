#ifndef WINDOWSH
#define WINDOWSH

#include "pente_types.h"

GtkWidget *create_splash_screen(gpointer game_info);
void resume_game(gpointer data);
void save_as_screen(gpointer data);
void show_winner(gpointer data);

void get_player_names_window(gpointer data);
GtkWidget *create_label(char *str);

GtkWidget *main_window_board(game_info_t *game_data);

#endif
