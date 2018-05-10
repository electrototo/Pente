#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10
#define VAL1 1
#define VAL2 2
//codigo funcional

typedef struct hit_t
{
    int coordenada_y, coordenada_x;
    struct hit_t *sig;
} hit_t;

typedef struct game_info_t
{
    int hit1, hit2;
    int score1, score2;
    int turn, items;
    struct plays_t *child;
    struct game_info_t *sig, *ant;
} game_info_t;

typedef struct plays_t
{
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
/*******************************/

/***********JUGADAS*************/
void coordinates(int pente[MAX][MAX], game_info_t **head);
void file(char name[30]);
void load_plays(int pente[MAX][MAX]);
void save_plays();
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
int count_hit(int pente[MAX][MAX], int contador, hit_t **head);
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

int main() {
    Pente();
    return 0;
}

void Pente()
{
    int pente[MAX][MAX];
    int i;
    game_info_t *head = NULL;

    clear_board(pente);

    printf("\n¿Desea cargar algun juego? [Si = 0/ No = 1]\n> "); //Igual a resume playing
    scanf("%d", &i);
    if (i == 0)
        //load_plays();
        print(pente);
    coordinates(pente, &head); //funcion encargada de la parte funcional del juego
}

void clear_board(int pente[MAX][MAX])
{
    int i, j;
    for (i = 0; i < MAX; i++) //Inicializar matriz en ceros
    {
        for (j = 0; j < MAX; j++)
        {
            pente[i][j] = 0;
        }
    }
}

void load_plays(int pente[MAX][MAX]) {
    //cambiar para guardar game_info y plays_t
    int x, y, read_token_value;
    FILE *fd;
    char name[30];
    file(name);
    fd = fopen(name, "r");
    if (fd == NULL)
    {
        printf("\n<file inexistente>\n");
        return;
    }
    while (!feof(fd))
    {
        fscanf(fd, "%d|%d|%d\n", &x, &y, &read_token_value);
        pente[y][x] = read_token_value;
    }
    fclose(fd);
    printf("\n<file leido>\n");
}

void save_plays(plays_t *head)
{ //Funcion para guardar lista dinamica game_info y plays_t en un archivo
    FILE *f;
    char name[30];
    plays_t *temp;
    temp = head;
    //file(name);
    f = fopen("juego", "w");
    while (temp != NULL)
    {
        fprintf(f, "%d|%d|%d\n", temp->coor_x, temp->coor_y, temp->token_value);
        temp = temp->sig;
    }
    fclose(f);
}

void coordinates(int pente[MAX][MAX], game_info_t **head)
{
    hit_t *first = NULL; //inicializar lista de hits
    int cor_x, cor_y, jugador, contador = 1, temp_1, temp_2, hit = 0;
    int hit_uno = 0, hit_dos = 0, next;
    do
    {
        next = (contador % 2) + 1;
        jugador = (contador % 2 == 0) ? VAL2 : VAL1;

        do
        {
            printf("\nTURNO Jugador %d\n", jugador);
            printf("Coordenada x: ");
            scanf("%d", &cor_x);
            printf("Coordenada y: ");
            scanf("%d", &cor_y);
            if (cor_x < 0 || cor_x >= MAX || cor_y < 0 || cor_y >= MAX)
                printf("<Coordenada fuera de rango\n");
            if (pente[cor_y][cor_x] == 0 && pente[cor_y][cor_x] != jugador)
            {
                board(pente, cor_x, cor_y, jugador); //Marcar tablero
                if (jugador == VAL1)
                {
                    temp_1 = count(pente, VAL1);
                    hit = count_hit(pente, contador, &first);
                    if (first != NULL)
                    {
                        hit_uno = hit_uno + hit;
                        clear_hit(&first, pente, VAL2);
                    }
                    printf("\nContador filas 1 = %d\n", temp_1);
                    printf("Comidas jugador 1 = %d\n\n", hit_uno);
                }
                if (jugador == VAL2)
                {
                    temp_2 = count(pente, VAL2);
                    hit = count_hit(pente, contador, &first);
                    if (first != NULL)
                    {
                        hit_dos = hit_dos + hit;
                        clear_hit(&first, pente, VAL1);
                    }
                    printf("\nContador filas 2 = %d\n", temp_2);
                    printf("hit_t jugador 2 = %d\n", hit_dos);
                }
            }
            else
                printf("<Lugar ya ocupado>\n");
            enter_data(head, hit_uno, hit_dos, temp_1, temp_2, jugador);

            (*head)->child = create_list(pente, &(*head)->items);
            print(pente);
        } while (pente[cor_y][cor_x] != jugador && pente[cor_y][cor_x] == next);
        contador++;
    } while ((temp_1 != 2 && temp_1 != -1) && (temp_2 != 2 && temp_2 != -1));
    erase_hits(&first);
    erase_game(head);
}

void board(int pente[MAX][MAX], int x, int y, int jugador)
{
    pente[y][x] = jugador;
}

void enter_data(game_info_t **head, int comida1, int comida2, int contador1, int contador2, int jugador)
{
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
    if ((*head)->sig != NULL)
        (*head)->sig->ant = *head;
}

plays_t *create_list(int pente[MAX][MAX], int *total) {
    plays_t *head = NULL;
    plays_t *temp;
    int i, j;
    *total = 0;

    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
        {
            if (pente[i][j] != 0)
            {
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

int count(int pente[MAX][MAX], int jugador)
{ //get_moves regresa 1 para una fila de 4, 0 si no hay filas y -1 para una fila de 5
    int x, y, temp = 0;
    for (y = 0; y < MAX; y++)
        for (x = 0; x < MAX; x++)
            if ((get_moves(pente, x, y, jugador)) == -1)
                return -1;
            else
                temp += get_moves(pente, x, y, jugador);

    return temp;
}

int follow(int pente[MAX][MAX], int token_value, int x, int y, int dx, int dy, int level)
{
    if (x < 0 || x >= MAX || y < 0 || y >= MAX)
        return level;

    if (pente[y][x] != token_value || level == 5)
        return level;

    level = follow(pente, token_value, x + dx, y + dy, dx, dy, level + 1);

    return level;
}

int get_moves(int pente[MAX][MAX], int x, int y, int jugador)
{
    int total = 0, actual, token_value;

    token_value = pente[y][x];

    if (token_value != 1 && token_value != 2)
        return 0;

    // peek ahead este
    actual = follow(pente, jugador, x, y, 1, 0, 0);

    if (actual == 4)
        total++;
    if (actual == 5)
        return -1;

    // peek ahead sureste
    actual = follow(pente, jugador, x, y, 1, 1, 0);

    if (actual == 4)
        total++;
    if (actual == 5)
        return -1;

    // peek ahead sur
    actual = follow(pente, jugador, x, y, 0, 1, 0);

    if (actual == 4)
        total++;
    if (actual == 5)
        return -1;

    // peek ahead suroeste
    actual = follow(pente, jugador, x, y, -1, 1, 0);

    if (actual == 4)
        total++;
    if (actual == 5)
        return -1;

    return total;
}

int count_hit(int pente[MAX][MAX], int contador, hit_t **head)
{
    int temp = 0, x, y, token_value, next;

    next = (contador % 2) + 1;
    token_value = (contador % 2 == 0) ? VAL2 : VAL1;

    for (y = 0; y < MAX; y++)
        for (x = 0; x < MAX; x++)
            if (pente[y][x] == next)
            {
                temp += get_hits(pente, x, y, token_value, next, head);
            }

    return temp;
}

int get_hits(int pente[MAX][MAX], int x, int y, int token_value, int next, hit_t **head)
{
    int total = 0, actual;

    // peek ahead norte
    actual = follow_hits(pente, token_value, next, x, y, 0, -1, 0, head);

    if (actual == 1)
        total++;

    // peek ahead noreste
    actual = follow_hits(pente, token_value, next, x, y, 1, -1, 0, head);

    if (actual == 1)
        total++;

    // peek ahead este
    actual = follow_hits(pente, token_value, next, x, y, 1, 0, 0, head);

    if (actual == 1)
        total++;

    // peek ahead sureste
    actual = follow_hits(pente, token_value, next, x, y, 1, 1, 0, head);

    if (actual == 1)
        total++;

    // peek ahead sur
    actual = follow_hits(pente, token_value, next, x, y, 0, 1, 0, head);

    if (actual == 1)
        total++;

    // peek ahead suroeste
    actual = follow_hits(pente, token_value, next, x, y, -1, 1, 0, head);

    if (actual == 1)
        total++;

    // peek ahead oeste
    actual = follow_hits(pente, token_value, next, x, y, -1, 0, 0, head);

    if (actual == 1)
        total++;

    // peek ahead noroeste
    actual = follow_hits(pente, token_value, next, x, y, -1, -1, 0, head);

    if (actual == 1)
        total++;

    return total;
}

int follow_hits(int pente[MAX][MAX], int token_value, int next, int x, int y, int dx, int dy, int level, hit_t **head)
{
    if (x < 0 || x >= MAX || y < 0 || y >= MAX) //checa limites de la matriz
        return level;

    if (pente[y][x] != next) //si la coordenada es distinta a next_token_value se sale
        return level;

    if (level == 1)
        return 1;

    if (level == 0)
    {
        if ((pente[y - dy][x - dx] == token_value) && (pente[y + dy][x + dx] == next) && (pente[y + (dy + dy)][x + (dx + dx)] == token_value))
        {
            enter_hit(head, y, x, pente);
            printf("Llegando al nivel %d, pente[%d][%d]\n", level, y, x);
            return level + 1;
        }
        else
            return 0;
    }

    level = follow_hits(pente, token_value, next, x + dx, y + dy, dx, dy, level + 1, head);
    return level;
}

void enter_hit(hit_t **head, int y, int x, int pente[MAX][MAX])
{
    hit_t *temp;

    temp = (hit_t *) malloc(sizeof(hit_t));
    temp->coordenada_x = x;
    temp->coordenada_y = y;
    temp->sig = *head;
    *head = temp;
}

void clear_hit(hit_t **head, int pente[MAX][MAX], int jugador)
{ //borrar coordenada de la matriz
    hit_t *temp;
    temp = *head;

    while (temp != NULL)
    {
        pente[temp->coordenada_y][temp->coordenada_x] = 0;
        *head = temp->sig;
        free(temp);
        temp = *head;
    }
}

void erase_hits(hit_t **head) //funcion limpia lista de hits
{
    hit_t *temp;
    temp = *head;

    while (temp != NULL)
    {
        *head = temp->sig;
        free(temp);
        temp = *head;
    }
}

void erase_game(game_info_t **head) //funcion limpia lista de game
{
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

void erase_plays(plays_t **head) //funcion limpia lista de game
{
    plays_t *temp;
    temp = *head;

    while (temp != NULL)
    {
        *head = temp->sig;
        free(temp);
        temp = *head;
    }
}

void undo(game_info_t **head)
{
}

void redo(game_info_t **head)
{
}

void clear_history(game_info_t **head)
{
    game_info_t *cursor, *temp; 
    cursor = (*head)->ant; 
    while(cursor != NULL){
        temp = cursor->ant;
        free(cursor); 
        cursor = temp; 
    }
    (*head)->ant = NULL; 
}

void print(int pente[MAX][MAX]) //Impresion del tablero
{
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

void file(char name[30])
{
    getchar();
    printf("\nname archivo> ");

    fgets(name, 29, stdin);

    strcat(name, ".ice"); 
    strtok(name, "\n");
}

void pause()
{
    printf("\n\n\t<Pulsee ENTER para continuar...>\n");
    while (getchar() != '\n');
    system("clear");
}
