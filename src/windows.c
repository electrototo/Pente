/*
 *  autor: cristobal liendo <cristobal@liendo.net>
 *  fecha: Mon 07 May 2018 09:03:04 PM CDT
 *  descripcion: se encuentra el codigo de todas las ventanas
*/

#include <gtk/gtk.h>
#include <string.h>

#include "callbacks.h"
#include "windows.h"
#include "menus.h"
#include "general.h"

#include "pente_types.h"

GtkWidget *create_splash_screen(gpointer game_info) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *vbox = gtk_vbox_new(TRUE, 0);

    GtkWidget *new_game_button, *resume_button;

    gtk_container_set_border_width(GTK_CONTAINER(window), 50);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "Pente v1.0");

    new_game_button = gtk_button_new_with_label("NEW GAME");
    resume_button = gtk_button_new_with_label("RESUME PLAYING");

    g_signal_connect(new_game_button, "clicked", G_CALLBACK(new_game_callback), game_info);
    g_signal_connect(resume_button, "clicked", G_CALLBACK(resume_game_callback), game_info);

    gtk_widget_set_usize(new_game_button, 400, 70);

    g_signal_connect(GTK_WINDOW(window), "delete-event", G_CALLBACK(delete_event), game_info);

    gtk_box_pack_start(GTK_BOX(vbox), new_game_button, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), resume_button, TRUE, TRUE, 10);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    return window;
}

// get file direction
void resume_game(gpointer data) {
    GtkWidget *chooser;
    GtkFileFilter *filter;

    chooser = gtk_file_chooser_dialog_new(
        "Select file",
        NULL,
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Open",
        RESPONSE_OPEN,
        "Cancel",
        RESPONSE_CANCEL,
        NULL
    );

    filter = gtk_file_filter_new();

    gtk_file_filter_set_name(filter, "Pente files (.ice)");
    gtk_file_filter_add_pattern(filter, "*.ice");

    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(chooser), FALSE);

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(chooser), filter);
    g_signal_connect(GTK_DIALOG(chooser), "response", G_CALLBACK(chooser_callback), data);

    gtk_widget_show_all(chooser);
}

void save_as_screen(gpointer data) {
    GtkWidget *chooser;
    GtkFileFilter *filter;

    chooser = gtk_file_chooser_dialog_new(
        "Select file",
        NULL,
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "Save",
        RESPONSE_SAVE_AS,
        "Cancel",
        RESPONSE_CANCEL,
        NULL
    );

    filter = gtk_file_filter_new();

    gtk_file_filter_set_name(filter, "Pente files (.ice)");
    gtk_file_filter_add_pattern(filter, "*.ice");

    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(chooser), FALSE);

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(chooser), filter);
    g_signal_connect(GTK_DIALOG(chooser), "response", G_CALLBACK(chooser_callback), data);

    gtk_widget_show_all(chooser);
}

void show_winner(gpointer data) {
    GtkWidget *winner_window, *vbox, *hbox;
    GtkWidget *close_button, *new_game_button, *label;

    char buffer_message[100];

    game_info_t *game_data = (game_info_t *) data;

    winner_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(winner_window), "Pente v1.0");
    gtk_container_set_border_width(GTK_CONTAINER(winner_window), 30);

    gtk_window_set_title(GTK_WINDOW(winner_window), "WINNER!");

    close_button = gtk_button_new_with_label("CLOSE");
    new_game_button = gtk_button_new_with_label("NEW GAME");

    g_signal_connect(close_button, "clicked", G_CALLBACK(close_winner_dialog), data);
    g_signal_connect(new_game_button, "clicked", G_CALLBACK(new_game_winner), data);

    gtk_widget_set_usize(close_button, 150, 50);
    gtk_widget_set_usize(new_game_button, 150, 50);

    if (game_data->head->score1 >= 4 || game_data->head->score1 == -1 || game_data->head->hit1 >= 10)
        strcpy(buffer_message, game_data->player1);
    else
        strcpy(buffer_message, game_data->player2);

    strcat(buffer_message, " is the winner!");

    if (game_data->head->items >= PENTEMAX * PENTEMAX) {
        strcpy(buffer_message, "Game over");
    }

    label = gtk_label_new(buffer_message);

    vbox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(winner_window), vbox);

    gtk_container_add(GTK_CONTAINER(vbox), label);

    hbox = gtk_hbox_new(TRUE, 50);
    gtk_container_add(GTK_CONTAINER(hbox), close_button);
    gtk_container_add(GTK_CONTAINER(hbox), new_game_button);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);

    gtk_widget_show_all(winner_window);
}

void get_player_names_window(gpointer data) {
    GtkWidget *window, *accept, *entry;
    GtkWidget *vbox, *hbox;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Pente v1.0");
    accept = gtk_button_new_with_label("Continue");

    vbox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(GTK_WINDOW(window), "delete-event", G_CALLBACK(delete_event), data);

    name_packet_t *info_packet = (name_packet_t *) g_malloc(sizeof(name_packet_t));

    // tabla de jugador 1
    hbox = gtk_hbox_new(TRUE, 0);

    // falta conectar al picar enter
    entry = gtk_entry_new();
    info_packet->player1 = entry;

    gtk_container_add(GTK_CONTAINER(hbox), gtk_label_new("Player's 1 name: "));
    gtk_container_add(GTK_CONTAINER(hbox), entry);

    gtk_container_add(GTK_CONTAINER(vbox), hbox);

    // tabla de jugador 2
    hbox = gtk_hbox_new(TRUE, 0);
    entry = gtk_entry_new();
    info_packet->player2 = entry;

    gtk_container_add(GTK_CONTAINER(hbox), gtk_label_new("Player's 2 name: "));
    gtk_container_add(GTK_CONTAINER(hbox), entry);

    gtk_container_add(GTK_CONTAINER(vbox), hbox);
    gtk_container_add(GTK_CONTAINER(vbox), accept);

    info_packet->game_data = data;

    g_signal_connect(accept, "clicked", G_CALLBACK(set_player_name), info_packet);

    gtk_widget_show_all(window);
}

GtkWidget *main_window_board(game_info_t *game_data) {
    GtkWidget *vbox, *hbox;
    GtkWidget *window;

    // para las imagenes
    GtkWidget *event_box;
    image_data_t *img_data;

    // tablero principal
    GtkWidget *main_container, *sidebar_menu, *pente_container;
    GtkWidget *players, *turn, *comidas;
    GtkWidget *label, *frame;
    // final tablero principal

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Pente v1.0");
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), game_data);

    GtkWidget *token, *white;

    vbox = gtk_vbox_new(FALSE, 0);
    hbox = gtk_hbox_new(TRUE, 0);

    gtk_container_add(GTK_CONTAINER(vbox), create_menubar(game_data));


    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    main_container = gtk_hbox_new(TRUE, 0);
    sidebar_menu = gtk_vbox_new(TRUE, 0);
    pente_container = gtk_vbox_new(TRUE, 0);

    players = gtk_vbox_new(TRUE, 0);
    turn = gtk_hbox_new(TRUE, 0);
    comidas = gtk_vbox_new(TRUE, 0);



    gtk_container_add(GTK_CONTAINER(hbox), create_toolbar(game_data));

    // start pente board
    for (int y = 0; y < PENTEMAX; y++) {
        hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(pente_container), hbox, TRUE, TRUE, 0);

        for (int x = 0; x < PENTEMAX; x++) {
            token = gtk_image_new_from_file("imagenes/white_token.jpg");

            img_data = (image_data_t *) g_malloc(sizeof(image_data_t));

            game_data->positions[y][x] = img_data;

            img_data->x = x;
            img_data->y = y;
            img_data->image = token;

            img_data->game_info = game_data;

            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), token);

            g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(image_press_callback), img_data);

            gtk_container_add(GTK_CONTAINER(hbox), event_box);
            gtk_widget_show(token);
        }
    }

    // end pente board
    clear_board(game_data->pente_board, game_data);

    gtk_box_pack_start(GTK_BOX(vbox), main_container, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_container), sidebar_menu, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_container), pente_container, TRUE, TRUE, 0);

    // informacion general
    frame = gtk_frame_new("Jugadores");
    gtk_container_add(GTK_CONTAINER(sidebar_menu), frame);
    gtk_container_add(GTK_CONTAINER(frame), players);

    gtk_container_add(GTK_CONTAINER(players), game_data->p1_label1);
    gtk_container_add(GTK_CONTAINER(players), game_data->p2_label1);

    frame = gtk_frame_new("Turno");
    game_data->turn_label = create_label("Jugador 1");

    gtk_container_add(GTK_CONTAINER(sidebar_menu), frame);
    gtk_container_add(GTK_CONTAINER(frame), turn);
    gtk_container_add(GTK_CONTAINER(turn), game_data->turn_label);

    // imagen del jugador
    game_data->turn_image = gtk_image_new_from_file("imagenes/blue_token.jpg");
    gtk_container_add(GTK_CONTAINER(turn), game_data->turn_image);

    frame = gtk_frame_new("Puntaje");
    gtk_container_add(GTK_CONTAINER(sidebar_menu), frame);
    gtk_container_add(GTK_CONTAINER(frame), comidas);

    hbox = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(comidas), hbox);
    gtk_container_add(GTK_CONTAINER(hbox), game_data->p1_label2);
    gtk_container_add(GTK_CONTAINER(hbox), game_data->points1_label);

    hbox = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(comidas), hbox);
    gtk_container_add(GTK_CONTAINER(hbox), game_data->p2_label2);
    gtk_container_add(GTK_CONTAINER(hbox), game_data->points2_label);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    return window;
}

GtkWidget *create_label(char *str) {
    GtkWidget *label;

    label = gtk_label_new(str);
    //gtk_misc_set_alignment(GTK_MISC(label), 0, 0);
    //gtk_misc_set_padding(GTK_MISC(label), 50, 5);

    return label;
}
