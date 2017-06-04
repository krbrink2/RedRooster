#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include "Game.h"
#include "GameState.h"

#define FRAMES_PER_SECOND (25)
#define SKIP_TICKS (1000/FRAMES_PER_SECOND)

Game game;

int main(){

  // Ticks to skip
  sf::Time skipTime = sf::milliseconds(SKIP_TICKS);

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()){
    // Get events
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Sleep
    while(game.clock.getElapsedTime() < skipTime){
      ; // Skip
    }
    game.clock.restart();

    // Update game

    // Draw game
    window.clear();
    window.draw(shape);
    window.display();

    }

  return 0;
}
