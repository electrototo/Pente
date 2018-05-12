/*
 *  autores: cristobal liendo, estibaliz cano, isabel leon
 *  fecha: Sat 05 May 2018 09:15:54 PM CDT
 *  descripcion: callbacks para la interfaz grafica de pente
*/

#include <gtk/gtk.h>

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
        game_data->score1, game_data->score2);

    if (valid_position(game_data->pente_board, img_data->x, img_data->y)) {
        print(game_data->pente_board);


        if (game_data->turn == 1) {
            new_image = gdk_pixbuf_new_from_file("imagenes/blue_token.jpg", NULL);
            turn_image = gdk_pixbuf_new_from_file("imagenes/red_token.jpg", NULL);

            game_data->turn = 2;

            gtk_label_set_text(GTK_LABEL(game_data->turn_label), "Jugador 2");
        }
        else {
            new_image = gdk_pixbuf_new_from_file("imagenes/red_token.jpg", NULL);
            turn_image = gdk_pixbuf_new_from_file("imagenes/blue_token.jpg", NULL);

            game_data->turn = 1;

            gtk_label_set_text(GTK_LABEL(game_data->turn_label), "Jugador 1");
        }
        gtk_image_set_from_pixbuf(GTK_IMAGE(game_data->turn_image), turn_image);
        gtk_image_set_from_pixbuf(GTK_IMAGE(img_data->image), new_image);

        coordinates(game_data->pente_board, img_data->x, img_data->y, game_data->turn, game_data);
    }
}

void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void open_file(GtkWidget *widget, gpointer data) {
    resume_game(data);
} 

void new_game(GtkWidget *wdiget, gpointer data) {
    printf("New game");
} 

void save(GtkWidget *wdiget, gpointer data) {
    printf("Save");
} 

void save_as(GtkWidget *wdiget, gpointer data) {
    save_as_screen(data);
} 

void quit(GtkWidget *wdiget, gpointer data) {
    printf("Quit");
} 

void undo(GtkWidget *wdiget, gpointer data) {
    printf("Undo");
} 

void redo(GtkWidget *wdiget, gpointer data) {
    printf("Redo");
} 

void tutorial(GtkWidget *wdiget, gpointer data) {
    printf("Tutorial\n");
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
    gtk_widget_show_all(info->main_board);
}

void resume_game_callback(GtkWidget *widget, gpointer data) {
    resume_game(data);
}

void chooser_callback(GtkWidget *widget, gint response_id, gpointer data) {
    char *uri;

    g_print("callback\n");
    switch (response_id) {
        case RESPONSE_OPEN:
            uri = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(widget));

            // aqui carga en memoria el archivo
            g_print("uri: %s\n", uri);

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
