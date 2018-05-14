#ifndef COMIDASH
#define COMIDASH

#include "pente_types.h"

/**
* Cuenta el número de hits en cada tiro.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param x Coordenadas del token en x.
* @param y Coordenadas del token en y.
* @param token_value Color del token.
* @param **head Apuntador al inicio de la lista de hits.
* @return temp Total de hits.
**/
int count_hit(int **pente, int next, int token_value, hit_t **head);

/**
* Checa en las ocho direcciones posibles después de un tiro, la cantidad de hits que hubo.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param x Coordenadas del token en x.
* @param y Coordenadas del token en y.
* @param token_value Color del token.
* @param next Contiene el valor de la ficha contraria a la del jugador en turno.
* @param **head Apuntador al inicio de la lista de hits.
* @return total Total de hits en las 8 direcciones.
**/
int get_hits(int **pente, int x, int y, int token_value, int next, hit_t **head);

/**
* Revisa si hay un hit en (x, y) y la posición indicada por (dx, dy).
* Si no lo hay, regresa 0, Si si lo hay, regresa 1 (level).
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param x Coordenadas del token en x.
* @param y Coordenadas del token en y.
* @param dx Dirección en la que se v a checar la siguiente casilla, en x.
* @param dy Dirección en la que se va a checar la siguiente casilla, en y.
* @param level Indica si hubo hits o no.
* @param token_value Color del token.
* @param next Contiene el valor de la ficha contraria a la del jugador en turno.
* @param **head Apuntador al inicio de la lista de hits.
* @return level Si hubo hits (1), o no (0).
**/
int follow_hits(int **pente, int token_value, int next, int x, int y, int dx, int dy, int level, hit_t **head);

/**
* Agrega un hit a la lista de hits en (x, y).
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param x Coordenadas del token en x.
* @param y Coordenadas del token en y.
* @param **head Apuntador al inicio de la lista de hits.
* @return void
**/
void enter_hit(hit_t **head, int y, int x, int **pente);

/**
* Elimina un hit en el tablero y en la lista de hits.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param **first Apuntador al inicio de la lista de hits.
* @param jugador Color de la ficha.
* @param data Contiene toda la información del juego.
* @return void
**/
void clear_hit(hit_t **head, int **pente, int jugador, game_info_t *data);

/**
* Limpia la lista de hits después de cada turno para reusarse. 
*
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **head Apuntador al inicio de la lista de hits.
* @return void
**/
void erase_hits(hit_t **head);

#endif
