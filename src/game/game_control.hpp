#ifndef MINES_GAMECONTROL_HPP
#define MINES_GAMECONTROL_HPP

#include <ctime>
#include <set>
#include <stdlib.h>

#include "game/util.hpp"

#define FIELD_CLOSED (0)
#define FIELD_FLAGGED (1)
#define FIELD_OPENED (2)

class main_window;

class game_control{
  
  
  bool dead;
  int height,width,mine_count;
  std::set<int> mines;
  int* field_state;
  main_window* mw;
  
public:
  game_control(main_window* _mw);
  ~game_control();
  
  void die();
  void game_reset();
  bool is_dead() const;
  
  bool is_mine(int x,int y) const;
  
  void toggle_flagged(int x,int y);
  void open_field(int x,int y);
  int get_state(int x,int y) const;
  
  
  int get_height() const;
  int get_width() const;
  int get_mine_count() const;
  int get_neighbour_mine_count(int x,int y) const;
  int get_neighbour_flag_count(int x,int y) const;
  
};


#endif
