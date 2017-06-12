#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Globals.h"
// #include "Game.h"
// #include "GameState.h"

Game Glb::game;
std::vector< std::vector<bool[2]> > Glb::maze;

int main(){
  // Prep for main loop
  // Ticks to skip
  sf::Time skipTime = sf::milliseconds(SKIP_TICKS);
  
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (Glb::game.window_.isOpen()){  // Main loop
    // Get events
    sf::Event event;
    while (Glb::game.window_.pollEvent(event)){
      if (event.type == sf::Event::Closed)
      {
        Glb::game.window_.close();
      }
      else
      {
        Glb::game.takeInput(event);
      }
    }

    // Sleep
    while(Glb::game.clock_.getElapsedTime() < skipTime){
      ; // Skip
    }
    Glb::game.clock_.restart();

    // Update game

    // Draw game
    Glb::game.window_.clear();
    Glb::game.window_.draw(shape);
    Glb::game.window_.display();

    }

  return 0;
}
