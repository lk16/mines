#ifndef MINES_UTIL_HPP
#define MINES_UTIL_HPP

#include <cassert>
#include <cstdlib>
#include <cmath>
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

/// size of othello field, assuming width==height
#define FIELD_SIZE (8)

/// total number of fields 
#define TOTAL_FIELDS (FIELD_SIZE*FIELD_SIZE)

/// perfect score factor
#define EXACT_SCORE_FACTOR (1000)

/// heighest possible heuristic value
#define MAX_HEURISTIC (EXACT_SCORE_FACTOR * TOTAL_FIELDS)

/// lowest possible heuristic value
#define MIN_HEURISTIC (-1 * MAX_HEURISTIC)

enum color{
  BLACK = 0,
  WHITE = 1,
  EMPTY = 2
};

inline color opponent(color c){
  assert(c==WHITE || c==BLACK);
  return ((c==BLACK) ? WHITE : BLACK);
}

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

/* returns with high probablility values close to min */
inline int rand_exp(int min,int max,double rate){
  return min + (max-min)*(std::log(1.0-(rand()/(double)RAND_MAX))/(-rate));
}

#endif