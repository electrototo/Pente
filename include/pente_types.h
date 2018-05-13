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

typedef struct name_packet_t {
    struct game_info_t *game_data;
    GtkWidget *player1, *player2;
} name_packet_t;

// parte funcional
typedef struct hit_t {
    int coordenada_y, coordenada_x;
    struct hit_t *sig;
} hit_t;

typedef struct game_info_t{
  GtkWidget *main_board;
  GtkWidget *turn_image, *turn_label;
  GtkWidget *points1_label, *points2_label;

  GtkWidget *p1_label1, *p2_label1;
  GtkWidget *p1_label2, *p2_label2;

  char player1[50], player2[50];
  char *file_name;
  
  int **pente_board;
  image_data_t ***positions;
  struct total_info_t *head; 
}game_info_t;

typedef struct total_info_t {
    int hit1, hit2;
    int score1, score2;
    int turn, items;

    char player1[50], player2[50];

    struct plays_t *child;
    struct total_info_t *sig, *ant;
} total_info_t;

typedef struct plays_t {
    int coor_y, coor_x;
    int token_value;
    struct plays_t *sig;
} plays_t;

#endif
