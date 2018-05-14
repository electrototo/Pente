#ifndef JUGADASH
#define JUGADASH

#include "pente_types.h"

/**
* Valida y coloca un token del jugador en turno en la posición (x, y) y actualiza los scores.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param cor_x Coordenadas del token en x.
* @param cor_y Coordenadas del token en y.
* @param turno Indica de que jugador es el turno.
* @param *game_data Contiene la información del juego.
* @return void
**/
void coordinates(int **pente, int x, int y, int turno, game_info_t *head);

/**
* Pide al usuario el nombre del archivo y le concatena .ice
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param name Arreglo del nombre del archivo.
* @return void
**/
void file(char name[30]);

/**
* Carga el estado de juego desde un archivo guardado.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *head Apuntador al inicio de la lista de información del juego.
* @return void
**/
void load_plays(game_info_t *head);

/**
* Guarda el estado de juego en un archivo .ice
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *head Apuntador al inicio de la lista de información del juego.
* @return void
**/
void save_plays(game_info_t *head);

/**
* Actualiza el estado de juego.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *head Apuntador al inicio de la lista de información del juego.
* @return void
**/
void enter_data(total_info_t **head);

/**
* Crea la lista de jugadas.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *game_data Contiene la información del juego.
* @return game_data Regresa la lista.
**/
plays_t *create_list(game_info_t *game_data);

/**
* Borra el historial de jugadas.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *head Apuntador al inicio de la lista de información del juego.
* @return void
**/
void clear_history(game_info_t *head);

/**
* Limpia la lista de game_data.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *head Apuntador al inicio de la lista de información del juego.
* @return void
**/
void erase_game(game_info_t *head);

/**
* Borra las jugadas.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *head Apuntador al inicio de la lista de información del juego.
* @return void
**/
void erase_plays(plays_t **head);

/**
* Carga las jugadas de la lista dinamica.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *game_data Apuntador al inicio de la lista de información del juego.
* @param *head Apuntador al inicio de la lista de posiciones del juego a cargar.
* @return void
**/
void load_from_list(game_info_t *game_data, plays_t *head);

#endif
