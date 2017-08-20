#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Globals.h"
#include "MainMenuState.h"
#include "MenuState.h"

int main(int argc, char* argv[]){
  // Prep for main loop
  // Ticks to skip
  sf::Time skipTime = sf::milliseconds(SKIP_TICKS);

  // Set up game
  //Gbl::game.pushGameState(new GameplayState());
  Gbl::game.pushGameState(new MainMenuState());

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
