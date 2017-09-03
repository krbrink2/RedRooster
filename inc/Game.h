#ifndef GAME_H
#define GAME_H
#include "GameState.h"
#include "Noncopyable.h"
#include <stack>

#define GAME_WINDOW_WIDTH   (800)
#define GAME_WINDOW_HEIGHT  (600)

class Game : public Noncopyable 
{
public:
  Game();
  ~Game();
  int clear();

  /*void startClock();
  void pauseClock();
  void resetClock();*/

  void pushGameState(GameState* state);
  void popGameState();
  // Elegently end game
  void endGame();
  void takeInput(sf::Event event);
  void draw();
  void drawSprite(sf::Drawable& sprite);
  void update();

  bool isRunning();

  int gameWindowWidth_  = GAME_WINDOW_WIDTH;
  int gameWindowHeight_ = GAME_WINDOW_HEIGHT;

// private:
  sf::Clock clock_;
  sf::RenderWindow window_;
  sf::Font font_;
  bool run_;
  std::stack<GameState*> gameStatePtrStack_;
  
};



#endif
