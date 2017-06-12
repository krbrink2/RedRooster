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
  
  // To be removed:
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  // Set up game
  GameplayState* gamestate = new GameplayState();
  Glb::game.pushGameState(gamestate);

  while (Glb::game.run_){  // Main loop
    // Get events
    sf::Event event;
    while (Glb::game.window_.pollEvent(event)){
      if (event.type == sf::Event::Closed)
      {
        Glb::game.clear();
      }
      else
      {
        Glb::game.takeInput(event);
      }
    }

    // Update Game

    // Draw game
    Glb::game.window_.clear();
    Glb::game.window_.draw(shape);

    // Sleep
    while(Glb::game.clock_.getElapsedTime() < skipTime){
      ; // Skip
    }
    Glb::game.clock_.restart();

    // Display game
    Glb::game.window_.display();

    }

  return 0;
}
