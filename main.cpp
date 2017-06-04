#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Globals.h"
// #include "Game.h"
// #include "GameState.h"

Game game;

int main(){
  // Prep for main loop
  // Ticks to skip
  sf::Time skipTime = sf::milliseconds(SKIP_TICKS);
  //game.window = sf::RenderWindow(sf::VideoMode(200, 200), GAME_TITLE, sf::Style::Fullscreen);
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (game.window.isOpen()){  // Main loop
    // Get events
    sf::Event event;
    while (game.window.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        game.window.close();
    }

    // Sleep
    while(game.clock.getElapsedTime() < skipTime){
      ; // Skip
    }
    game.clock.restart();

    // Update game

    // Draw game
    game.window.clear();
    game.window.draw(shape);
    game.window.display();

    }

  return 0;
}
