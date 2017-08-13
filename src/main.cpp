#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Globals.h"
#include "GameplayState.h"

int main(){
  // Prep for main loop
  // Ticks to skip
  sf::Time skipTime = sf::milliseconds(SKIP_TICKS);
  
  // To be removed:


  // Set up game
  Gbl::game.pushGameState(new GameplayState());

  while (Gbl::game.run_){  // Main loop
    // Get events
    sf::Event event;
    while (Gbl::game.window_.pollEvent(event)){
      if (event.type == sf::Event::Closed)
      {
        Gbl::game.clear();
        return 0;
      }
      else
      {
        Gbl::game.takeInput(event);
      }
    }

    // Update Game
    Gbl::game.update();

    // Check to see if game has ended.
    if(!Gbl::game.isRunning())
    {
      Gbl::game.clear();
      return 0;
    }


    // Draw game
    Gbl::game.draw();

    // Sleep
    while(Gbl::game.clock_.getElapsedTime() < skipTime){
      ; // Skip
    }
    Gbl::game.clock_.restart();

    // Display game
    Gbl::game.window_.display();

    }

  return 0;
}
