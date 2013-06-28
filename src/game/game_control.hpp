#ifndef MINES_GAMECONTROL_HPP
#define MINES_GAMECONTROL_HPP

#include <set>

class main_window;

class game_control{
  
  game_control(main_window* mw);
  ~game_control();
  
  bool dead;
  int height,width;
  std::set<int> mines,flagged;
  
public:
  void die();
  void game_reset();
  bool is_dead() const;
  
  bool is_mine(int x,int y) const;
  
  void toogle_flagged(int x,int y);
  bool is_flagged(int x,int y) const;
  
};


#endif
