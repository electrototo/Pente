#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10
#define VAL1 1
#define VAL2 2

#define valid_range(x, y) (!(x < 0 || x >= MAX || y < 0 || y >= MAX))

typedef struct hit_t {
    int coordenada_y, coordenada_x;
    struct hit_t *sig;
} hit_t;

typedef struct game_info_t {
    int hit1, hit2;
    int score1, score2;
    int turn, items;
    struct plays_t *child;
    struct game_info_t *sig, *ant;
} game_info_t;

typedef struct plays_t {
    int coor_y, coor_x;
    int token_value;
    struct plays_t *sig;
} plays_t;

/***********GENERAL*************/
void Pente();
void clear_board(int pente[MAX][MAX]);
void board(int pente[MAX][MAX], int x, int y, int jugador);
void print(int pente[MAX][MAX]);
void pause();
void print_prueba(plays_t *head);
/*******************************/

/***********JUGADAS*************/
void coordinates(int pente[MAX][MAX], game_info_t **head);
void file(char name[30]);
void load_plays(int pente[MAX][MAX], game_info_t **head);
void save_plays(game_info_t *head);
void enter_data(game_info_t **head, int comida1, int comida2, int contador1, int contador2, int jugador);
plays_t *create_list(int pente[MAX][MAX], int *total);
void undo(game_info_t **head);
void redo(game_info_t **head);
void clear_history(game_info_t **head);
/*******************************/

/************FILAS*************/
int count(int pente[MAX][MAX], int jugador);
int get_moves(int pente[MAX][MAX], int x, int y, int jugador);
int follow(int pente[MAX][MAX], int token_value, int x, int y, int dx, int dy, int level);
/*******************************/

/***********COMIDAS*************/
int count_hit(int pente[MAX][MAX], int next, int token_value, hit_t **head);
int get_hits(int pente[MAX][MAX], int x, int y, int token_value, int next, hit_t **head);
int follow_hits(int pente[MAX][MAX], int token_value, int next, int x, int y, int dx, int dy, int level, hit_t **head);
void enter_hit(hit_t **head, int y, int x, int pente[MAX][MAX]);
void clear_hit(hit_t **head, int pente[MAX][MAX], int jugador);
/*******************************/

/***********CLEAR***************/
void erase_hits(hit_t **head);
void erase_game(game_info_t **head);
void erase_plays(plays_t **head);
/*******************************/

// validez
int valid_position(int pente[MAX][MAX], int x, int y);

int main() {
    Pente();
    printf("\nCerrando juego\n");
    return 0;
}

void Pente() {
    int pente[MAX][MAX];
    int i;
    game_info_t *head = NULL;

    clear_board(pente);

    printf("\n¿Desea cargar algun juego? [Si = 0/ No = 1]\n> "); //Igual a resume playing
    scanf("%d", &i);
    if (i == 0)
        load_plays(pente, &head);
    coordinates(pente, &head); //funcion encargada de la parte funcional del juego
}

void clear_board(int pente[MAX][MAX]) {
    memset(pente, 0, sizeof(int) * MAX * MAX);
}

void coordinates(int pente[MAX][MAX], game_info_t **head) {
    hit_t *first = NULL; //inicializar lista de hits
    game_info_t *cursor; 
    int cor_x, cor_y, jugador, contador = 1, filas_1 = 0, filas_2 = 0, hit = 0;
    int hit_uno = 0, hit_dos = 0, next;

    int filas;

    print(pente);

    do {
        next = (contador % 2) + 1;
        jugador = (contador % 2 == 0) ? VAL2 : VAL1;

        printf("\nTURNO Jugador %d\n", jugador);
        printf("Coordenada x: ");
        scanf("%d", &cor_x);
        printf("Coordenada y: ");
        scanf("%d", &cor_y);

        if (!valid_range(cor_x, cor_y))
            printf("<Coordenada fuera de rango\n");

        else if (valid_position(pente, cor_x, cor_y)) {
            board(pente, cor_x, cor_y, jugador);

            filas = count(pente, jugador);
            printf("contar filas\n");

            if (jugador == VAL1)
                filas_1 = filas;
            else
                filas_2 = filas;

            hit_uno += count_hit(pente, next, jugador, &first);
            if (first != NULL)
                clear_hit(&first, pente, next);

            hit_dos += count_hit(pente, jugador, next, &first);
            if (first != NULL)
                clear_hit(&first, pente, jugador);

            printf("\nContador filas 1  = %d\n", filas_1);
            printf("Comidas jugador 1   = %d\n\n", hit_uno);
            printf("Contador filas 2   = %d\n", filas_2);
            printf("Comidas jugador 2   = %d\n\n", hit_dos);
        }
        else
            printf("<Lugar ya ocupado>\n");

        if(*head != NULL){
            cursor = (*head)->ant;
            if(cursor != NULL) {
                clear_board(pente);
                clear_history(head);        
            }
        }
        enter_data(head, hit_uno, hit_dos, filas_1, filas_2, jugador);
        (*head)->child = create_list(pente, &(*head)->items);
        print_prueba((*head)->child);
        save_plays(*head);
        contador++;

        print(pente);
    } while ((filas_1 != 1 && filas_1 != -1) && (filas_2 != 5 && filas_2 != -1) && contador < (MAX*MAX));

    save_plays(*head);
    erase_hits(&first);
    erase_game(head);
}

int valid_position(int pente[MAX][MAX], int x, int y) {
    return valid_range(x, y) && pente[y][x] != VAL1 && pente[y][x] != VAL2;
}

void load_plays(int pente[MAX][MAX], game_info_t **head) {
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

//Funcion para guardar lista dinamica game_info y plays_t en un archivo
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

void board(int pente[MAX][MAX], int x, int y, int jugador) {
    pente[y][x] = jugador;
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

plays_t *create_list(int pente[MAX][MAX], int *total) {
    plays_t *head = NULL;
    plays_t *temp;
    int i, j;
    *total = 0;

    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
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

//get_moves regresa 1 para una fila de 4, 0 si no hay filas y -1 para una fila de 5
int count(int pente[MAX][MAX], int jugador) {
    int x, y, temp = 0;
    for (y = 0; y < MAX; y++)
        for (x = 0; x < MAX; x++)
            if ((get_moves(pente, x, y, jugador)) == -1)
                return -1;
            else
                temp += get_moves(pente, x, y, jugador);

    return temp;
}

int follow(int pente[MAX][MAX], int token_value, int x, int y, int dx, int dy, int level) {
    if (!valid_range(x, y))
        return level;

    if (pente[y][x] != token_value || level == 5)
        return level;

    level = follow(pente, token_value, x + dx, y + dy, dx, dy, level + 1);

    return level;
}

int get_moves(int pente[MAX][MAX], int x, int y, int jugador) {
    int total = 0, actual, token_value;

    token_value = pente[y][x];

    if (token_value != 1 && token_value != 2)
        return 0;

    int directions[4][2] = {
        {1, 0}, {1, 1},
        {0, 1}, {-1, 1}
    };

    for (int i = 0; i < 4; i++) {
        actual = follow(pente, jugador, x, y, directions[i][0], directions[i][1], 0);

        if (actual == 4)
            total++;

        if (actual == 5)
            return -1;
    }

    return total;
}

int count_hit(int pente[MAX][MAX], int next, int token_value, hit_t **head) {
    int temp = 0, x, y;

    for (y = 0; y < MAX; y++)
        for (x = 0; x < MAX; x++)
            if (pente[y][x] == next)
                temp += get_hits(pente, x, y, token_value, next, head);

    return temp;
}

int get_hits(int pente[MAX][MAX], int x, int y, int token_value, int next, hit_t **head) {
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

int follow_hits(int pente[MAX][MAX], int token_value, int next, int x, int y, int dx, int dy, int level, hit_t **head) {
    if (x < 0 || x >= MAX || y < 0 || y >= MAX) //checa limites de la matriz
        return level;

    if (pente[y][x] != next) //si la coordenada es distinta a next_token_value se sale
        return level;

    if (level == 1)
        return 1;

    if (level == 0) {
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

void enter_hit(hit_t **head, int y, int x, int pente[MAX][MAX]) {
    hit_t *temp;

    temp = (hit_t *) malloc(sizeof(hit_t));
    temp->coordenada_x = x;
    temp->coordenada_y = y;
    temp->sig = *head;
    *head = temp;
}

//borrar coordenada de la matriz
void clear_hit(hit_t **head, int pente[MAX][MAX], int jugador) { 
    hit_t *temp;
    temp = *head;

    while (temp != NULL) {
        pente[temp->coordenada_y][temp->coordenada_x] = 0;
        *head = temp->sig;
        free(temp);
        temp = *head;
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

//funcion limpia lista de game
void erase_game(game_info_t **head)  {
    game_info_t *temp;
    temp = *head;

    while (temp != NULL)
    {
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

    while (temp != NULL)
    {
        *head = temp->sig;
        free(temp);
        temp = *head;
    }
}

void undo(game_info_t **head) {
    *head = (*head)->sig;
}

void redo(game_info_t **head) {
    *head = (*head)->ant;
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

//Impresion del tablero
void print(int pente[MAX][MAX])  {
    int i, j;
    printf("    ");
    for (i = 0; i < MAX; i++)
    {
        printf(" %d ", i);
    }
    printf("\n");
    for (i = 0; i < MAX; i++)
    {
        printf(" %d |", i);
        for (j = 0; j < MAX; j++)
        {
            printf(" %d|", pente[i][j]);
        }
        printf("\n");
    }
}

void file(char name[30]) {
    getchar();
    printf("\nFile archivo> ");
    fgets(name, 29, stdin);

    strcat(name, ".ice"); 
    strtok(name, "\n");
}

void pause() {
    printf("\n\n\t<Pulsee ENTER para continuar...>\n");
    while (getchar() != '\n');
    system("clear");
}

void print_prueba(plays_t *head){
    while (head != NULL) {
        printf("Nodo %p\n", head);
        printf("  sig: %p\n", head->sig);
        printf("X = %d, Y = %d\n", head->coor_x, head->coor_y);
        head = head->sig;
    }       
}