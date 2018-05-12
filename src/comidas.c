#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "pente_types.h"
#include "comidas.h"


int count_hit(int **pente, int next, int token_value, hit_t **head) {
    int temp = 0, x, y;

    for (y = 0; y < PENTEMAX; y++) {
        for (x = 0; x < PENTEMAX; x++) {
            if (pente[y][x] == next) {
                temp += get_hits(pente, x, y, token_value, next, head);
            }
        }
    }

    return temp;
}

int get_hits(int **pente, int x, int y, int token_value, int next, hit_t **head) {
    int total = 0, actual;

    int directions[8][2] = {
        {0, -1}, {1, -1},
        {1, 0}, {1, 1},
        {0, 1}, {-1, 1},
        {-1, 0}, {-1, -1}
    };

    for (int i = 0; i < 8; i++) {
        actual = follow_hits(pente, token_value, next, x, y, directions[i][0], directions[i][1], 0, head);

        if (actual == 1)
            total++;
    }

    return total;
}

int follow_hits(int **pente, int token_value, int next, int x, int y, int dx, int dy, int level, hit_t **head) {
    if (x < 0 || x >= PENTEMAX || y < 0 || y >= PENTEMAX) //checa limites de la matriz
        return level;

    if (pente[y][x] != next) //si la coordenada es distinta a next_token_value se sale
        return level;

    if (level == 1)
        return 1;

    if (level == 0) {
        if ((x - dx) < 0 || (x - dx) >= PENTEMAX || (x + dx) < 0 || (x + dx) >= PENTEMAX)
            return level;

        if((y - dy) < 0 || (y - dy) >= PENTEMAX || (y + dy) < 0 || (y + dy) >= PENTEMAX) //checa limites de la matriz
            return level;

        if ((pente[y - dy][x - dx] == token_value) && (pente[y + dy][x + dx] == next) && (pente[y + (dy + dy)][x + (dx + dx)] == token_value)) {
            enter_hit(head, y, x, pente);
            return level + 1;
        }
        else
            return 0;
    }

    level = follow_hits(pente, token_value, next, x + dx, y + dy, dx, dy, level + 1, head);
    return level;
}

void enter_hit(hit_t **head, int y, int x, int **pente) {
    hit_t *temp;

    temp = (hit_t *) malloc(sizeof(hit_t));
    temp->coordenada_x = x;
    temp->coordenada_y = y;
    temp->sig = *head;
    *head = temp;
}

//borrar coordenada de la matriz
void clear_hit(hit_t **first, int **pente, int jugador, game_info_t *data) { 
    hit_t *temp;
    temp = *first;

    GdkPixbuf *white_token;
    image_data_t *image_pos;

    printf("check 1\n");
    printf("score 1: %d, score 2: %d\n", data->head->score1, data->head->score2);
    printf("check 2\n");

    while (temp != NULL) {
        printf("borrando (%d, %d)\n", temp->coordenada_x, temp->coordenada_y);
        pente[temp->coordenada_y][temp->coordenada_x] = 0;

        white_token = gdk_pixbuf_new_from_file("imagenes/white_token.jpg", NULL);

        // set image here
        image_pos = data->positions[temp->coordenada_y][temp->coordenada_x];
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_pos->image), white_token);

        *first = temp->sig;
        free(temp);
        temp = *first;
    }
}

//funcion limpia lista de hits
void erase_hits(hit_t **head)  {
    hit_t *temp;
    temp = *head;

    while (temp != NULL) {
        *head = temp->sig;
        free(temp);
        temp = *head;
    }
}
