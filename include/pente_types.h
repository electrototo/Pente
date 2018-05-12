/*
 * Pente types
 * Escrito por Cristobal Liendo <cristobal@liendo.net>
*/
#ifndef PTYPESH
#define PTYPESH

#include <gtk/gtk.h>

#define RESPONSE_OPEN 1
#define RESPONSE_CANCEL 2

#define PENTEMAX 20
#define VAL1 1
#define VAL2 2

#define valid_range(x, y) (!(x < 0 || x >= PENTEMAX || y < 0 || y >= PENTEMAX))

typedef struct image_data_t{
    GtkWidget *image;
    int x, y;

    struct game_info_t *game_info;
} image_data_t;

typedef struct menu_item_dt {
    char label[15];
    void (*callback)(GtkWidget *, gpointer);
    gpointer data;
} menu_item_dt;

typedef struct tool_item_dt {
    gchar stock_id[50];
    void (*callback)(GtkWidget *, gpointer);
    gpointer data;
} tool_item_dt;

// parte funcional
typedef struct hit_t {
    int coordenada_y, coordenada_x;
    struct hit_t *sig;
} hit_t;

typedef struct game_info_t {
    int hit1, hit2;
    int score1, score2;
    int turn, items;

    struct plays_t *child;
    struct game_info_t *sig, *ant, **head;

    GtkWidget *main_board;
    GtkWidget *turn_image, *turn_label;
    GtkWidget *points1_label, *points2_label;

    int **pente_board;
    image_data_t ***positions;
} game_info_t;

typedef struct plays_t {
    int coor_y, coor_x;
    int token_value;
    struct plays_t *sig;
} plays_t;

#endif
