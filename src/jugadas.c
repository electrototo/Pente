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
    int contador = 1, next;

    int filas;
    next = (turno == VAL1) ? VAL2 : VAL1;

    if (valid_position(pente, cor_x, cor_y)) {
        board(pente, cor_x, cor_y, turno);

        game_data->score1 = count(pente, VAL2);
        game_data->score2 = count(pente, VAL1);

        game_data->hit1 += count_hit(pente, VAL1, VAL2, &first);
        if (first != NULL)
            clear_hit(&first, pente, next, game_data);

        game_data->hit2 += count_hit(pente, VAL2, VAL1, &first);
        if (first != NULL) {
            clear_hit(&first, pente, turno, game_data);
        }

        printf("\nContador filas 1  = %d\n", game_data->score1);
        printf("Comidas jugador 1   = %d\n\n", game_data->hit1);
        printf("Contador filas 2   = %d\n", game_data->score2);
        printf("Comidas jugador 2   = %d\n\n", game_data->hit2);
    }
    else
        printf("<Lugar ya ocupado>\n");

    // Segmentation fault aqui
    //if(*head != NULL){
    //    cursor = (*head)->ant;
    //    if(cursor != NULL) {
    //        clear_board(pente);
    //        clear_history(head);        
    //    }
    //}
    //enter_data(head, hit_uno, hit_dos, filas_1, filas_2, turno);
    //(*head)->child = create_list(pente, &(*head)->items);
    //print_prueba((*head)->child);
    //save_plays(*head);
    contador++;

    print(pente);

    //acomodar
    // save_plays(*head);
    // erase_hits(&first);
    // erase_game(head);
}

void file(char name[30]) {
    getchar();
    printf("\nFile archivo> ");
    fgets(name, 29, stdin);

    strcat(name, ".ice"); 
    strtok(name, "\n");
}

void load_plays(int **pente, game_info_t **head) {
    FILE *fd;
    char name[30];
    game_info_t *temp, *temp2;
    plays_t *actual_coord;
    file(name);
    fd = fopen(name, "r");
    if (fd == NULL) {
        printf("\n<nonexistent file>\n");
        return;
    }
    while (!feof(fd)) {
        temp = (game_info_t *)malloc(sizeof(game_info_t));
        fread(temp, sizeof(game_info_t), 1, fd);
        printf("comida 1 = %d\n", temp->hit1);
        printf("comida 2 = %d\n", temp->hit2); 
        printf("score 1 = %d\n", temp->score1);
        printf("score2 = %d\n", temp->score2);
        printf("Items = %d\n", temp->items);
        printf("turno = %d\n", temp->turn);
        //fread(cursor, sizeof(cursor), temp->items, fd);
        for (int i = 0; i < temp->items; i++) {
            actual_coord = (plays_t *) malloc(sizeof(plays_t));
            fread(actual_coord, sizeof(plays_t), 1, fd);
            printf("\tX = %d Y = %d\n", actual_coord->coor_x, actual_coord->coor_y);
            printf("\tJugador %d\n", actual_coord->token_value);
        }
        printf("fin\n");
        //temp->sig = *head; 
        //temp->ant = NULL;
    }
    fclose(fd);
    printf("\n<file loaded>\n");
}

void save_plays(game_info_t *head) {
    FILE *fd;
    char name[30];
    game_info_t *temp;
    plays_t *cursor;
    temp = head;
    //file(name);
    fd = fopen("juego.ice", "w");
    while (temp != NULL)
    {
        fwrite(temp, sizeof(temp), 1, fd);
        printf("temp items = %d\n", temp->items);
        printf("temp turn = %d\n", temp->turn);
        cursor = temp->child; 
        while(cursor != NULL){
            fwrite(cursor, sizeof(cursor), 1, fd);
            printf("cursor jugador = %d\n", cursor->token_value);
            cursor = cursor->sig; 
        }
        temp = temp->sig;
    }
    fclose(fd);
}

void enter_data(game_info_t **head, int comida1, int comida2, int contador1, int contador2, int jugador) {
    game_info_t *temp, *temp2;
    temp = (game_info_t *)malloc(sizeof(game_info_t));
    temp->hit1 = comida1;
    temp->hit2 = comida2;
    temp->score1 = contador1;
    temp->score2 = contador2;
    temp->turn = jugador;
    temp->sig = *head;
    temp->ant = NULL;

    *head = temp;
    if ((*head)->sig != NULL) {
        temp2 = (*head)->sig;
        temp2->ant = *head;
    }
}

plays_t *create_list(int **pente, int *total) {
    plays_t *head = NULL;
    plays_t *temp;
    int i, j;
    *total = 0;

    for (i = 0; i < PENTEMAX; i++) {
        for (j = 0; j < PENTEMAX; j++) {
            if (pente[i][j] != 0) {
                temp = (plays_t *)malloc(sizeof(plays_t));
                temp->coor_x = j;
                temp->coor_y = i;
                temp->token_value = pente[i][j];

                temp->sig = head;
                head = temp;
                (*total)++;
            }
        }
    }
    return head;
}

void clear_history(game_info_t **head) {
    game_info_t *cursor, *temp; 
    cursor = (*head)->ant; 
    while(cursor != NULL){
        temp = cursor->ant;
        free(cursor); 
        cursor = temp; 
    }
    (*head)->ant = NULL; 
}

//funcion limpia lista de game
void erase_game(game_info_t **head)  {
    game_info_t *temp;
    temp = *head;

    while (temp != NULL) {
        erase_plays(&(*head)->child);
        *head = temp->sig;
        free(temp);
        temp = *head;
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
