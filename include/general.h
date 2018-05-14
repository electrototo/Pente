#ifndef GENERALH
#define GENERALH

#include "pente_types.h"

/**
* Elimina el tablero.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param *data Apuntador a toda la información del estado de juego.
* @return void
**/
void clear_board(int **pente, game_info_t *data);

/**
* Asigna una ficha del jugador correspondiente al tablero (x, y).
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param x Coordenadas del token en x.
* @param y Coordenadas del token en y.
* @param jugador Contiene el color del token.
* @return void
**/
void board(int **pente, int x, int y, int jugador);

/**
* Coloca el token del color correspondiente del jugador al tablero.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @return void
**/
void print(int **pente);

/**
* Realiza una prueba de impresión de la estructura de información del estado de juego.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *head Apuntador al inicio de la lista de información.
* @return void
**/
void print_prueba(total_info_t *head);

/**
* Revisa si la posición en la que se quiere colocar el token esta vacía y que el rango de la matriz sea válido.
* Llama a la función valid_range.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param x Coordenadas del token en x.
* @param y Coordenadas del token en y.
* @return valid_range Revisa que la posición este dentro del rango de la matriz.
**/
int valid_position(int **pente, int x, int y);

/**
* Marca la posición en x en el tablero con la información recibida de actual_coord.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *game_data Contiene la información del juego.
* @param *actual_coord Indica de que jugador es la ficha y su posición (x, y).
* @return void
**/
void tick_image_board(plays_t *actual_coord, game_info_t *game_data);

#endif
