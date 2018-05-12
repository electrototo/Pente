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
    while (head != NULL) {
        printf("Nodo %p\n", head);
        printf("  sig: %p\n", head->sig);
        //printf("X = %d, Y = %d\n", head->coor_x, head->coor_y);
        head = head->sig;
    }       
}

int valid_position(int **pente, int x, int y) {
    return valid_range(x, y) && pente[y][x] != VAL1 && pente[y][x] != VAL2;
}
