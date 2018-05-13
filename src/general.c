#include <stdio.h>
#include <string.h>

#include "pente_types.h"
#include "general.h"
#include "jugadas.h"
#include "filas.h"

void clear_board(int **pente, game_info_t *data) {
  GdkPixbuf *white_token;
  image_data_t *image_pos;
  
  white_token = gdk_pixbuf_new_from_file("imagenes/white_token.jpg", NULL);
  
  for (int y = 0; y < PENTEMAX; y++){
    for (int x = 0; x < PENTEMAX; x++){
      pente[y][x] = 0;
      image_pos = data->positions[y][x];
      gtk_image_set_from_pixbuf(GTK_IMAGE(image_pos->image), white_token);
    }
  }
}

void board(int **pente, int x, int y, int jugador) {
  pente[y][x] = jugador;
}

void tick_image_board(plays_t *actual_coord, game_info_t *game_data) {
    image_data_t *image_pos;

    int x = actual_coord->coor_x;
    int y = actual_coord->coor_y;
    int token_value = actual_coord->token_value;

    image_pos = game_data->positions[y][x];
    GdkPixbuf *token_image;

    if (token_value == VAL2)
        token_image = gdk_pixbuf_new_from_file("imagenes/blue_token.jpg", NULL);

    else if (token_value == VAL1)
        token_image = gdk_pixbuf_new_from_file("imagenes/red_token.jpg", NULL);

    gtk_image_set_from_pixbuf(GTK_IMAGE(image_pos->image), token_image);
}

void print(int **pente)  {
  int i, j;
  printf("    ");
  for (i = 0; i < PENTEMAX; i++)
    {
      printf(" %2d", i);
    }

  printf("\n");
  for (i = 0; i < PENTEMAX; i++)
    {
      printf(" %2d |", i);
      for (j = 0; j < PENTEMAX; j++)
        {
            printf(" %d|", pente[i][j]);
        }
      printf("\n");
    }
}

void print_prueba(total_info_t *head){
    total_info_t *cursor = head;
    plays_t *plays_cursor;

    while (cursor != NULL) {
        printf("Node %p\n", cursor);
        printf("\tPrev: %p\n", cursor->ant);
        printf("\tNext: %p\n", cursor->sig);
        printf("\tChild: %p\n", cursor->child);
        printf("\tImprimiendo informacion de coordenadas de %p\n", cursor->child);

        plays_cursor = cursor->child;

        while (plays_cursor != NULL) {
            printf("\t\tPlay %p", plays_cursor);
            printf("\t\tX, Y: %d, %d\n", plays_cursor->coor_x, plays_cursor->coor_y);
            printf("\t\tToken value: %d\n", plays_cursor->token_value);
            printf("\t\tNext: %p\n", plays_cursor->sig);

            plays_cursor = plays_cursor->sig;
        }

        cursor = cursor->sig;
    }
}

int valid_position(int **pente, int x, int y) {
    return valid_range(x, y) && pente[y][x] != VAL1 && pente[y][x] != VAL2;
}
