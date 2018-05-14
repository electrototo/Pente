#ifndef FILASH
#define FILASH

#include "pente_types.h"

/**
* Revisa el tablero y llama a la función de get_moves para checar si ganó un jugador.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param jugador Contiene el color del token.
* @return temp Numero de tokens del mismo color obtenidos.
**/
int count(int **pente, int jugador);

/**
* Checa en las ocho direcciones posibles después de un tiro, la cantidad de hits que hubo.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param x Coordenadas del token en x.
* @param y Coordenadas del token en y.
* @param jugador Contiene el color del token.
* @return total Regresa (1) si hay una fila de 4, (0) Si no hay filas y (-1) para una fila de 5.
**/
int get_moves(int **pente, int x, int y, int jugador);

/**
* Revisa recursivamente los tokens del tablero para ver si se cumplen las condiciones para ganar.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param **pente Matriz del juego (arreglo bidimensional).
* @param x Coordenadas del token en x.
* @param y Coordenadas del token en y.
* @param token_value Color del token.
* @param dx Dirección en la que se v a checar la siguiente casilla, en x.
* @param dy Dirección en la que se va a checar la siguiente casilla, en y.
* @param level Indica si hubo hits o no.
**/
int follow(int **pente, int token_value, int x, int y, int dx, int dy, int level);

#endif
