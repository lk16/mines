#include <glib-object.h>
#include <gtk/gtk.h>

GtkWidget* main_window_new(void){
  GtkWidget *res,*menubar,*vbox,*gamemenu,*gamemenulabel;
  GtkWidget *gamemenu_new,*gamemenu_scores,*gamemenu_quit;
  
  res = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title((GtkWindow*)res,"Minesweeper");
  gtk_window_resize((GtkWindow*)res,200,200);  
  gtk_window_set_position((GtkWindow*)res, GTK_WIN_POS_CENTER);
  
  vbox = gtk_vbox_new(0,0);
  gtk_container_add((GtkContainer*)res,vbox);
  
  menubar = gtk_menu_bar_new();
  gtk_box_pack_start((GtkBox*)vbox,menubar,0,0,0);
  
  gamemenulabel = gtk_menu_item_new_with_label("Game");
  gtk_menu_shell_append((GtkMenuShell*)menubar,gamemenulabel);
  
  gamemenu = gtk_menu_new();
  gtk_menu_item_set_submenu((GtkMenuItem*)gamemenulabel,gamemenu);
  
  gamemenu_new = gtk_menu_item_new_with_label("New");
  gtk_menu_shell_append((GtkMenuShell*)gamemenu,gamemenu_new);
  gamemenu_scores = gtk_menu_item_new_with_label("Scores");
  gtk_menu_shell_append((GtkMenuShell*)gamemenu,gamemenu_scores);
  gamemenu_quit = gtk_menu_item_new_with_label("Quit");
  gtk_menu_shell_append((GtkMenuShell*)gamemenu,gamemenu_quit);
  
  g_signal_connect_swapped((GObject*)res,"destroy",G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect_swapped((GObject*)gamemenu_quit,"activate",G_CALLBACK(gtk_main_quit), NULL);
  return res;
}



int main(int argc,char** argv){
  GtkWidget* main_window;
  
  gtk_init(&argc,&argv);

  main_window = main_window_new();
  gtk_widget_show_all(main_window);
  
  gtk_main();
  return 0;
}
