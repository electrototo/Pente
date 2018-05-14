#ifndef WINDOWSH
#define WINDOWSH

#include "pente_types.h"

/**
* Crea la ventana del splash screen.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param game_info Información del juego.
* @return window Se abre el splash screen.
**/
GtkWidget *create_splash_screen(gpointer game_info);

/**
* Abre el cuadro de diálogo para escoger un archivo de juego guardado previamente (*.ice).
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param data Contiene la información del juego.
* @return void
**/
void resume_game(gpointer data);

/**
* Abre el cuadro de diálogo para guardar el estado de un juego en un archivo (*.ice).
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param data Contiene la información del juego.
* @return void
**/
void save_as_screen(gpointer data);

/**
* Crea y muestra la ventana del jugador que ganó.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param data Contiene la información del juego.
* @return void
**/
void show_winner(gpointer data);

/**
* Crea y abre la ventana para solicitar el nombre de los jugadores.
* Si el usuario no ingresa su nombre, se autodeterminarán (Jugador 1) y (Jugador 2).
*
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param data Contiene la información del juego.
* @return void
**/
void get_player_names_window(gpointer data);

/**
* Crea una etiqueta con el contenido de *str.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *str Apuntador al contenido de la etiqueta.
* @return label La etiqueta que se creó
**/
GtkWidget *create_label(char *str);

/**
* Crea e inicializa la ventana principal del tablero de juego.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *game_data Información del juego.
* @return window La ventana principal del tablero de juego.
**/
GtkWidget *main_window_board(game_info_t *game_data);

#endif
