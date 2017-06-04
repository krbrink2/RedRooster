#include "Game.h"
#include "Globals.h"

// Constructor
Game::Game():
	window(sf::VideoMode(200, 200), GAME_TITLE, sf::Style::Fullscreen),
	run(true){
}

Game::Game(Game& rhs){
	run = rhs.run;
	GameStateStack = rhs.GameStateStack;
	clock = rhs.clock;
}

Game& Game::operator=(Game& rhs){
	run = rhs.run;
	GameStateStack = rhs.GameStateStack;
	clock = rhs.clock;
	return *this;
}

Game::~Game(){
	//@TODO
}