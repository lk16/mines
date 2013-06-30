#ifndef MINES_GAMECONTROL_HPP
#define MINES_GAMECONTROL_HPP

#include <ctime>
#include <set>
#include <stdlib.h>

#include "game/util.hpp"

class main_window;

class game_control{
  
  bool dead;
  int height,width,mine_count,game_state;
  int* field_state;
  std::set<int> mines;
  main_window* mw;
  
public:
  game_control(main_window* _mw);
  ~game_control();
  
  void game_reset();
  void toggle_flagged(int x,int y);
  void open_field(int x,int y);
  
  bool is_mine(int x,int y) const;
  
  int get_field_state(int x,int y) const;
  int get_game_state() const;
  bool test_game_won() const;
  
  int get_height() const;
  int get_width() const;
  int get_mine_count() const;
  
  int get_neighbour_mine_count(int x,int y) const;
  int get_neighbour_flag_count(int x,int y) const;
  
  
};


#endif
