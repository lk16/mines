#include "main_window.hpp"

main_window::main_window():
  table(DEFAULT_HEIGHT,DEFAULT_WIDTH),
  control(this),
  fields(DEFAULT_HEIGHT*DEFAULT_WIDTH,NULL),
  ui_file(UI_PATH + "menus.xml")
{
  init_ui();
  control.game_reset();
  show_all_children();
}


void main_window::init_ui(){
    
  this->set_default_size(400,400);
  this->set_title(Glib::ustring("Mines"));
  
  action_group = Gtk::ActionGroup::create();
  
  /* menus themselves */
  action_group->add(Gtk::Action::create("GameMenu","_Game"));
  action_group->add(Gtk::Action::create("SettingsMenu","_Settings"));

  /* Game menu */
  action_group->add(
    Gtk::Action::create("GameNew",Gtk::Stock::NEW,"_New","Start a new game"),
    sigc::mem_fun(control,&game_control::game_reset)
  );
  action_group->add(
    Gtk::Action::create("GameQuit",Gtk::Stock::QUIT,"_Quit","Quit game"),
    sigc::mem_fun(*this,&main_window::on_menu_game_quit)
  );
  
  /* Settings menu */
  action_group->add(
    Gtk::Action::create("SettingsSettings","_Settings"),
    sigc::mem_fun(*this,&main_window::on_menu_settings_settings)
  );
  
  
  ui_manager = Gtk::UIManager::create();
  ui_manager->insert_action_group(action_group);
  
  
  try{
    ui_manager->add_ui_from_file(UI_PATH + "menus.xml");
  }
  catch(const Glib::Error& ex){
    std::cerr << "Adding ui from 'menus.xml' failed: " << ex.what();
  }
  
  add(vbox);
  
  Gtk::Widget* menubar = ui_manager->get_widget("/MenuBar");
  if(menubar){
    vbox.pack_start(*menubar,Gtk::PACK_SHRINK);
  }
  
  for(int i=0;i<(int)fields.size();i++){
    int x = i % DEFAULT_WIDTH;
    int y = i / DEFAULT_WIDTH;
    fields[i] = new clickable_image(this,x,y,IMAGE_PATH + "closed.png");
    table.attach(*fields[i],x,x+1,y,y+1);
  }
  
  vbox.pack_start(aspect_frame,Gtk::PACK_EXPAND_WIDGET);
  aspect_frame.set_shadow_type(Gtk::SHADOW_NONE);
  aspect_frame.add(table);
  
  vbox.pack_start(status_bar,Gtk::PACK_SHRINK);
  
  this->set_resizable(false);
  
  show_all_children();
}

void main_window::on_menu_game_quit()
{
  Gtk::Dialog dialog("Quit?",*this);
  Gtk::Label label("Are you sure you want to quit?",0.5,0.5,false);
  dialog.get_vbox()->add(label);
  dialog.show_all_children();
  dialog.add_button(Gtk::Stock::NO,Gtk::RESPONSE_NO);
  dialog.add_button(Gtk::Stock::YES,Gtk::RESPONSE_YES);
  if(dialog.run() == Gtk::RESPONSE_YES){
    hide();
  }
}

main_window::~main_window()
{
  for(int i=0;i<(int)fields.size();i++){
    delete fields[i];
  }
}

void main_window::on_menu_settings_settings()
{
  std::cout << "settings\n";
  /*  
  settings_dialog sd(*this,input_level[BLACK],input_level[WHITE]);
  
  if(sd.run() == Gtk::RESPONSE_OK){

  }
  */
}

void main_window::update_fields()
{ 
  std::string imagefile = "";
  
  for(int i=0;i<(int)fields.size();i++){
    int x = i % DEFAULT_WIDTH;
    int y = i / DEFAULT_WIDTH;
    switch(control.get_state(x,y)){
      case FIELD_CLOSED:
        imagefile = "closed.png";
        break;
      case FIELD_FLAGGED:
        imagefile = "flag.png";
        break;
      case FIELD_OPENED:
        if(control.is_mine(x,y)){
          imagefile = "mine.png";
        }
        else{
          imagefile = tostr<int>(control.get_neighbour_mine_count(x,y)) + ".png";
        }
        break;
      default:
        CRASH;
    }
    fields[i]->set_image(IMAGE_PATH + imagefile);
    table.show_all_children();
  }
}

void main_window::update_status_bar(const std::string& text)
{
  status_bar.pop();
  status_bar.push(text);
}
