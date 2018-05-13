/*
 *  autores: cristobal liendo, estibaliz cano, isabel leon
 *  fecha: Sat 05 May 2018 09:15:54 PM CDT
 *  descripcion: callbacks para la interfaz grafica de pente
*/

#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>

#include "callbacks.h" 
#include "pente_types.h" 
#include "windows.h" 

#include "general.h"
#include "jugadas.h"

// funcional

gboolean image_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data) {
    image_data_t *img_data = (image_data_t *) data;
    game_info_t *game_data = (game_info_t *) img_data->game_info;

    GdkPixbuf *new_image, *turn_image;

    printf("Click at: %d, %d\n", img_data->x, img_data->y);
    printf("Player 1 points: %d, Player 2 points: %d\n",
        game_data->head->score1, game_data->head->score2);

    if (valid_position(game_data->pente_board, img_data->x, img_data->y)) {
        print(game_data->pente_board);

        if ((game_data->head)->turn == 1) {
            new_image = gdk_pixbuf_new_from_file("imagenes/blue_token.jpg", NULL);
            turn_image = gdk_pixbuf_new_from_file("imagenes/red_token.jpg", NULL);

            (game_data->head)->turn = 2;

            gtk_label_set_text(GTK_LABEL(game_data->turn_label), game_data->player2);
        }
        else {
            new_image = gdk_pixbuf_new_from_file("imagenes/red_token.jpg", NULL);
            turn_image = gdk_pixbuf_new_from_file("imagenes/blue_token.jpg", NULL);

            (game_data->head)->turn = 1;

            gtk_label_set_text(GTK_LABEL(game_data->turn_label), game_data->player1);
        }
        gtk_image_set_from_pixbuf(GTK_IMAGE(game_data->turn_image), turn_image);
        gtk_image_set_from_pixbuf(GTK_IMAGE(img_data->image), new_image);

        coordinates(game_data->pente_board, img_data->x, img_data->y, (game_data->head)->turn, game_data);

        if (game_data->head->score1 == 4 || game_data->head->score1 == -1 || 
            game_data->head->score2 == 4 || game_data->head->score2 == -1 ||
            game_data->head->hit1 == 10  || game_data->head->hit2 == 10) {

            show_winner(game_data);
        }
    }
}

void destroy(GtkWidget *widget, gpointer data) {
    game_info_t *game_info = (game_info_t *) data;

    erase_game(game_info);
    gtk_main_quit();
}

void open_file(GtkWidget *widget, gpointer data) {
  resume_game(data);
  //game_info_t *game_info = (game_info_t *) data;

  //erase_game(game_info);
  //clear_board(game_info->pente_board, game_info);
  //load_plays(game_info); 
} 

void new_game(GtkWidget *wdiget, gpointer data) {
  game_info_t *game_info = (game_info_t *) data; 
  clear_board(game_info->pente_board, game_info);
} 

void new_game_winner(GtkWidget *widget, gpointer data) {
    game_info_t *game_info = (game_info_t *) data;
    GtkWidget *window;

    window = gtk_widget_get_parent(
        gtk_widget_get_parent(
            gtk_widget_get_parent(widget)
        )
    );


    gtk_widget_destroy(window);
    clear_board(game_info->pente_board, game_info);
}

void save(GtkWidget *wdiget, gpointer data) {
    game_info_t *game_info = (game_info_t *) data;

    print_prueba(game_info->head);
    save_plays(game_info);
} 

void save_as(GtkWidget *wdiget, gpointer data) {
    save_as_screen(data);
} 

void quit(GtkWidget *wdiget, gpointer data) {
} 

void undo(GtkWidget *wdiget, gpointer data) {
    game_info_t *game_info = (game_info_t *) data; 
    clear_board(game_info->pente_board, game_info);
} 

void redo(GtkWidget *wdiget, gpointer data) {
    game_info_t *game_info = (game_info_t *) data; 
    clear_board(game_info->pente_board, game_info);
} 

void tutorial(GtkWidget *wdiget, gpointer data) {
} 

void about_us(GtkWidget *wdiget, gpointer data) {
    printf("About us\n");
} 

gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    destroy(widget, data);

    return FALSE;
}

void gen_callback(GtkWidget *menuitem, gpointer data) {
    g_print("gen_callback\n");
}

// windows signals
void new_game_callback(GtkWidget *widget, gpointer data) {
    game_info_t *info = (game_info_t *) data;

    GtkWidget *splash_window = gtk_widget_get_parent(widget);
    splash_window = gtk_widget_get_parent(splash_window);
    gtk_widget_hide(splash_window);

    get_player_names_window(data);
}

void resume_game_callback(GtkWidget *widget, gpointer data) {
    resume_game(data);
}

void chooser_callback(GtkWidget *widget, gint response_id, gpointer data) {
    FILE *fp;
    char *uri, *file_name;

    game_info_t *game_info = (game_info_t *) data;

    switch (response_id) {
        case RESPONSE_OPEN:
            uri = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(widget));

            // aqui carga en memoria el archivo
            g_print("uri: %s\n", uri);
            file_name = &uri[7];

            fp = fopen(file_name, "rb");

            if (fp == NULL) {
                printf("error opening file\n");
            }
            else {
                fclose(fp);

                gtk_widget_destroy(widget);

                gtk_widget_show_all(game_info->main_board);

                erase_game(game_info);
                clear_board(game_info->pente_board, game_info);
                load_plays(game_info); 
            }

            g_free(uri);

            break;

        case RESPONSE_CANCEL:
            gtk_widget_destroy(widget);
            g_print("Cancel_data\n");
            break;

        default:
            break;
    }
}

void set_player_name(GtkWidget *widget, gpointer data) {
    name_packet_t *packet = (name_packet_t *) data;
    game_info_t *game_info = packet->game_data;

    strcpy(game_info->player1, gtk_entry_get_text(GTK_ENTRY(packet->player1)));
    strcpy(game_info->player2, gtk_entry_get_text(GTK_ENTRY(packet->player2)));

    if (strlen(game_info->player1) == 0)
        strcpy(game_info->player1, "Jugador 1");

    else if (isalpha(game_info->player1[0]) && islower(game_info->player1[0]))
        game_info->player1[0] = (game_info->player1[0] - 'a') + 'A';

    if (strlen(game_info->player2) == 0)
        strcpy(game_info->player2, "Jugador 2");

    else if (isalpha(game_info->player2[0]) && islower(game_info->player2[0]))
        game_info->player2[0] = (game_info->player2[0] - 'a') + 'A';

    gtk_label_set_text(GTK_LABEL(game_info->p1_label1), game_info->player1);
    gtk_label_set_text(GTK_LABEL(game_info->p1_label2), game_info->player1);

    gtk_label_set_text(GTK_LABEL(game_info->p2_label1), game_info->player2);
    gtk_label_set_text(GTK_LABEL(game_info->p2_label2), game_info->player2);

    gtk_label_set_text(GTK_LABEL(game_info->turn_label), game_info->player1);

    gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(widget)));
    gtk_widget_show_all(game_info->main_board);
}

void close_winner_dialog(GtkWidget *widget, gpointer data) {
    game_info_t *game_data = (game_info_t *) data;

    gtk_widget_destroy(gtk_widget_get_parent(widget));
    destroy(widget, data);
}
