/*
 *  autor: cristobal liendo <cristobal@liendo.net>
 *  fecha: Mon 07 May 2018 09:03:04 PM CDT
 *  descripcion: se encuentra el codigo de todas las ventanas
*/

#include <gtk/gtk.h>

#include "callbacks.h"
#include "windows.h"

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

void show_winner(gpointer data) {
    GtkWidget *winner_window, *vbox, *hbox;
    GtkWidget *close_button, *new_game_button, *label;

    winner_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(winner_window), 30);

    gtk_window_set_title(GTK_WINDOW(winner_window), "WINNER!");

    close_button = gtk_button_new_with_label("CLOSE");
    new_game_button = gtk_button_new_with_label("NEW GAME");

    gtk_widget_set_usize(close_button, 150, 50);
    gtk_widget_set_usize(new_game_button, 150, 50);

    label = gtk_label_new("Player 1 wins!");

    vbox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(winner_window), vbox);

    gtk_container_add(GTK_CONTAINER(vbox), label);

    hbox = gtk_hbox_new(TRUE, 50);
    gtk_container_add(GTK_CONTAINER(hbox), close_button);
    gtk_container_add(GTK_CONTAINER(hbox), new_game_button);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);

    gtk_widget_show_all(winner_window);
}
