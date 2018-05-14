#ifndef MENUH
#define MENUH

#include <gtk/gtk.h>
#include "pente_types.h"

/**
* Crea el menú de la ventama principal.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param data Contiene la información del juego.
* @return menu_bar El menú de la ventana principal.
**/
GtkWidget *create_menubar(gpointer data);

/**
* Crea la barra de herramientas de íconos con las funciones del menú.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param data Contiene la información del juego.
* @return toolbar Barra de herramientas.
**/
GtkWidget *create_toolbar(gpointer data);

/**
* Crea un item y lo agrega al menú.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *parent Apuntador al inicio del menú
* @param info Información del item.
* @return item El item creado.
**/
GtkWidget *create_menu_item(GtkWidget *parent, menu_item_dt info);

/**
* Crea un item y lo agrega a la barra de herramientas.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *parent Apuntador al inicio del menú
* @param info Información del item.
* @return tool_item El item creado en la barra de herramientas.
**/
GtkToolItem *create_toolbar_item(GtkWidget *parent, tool_item_dt info);

/**
* Crea el menú de un arreglo.
* 
* @author Estibaliz Cano, Isabel León, Cristobal Liendo
* @param *parent_item Apuntador al item de inicio del menú.
* @param *items Apuntador a los items del menú.
* @param size Tamaño del arreglo.
* @return void
**/
void create_menu_from_array(GtkWidget *parent_item, menu_item_dt *items, int size);

#endif
