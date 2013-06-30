#ifndef MINES_FIELD_HPP
#define MINES_FIELD_HPP

#include <boost/bind.hpp>

#include <gtkmm/eventbox.h>
#include <gtkmm/image.h>

#include "gui/main_window.hpp"
#include "game/util.hpp"

class main_window;

class clickable_image:
  public Gtk::EventBox
{
  //aspect_scaling_image image; // << did not work properly
  Gtk::Image image;
  int x,y;
  main_window* parent;
  
public: 
  clickable_image(main_window* par,int _x,int _y,const std::string& imagefile);
  ~clickable_image();
  
  virtual bool on_button_press_event(GdkEventButton* event);
  
  void set_image(const std::string& filename);
};
#endif