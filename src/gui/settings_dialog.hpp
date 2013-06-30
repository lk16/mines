#ifndef MINES_SETTINGS_DIALOG_HPP
#define MINES_SETTINGS_DIALOG_HPP

#include <gtkmm/dialog.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/scale.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>

class settings_dialog:
  public Gtk::Dialog
{

public:
  settings_dialog(Gtk::Window& parent,int width,int height,int mines_count);
  void collect_data(int* width,int* height,int* mines_count);
  
  
};

#endif