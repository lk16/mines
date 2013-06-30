#include "gui_base/clickable_image.hpp"
#include "gui/main_window.hpp"

clickable_image::clickable_image(main_window* par, int _x,int _y, const std::string& imagefile): 
  Gtk::EventBox(),
  image(imagefile),
  x(_x),
  y(_y),
  parent(par)
{
  add(image);
  show_all_children();
}

bool clickable_image::on_button_press_event(GdkEventButton* _event)
{
  if(parent->control.is_dead()){
    return true;
  }
  
  switch(_event->button){ // left click
    case 1: 
      // left click
      parent->control.open_field(x,y);
      break;
    case 3: 
      // right click
      parent->control.toggle_flagged(x,y);
      break;
    default: 
      // do nothing
      break;
  }
  parent->update_fields();
  return true;
}

void clickable_image::set_image(const std::string& filename)
{
  image.set(filename);
}

clickable_image::~clickable_image()
{
}

