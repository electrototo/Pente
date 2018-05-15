#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#include "pente_types.h" 
#include "jugadas.h" 
#include "filas.h" 
#include "comidas.h" 
#include "general.h" 

void coordinates(int **pente, int cor_x, int cor_y, int turno, game_info_t *game_data) {
    hit_t *first = NULL; //inicializar lista de hits
    game_info_t *cursor;
    int contador, next;

    int filas;
    next = (turno == VAL1) ? VAL2 : VAL1;

    if (valid_position(pente, cor_x, cor_y)) {
        board(pente, cor_x, cor_y, turno);

        if (game_data->head->ant != NULL)
            clear_history(game_data);

        enter_data(&(game_data->head));

        game_data->head->score1 = count(pente, VAL2);
        game_data->head->score2 = count(pente, VAL1);

        game_data->head->hit1 += count_hit(pente, VAL1, VAL2, &first);
        if (first != NULL)
            clear_hit(&first, pente, next, game_data);

        game_data->head->hit2 += count_hit(pente, VAL2, VAL1, &first);
        if (first != NULL)
            clear_hit(&first, pente, turno, game_data);

        printf("\nContador filas 1  = %d\n", game_data->head->score1);
        printf("Comidas jugador 1   = %d\n\n", game_data->head->hit1);
        printf("Contador filas 2   = %d\n", game_data->head->score2);
        printf("Comidas jugador 2   = %d\n\n", game_data->head->hit2);
    }
    else
        printf("<Lugar ya ocupado>\n");

    game_data->head->child = create_list(game_data);

    //print(pente);
    contador = game_data->head->items;
}

void file(char name[30]) {
    getchar();
    printf("\nFile archivo> ");
    fgets(name, 29, stdin);

    strcat(name, ".ice"); 
    strtok(name, "\n");
}

void load_plays(game_info_t *game_data) {
    FILE *fd;
    total_info_t *temp, *temp2;
    plays_t *actual_coord;
    long size;

    if (game_data->file_name == NULL)
        fd = fopen("juego.ice", "r");

    else
        fd = fopen(game_data->file_name, "r");

    if (fd == NULL) {
        printf("\n<nonexistent file>\n");
        return;
    }
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    
    while (ftell(fd) < size - 1) {
        temp = (total_info_t *)malloc(sizeof(total_info_t));
        fread(temp, sizeof(total_info_t), 1, fd);
        temp->ant = NULL;
        temp->child = NULL;
        temp->sig = game_data->head; 

        for (int i = 0; i < temp->items; i++) {
            actual_coord = (plays_t *) malloc(sizeof(plays_t));
            fread(actual_coord, sizeof(plays_t), 1, fd);
            actual_coord->sig = temp->child;
            temp->child = actual_coord; 
        }

        game_data->head = temp;
        if (game_data->head->sig != NULL) {
            temp2 = game_data->head->sig;
            temp2->ant = game_data->head;
        }
    }
    fclose(fd);

    temp = game_data->head;
    
    actual_coord = temp->child;
    load_from_list(game_data, actual_coord);

    strcpy(game_data->player1, game_data->head->player1);
    strcpy(game_data->player2, game_data->head->player2);

    //print(game_data->pente_board);
}

void load_from_list(game_info_t *game_data, plays_t *head) {
    plays_t *cursor = head;
    GdkPixbuf *turn_image;

    while(cursor != NULL) {
        board(game_data->pente_board, cursor->coor_x, cursor->coor_y, cursor->token_value);
        tick_image_board(cursor, game_data);

        if (cursor == head) {
           if (cursor->token_value == VAL2)
               turn_image = gdk_pixbuf_new_from_file("imagenes/blue_token.jpg", NULL);

           if (cursor->token_value == VAL1)
               turn_image = gdk_pixbuf_new_from_file("imagenes/red_token.jpg", NULL);

           gtk_image_set_from_pixbuf(GTK_IMAGE(game_data->turn_image), turn_image);
        }

        cursor = cursor->sig;
    }
}

void save_plays(game_info_t *game_data) {
    FILE *fd;
    total_info_t *temp;
    plays_t *cursor;

    temp = game_data->head;

    while (temp != NULL && temp->sig != NULL)
        temp = temp->sig;

    if(game_data->file_name == NULL) {
        fd = fopen("juego.ice", "w");
    }

    else {
        fd = fopen(game_data->file_name, "w");
    }
    
    while (temp != NULL) {
        fwrite(temp, sizeof(total_info_t), 1, fd);
        cursor = temp->child; 

        while(cursor != NULL){
            fwrite(cursor, sizeof(plays_t), 1, fd);
            cursor = cursor->sig; 
        }

        temp = temp->ant;
    }

    fclose(fd);
}       



void enter_data(total_info_t **head) {
    total_info_t *temp, *temp2;
    temp = (total_info_t *) malloc(sizeof(total_info_t));

    temp->hit1 = (*head)->hit1;
    temp->hit2 = (*head)->hit2;
    temp->turn = (*head)->turn; 

    strcpy(temp->player1, (*head)->player1);
    strcpy(temp->player2, (*head)->player2);

    temp->ant = NULL;

    temp->sig = *head; 
    *head = temp; 
    if ((*head)->sig != NULL) {
      temp2 = (*head)->sig;
      temp2->ant = *head;
    }
}


plays_t *create_list(game_info_t *game_data) {
    game_data->head->child = NULL;
    plays_t *temp;
    int i, j, total = 0;

    for (i = 0; i < PENTEMAX; i++) {
        for (j = 0; j < PENTEMAX; j++) {
            if (game_data->pente_board[i][j] != 0) {
                temp = (plays_t *)malloc(sizeof(plays_t));
                temp->coor_x = j;
                temp->coor_y = i;
                temp->token_value = game_data->pente_board[i][j];

                temp->sig = game_data->head->child;
                game_data->head->child = temp;
                total++;
            }
        }
    }
    game_data->head->items = total; 
    return game_data->head->child;
}

void clear_history(game_info_t *first) {
    total_info_t *cursor, *temp; 
    cursor = first->head->ant; 

    while(cursor != NULL){
        erase_plays(&cursor->child); 
        temp = cursor->ant;
        free(cursor); 
        cursor = temp; 
    }
    first->head->ant = NULL; 
}

//funcion limpia lista de game
void erase_game(game_info_t *first)  {
    total_info_t *temp;
    temp = first->head;

    while (temp != NULL) {
        erase_plays(&temp->child);

        first->head = temp->sig;

        free(temp);
        temp = first->head;
    }
}

//funcion limpia lista de game
void erase_plays(plays_t **head)  {
    plays_t *temp;
    temp = *head;

    while (temp != NULL) {
        *head = temp->sig;
        free(temp);
        temp = *head;
    }
}
