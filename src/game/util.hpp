#ifndef MINES_UTIL_HPP
#define MINES_UTIL_HPP

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>


#define LOCATION __FILE__ << ':' << __LINE__ << '\t'

#ifndef NDEBUG

  #define SHOW_VAR(a) std::cout << LOCATION << #a << " = " << (a) << std::endl 
  #define SHOW_VAR2(a,b)     SHOW_VAR(a);      SHOW_VAR(b)
  #define SHOW_VAR3(a,b,c)   SHOW_VAR2(a,b);   SHOW_VAR(c)
  #define SHOW_VAR4(a,b,c,d) SHOW_VAR3(a,b,c); SHOW_VAR(d)
  #define PING std::cout << LOCATION << "PING!\n"
  #define CONTAINS_BUG std::cout << LOCATION << "Do not use this function, it contains bugs!\n"
  #define NOT_IMPLEMENTED std::cout << LOCATION << "This is not implemented yet!\n" 
  #define CRASH std::cout << LOCATION << "I'm crashing!\n"; abort()

#else

  #define SHOW_VAR(a)
  #define SHOW_VAR2(a,b)
  #define SHOW_VAR3(a,b,c)
  #define SHOW_VAR4(a,b,c,d)
  #define PING
  #define CONTAINS_BUG
  #define NOT_IMPLEMENTED
  #define CRASH
  
#endif

/// subdirectory where images are stored
#define IMAGE_PATH std::string("./images/")

/// subdirectory where xml files containing ui are stored
#define UI_PATH std::string("./xml/")

#define DEFAULT_HEIGHT     (10)
#define DEFAULT_WIDTH      (10)
#define DEFAULT_MINE_COUNT (10)

enum{
  FIELD_CLOSED,
  FIELD_FLAGGED,
  FIELD_OPENED
};

enum{
  GAME_RESET,
  GAME_STARTED,
  GAME_LOSE,
  GAME_WIN
};


template<class T>
inline T min(T x,T y){
  return ((x<y) ? x : y);
}

template<class T>
inline T max(T x,T y){
  return ((x>y) ? x : y);
}


template<class T>
inline T abs(T x){
  return ((x<0) ? x : (-x));
}

template<class T>
inline std::string tostr(T x){
  std::stringstream buff;
  buff << x;
  return buff.str();
}

template<class T>
inline T fromstr(std::string x){
  std::stringstream buff(x);
  T temp;
  buff >> temp;
  return temp;
}

#endif
