/*
 * Callbacks
 * Escrito por Cristobal Liendo, Estibaliz Cano, Isabel León
*/

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

/**
* Determina quien es el jugador activo para colocar una ficha del color correspondiente.
* Se manda llamar cada vez que se detecta un click en la interfaz. 
*
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *event_box No se utiliza.
* @param *event No se utiliza.
* @param data Contiene toda la información del estado del juego.
* @return gboolean No se regresa nada.
**/
gboolean image_press_callback(GtkWidget *event_box, GdkEventButton *event, gpointer data);

/**
* Se manda llamar cuando se presiona el tache en la esquina superior derecha o cuando se cierra la ventana.
* Cierra el proceso principal de GTk.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
*
**/
void destroy(GtkWidget *widget, gpointer data);

/**
* Manda a llamar a la función destroy cuando se detecta el evento de salir de la ventana principal.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return gboolean Regresa falso siempre.
*
**/
gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);

/**
* Imprime gen callback.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *menuitem No se usa.
* @param data Contiene toda la información del estado del juego.
* @return void
*
**/
void gen_callback(GtkWidget *menuitem, gpointer data);

/**
* Llama a la función resume_game.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void open_file(GtkWidget *wdiget, gpointer data);

/**
* Imprime New game.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void new_game(GtkWidget *wdiget, gpointer data);

/**
* Imporime Save en pantalla.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void save(GtkWidget *wdiget, gpointer data);

/**
* Manda a llamar a la función save_as_screen.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void save_as(GtkWidget *wdiget, gpointer data);

/**
* Imprime quit en pantalla.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void quit(GtkWidget *wdiget, gpointer data);

/**
* Deshace la última movida realizada.
*
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void undo(GtkWidget *wdiget, gpointer data);

/**
* Rehace la última movida deshecha.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void redo(GtkWidget *wdiget, gpointer data);

/**
* Imprime el tutorial del juego.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void tutorial(GtkWidget *wdiget, gpointer data);

/**
* Imprime la información de los creadores del programa.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void about_us(GtkWidget *wdiget, gpointer data);

// windows callbacks

/**
* Inicializa la información del juego, muestra el splash screen y posteriormente el tamblero del juego.
* Se manda llamar desde el menú new game.
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void new_game_callback(GtkWidget *widget, gpointer data);

/**
* Manda a llamar a la función resume_game.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void resume_game_callback(GtkWidget *widget, gpointer data);

/**
* Carga en memoria el archivo seleccionado por el cuadro de diálogo.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param response_id Indica el botón que oprimió el usuario en el cuadro de diálogo.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void chooser_callback(GtkWidget *widget, gint response_id, gpointer data);

/**
* Le pide a los jugadores que ingresen el nombre con el que van a jugar.
* Si no se ingresa un nombre, automáticamente les asigana "Jugador 1" y "Jugador 2"
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param response_id Indica el botón que oprimió el usuario en el cuadro de diálogo.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void set_player_name(GtkWidget *widget, gpointer data);

/**
* Cierra la ventana con el nombre del ganador.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param response_id Indica el botón que oprimió el usuario en el cuadro de diálogo.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void close_winner_dialog(GtkWidget *widget, gpointer data);

/**
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *widget Dirección de la ventana principal.
* @param response_id Indica el botón que oprimió el usuario en el cuadro de diálogo.
* @param data Contiene toda la información del estado del juego.
* @return void
**/
void new_game_winner(GtkWidget *widget, gpointer data);

#endif
