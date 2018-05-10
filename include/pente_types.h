/*
 * Pente types
 * Escrito por Cristobal Liendo <cristobal@liendo.net>
*/


#ifndef PTYPESH
#define PTYPESH

#define RESPONSE_OPEN 1
#define RESPONSE_CANCEL 2

typedef struct image_data_t{
    GtkWidget *image;
    int x, y;

    struct game_info_t *game_info;
} image_data_t;

typedef struct game_info_t {
    int turn;
    int player1_p, player2_p;
    int ccount_1, ccount_2;

    GtkWidget *main_board;
    GtkWidget *turn_image, *turn_label;
    GtkWidget *points1_label, *points2_label;
} game_info_t;

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

#endif
