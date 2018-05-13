/*
 * autor: cristobal liendo i, estibaliz cano l, isabel leon, s.
 * fecha: Tue 24 Apr 2018 04:08:03 PM CDT
 * descripcion: 
*/

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h" 
#include "windows.h" 

#include "callbacks.h" 
#include "pente_types.h" 

#include "general.h" 

game_info_t *game_init();

int main(int argc, char **argv) {
    GtkWidget *window, *welcome_screen, *toolbar, *dialog, *button;
    GtkToolItem *tool_item;

    GtkWidget *hbox, *vbox;
    GtkWidget *welcome_vbox, *welcome_button;

    // informacion general
    game_info_t *game_data = game_init();

    gtk_init(&argc, &argv);

    game_data->main_board = main_window_board(game_data);
    printf("hey\n");

    // welcome vbox
    welcome_screen = create_splash_screen(game_data);
    gtk_widget_show_all(welcome_screen);
    // end welcome vbox

    gtk_main();

    return 0;
}


game_info_t *game_init() {
    int **pente = (int **) malloc(sizeof(int **) * PENTEMAX);
    image_data_t ***positions = (image_data_t ***) malloc(sizeof(image_data_t ***) * PENTEMAX);

    for (int i = 0; i < PENTEMAX; i++) {
        pente[i] = (int *) malloc(sizeof(int *) * PENTEMAX);
        positions[i] = (image_data_t **) malloc(sizeof(image_data_t **) * PENTEMAX);
    }

    game_info_t *info = g_malloc(sizeof(game_info_t));

    info->p1_label2 = create_label("Jugador 1");
    info->p2_label2 = create_label("Jugador 2");

    info->p1_label1 = create_label("Jugador 1");
    info->p2_label1 = create_label("Jugador 2");

    info->turn_label = create_label("Jugador 1");
    info->file_name = NULL;

    total_info_t *head = (total_info_t *) malloc(sizeof(total_info_t));
    head->turn = 1;
    head->score1 = 0;
    head->score2 = 0;
    head->hit1 = 0;
    head->hit2 = 0;
    head->child = NULL;
    head->ant = NULL;

    head->sig = NULL; 
    
    info->head = head; 

    info->pente_board = pente;
    info->positions = positions;

    return info;
}
