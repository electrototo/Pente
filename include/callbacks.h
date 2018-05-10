/*
 * Callbacks
 * Escrito por Cristobal Liendo <cristobal@liendo.net>
*/

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

gboolean image_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data);
void destroy(GtkWidget *widget, gpointer data);
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);

void gen_callback(GtkWidget *menuitem, gpointer data);

void open_file(GtkWidget *wdiget, gpointer data);
void new_game(GtkWidget *wdiget, gpointer data);
void save(GtkWidget *wdiget, gpointer data);
void save_as(GtkWidget *wdiget, gpointer data);
void quit(GtkWidget *wdiget, gpointer data);
void undo(GtkWidget *wdiget, gpointer data);
void redo(GtkWidget *wdiget, gpointer data);
void tutorial(GtkWidget *wdiget, gpointer data);
void about_us(GtkWidget *wdiget, gpointer data);

// windows callbacks
void new_game_callback(GtkWidget *widget, gpointer data);
void resume_game_callback(GtkWidget *widget, gpointer data);

void chooser_callback(GtkWidget *widget, gint response_id, gpointer data);

#endif
