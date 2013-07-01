#include "game/game_control.hpp"
#include "gui/main_window.hpp"

game_control::game_control(main_window* _mw):
  mw(_mw)
{
  width = DEFAULT_WIDTH;
  height = DEFAULT_HEIGHT;
  mine_count = DEFAULT_MINE_COUNT;
  game_state = GAME_RESET;
  field_state = new int[width*height];
  srand(std::time(NULL));
  // no game_reset here, this is being done in main_window ctor
}

game_control::~game_control()
{
  delete field_state;
}

void game_control::game_reset()
{
  dead = false;
  mines.clear();
  while((int)mines.size() < mine_count){
    mines.insert(rand() % (width*height));
  }
  for(int i=0;i<(width*height);++i){
    field_state[i] = FIELD_CLOSED;
  }
  game_state = GAME_RESET;
  mw->update_fields();
}

void game_control::toggle_flagged(int x, int y)
{
  if(x<0 || y<0 || x>=width || y>=height || game_state!=GAME_STARTED){
    return;
  }
  int* target = &field_state[x + width*y];
  switch(*target){
    case FIELD_OPENED: 
      return;
    case FIELD_CLOSED: 
      *target = FIELD_FLAGGED; 
      break;
    case FIELD_FLAGGED: 
      *target = FIELD_CLOSED;
      break;
    default: 
      CRASH;
  }
}

bool game_control::is_mine(int x, int y) const
{
  if(x<0 || y<0 || x>=width || y>=height){
    return false;
  }
  return mines.find(x + width*y) != mines.end();
}

int game_control::get_field_state(int x, int y) const
{
  return field_state[x + width*y];
}

void game_control::open_field(int x, int y)
{
  switch(game_state){
    case GAME_RESET: 
      game_state = GAME_STARTED;
      break;
    case GAME_LOSE:
    case GAME_WIN:
      return; // do nothing
    case GAME_STARTED: 
      break; // listed for completeness 
  }
  if(x<0 || y<0 || x>=width || y>=height){
    return;
  }
  int* target = &field_state[x + width*y];
  switch(*target){
    case FIELD_CLOSED:
      *target = FIELD_OPENED;
      if(is_mine(x,y)){
        game_state = GAME_LOSE;
        return;
      }
      if(get_neighbour_mine_count(x,y)==0){
        for(int dx=-1;dx<=1;dx++){
          for(int dy=-1;dy<=1;dy++){
            open_field(x+dx,y+dy);
          }
        }
      }
      if(test_game_won()){
        game_state = GAME_WIN;
      }
      break;
    case FIELD_FLAGGED:
      // do nothing
      break;
    case FIELD_OPENED:
      break;
    default:
      CRASH;
  }
}

int game_control::get_height() const
{
  return height;
}

int game_control::get_mine_count() const
{
  return mine_count;
}

int game_control::get_width() const
{
  return width;
}

int game_control::get_neighbour_mine_count(int x, int y) const
{
  int res = 0;
  for(int dx=-1;dx<=1;dx++){
    for(int dy=-1;dy<=1;dy++){
      if((dx!=0 || dy!=0) && is_mine(x+dx,y+dy)){
        res++;
      }
    }
  }
  return res;
}

int game_control::get_game_state() const
{
  return game_state;
}

bool game_control::test_game_won() const
{
  for(int y=0;y<height;y++){
    for(int x=0;x<width;x++){
      if(get_field_state(x,y)==FIELD_CLOSED && !is_mine(x,y)){
        return false;
      }
    }
  }
  return true;
}

