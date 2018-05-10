#ifndef MENUH
#define MENUH

#include <gtk/gtk.h>
#include "pente_types.h"

GtkWidget *create_menubar();
GtkWidget *create_toolbar();
GtkWidget *create_menu_item(GtkWidget *parent, menu_item_dt info);
GtkToolItem *create_toolbar_item(GtkWidget *parent, tool_item_dt info);
void create_menu_from_array(GtkWidget *parent_item, menu_item_dt *items, int size);

#endif
