
#ifndef GLOBALS_H
#define GLOBALS_H
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"


#define FRAMES_PER_SECOND   (25)
#define SKIP_TICKS          (1000/FRAMES_PER_SECOND)
#define GAME_TITLE          "Red Rooster"
#define LARGE_ROOSTER       "assets/rooster.png"
#define ICON                "assets/icon.png"

namespace Glb{

  extern Game game;
  extern std::vector< std::vector<bool[2]> > maze;

}



#endif