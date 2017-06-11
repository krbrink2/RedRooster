#include "Game.h"
#include "Globals.h"

// Constructor
Game::Game():
	window(sf::VideoMode(200, 200), GAME_TITLE, sf::Style::Fullscreen),
	run(true){
}

// Copy constructor
Game::Game(Game& rhs){
	run_ = rhs.run;
	gameStateStack_ = rhs.GameStateStack;
	clock_ = rhs.clock;
}

// Assignment operator
Game& Game::operator=(Game& rhs){
	run_ = rhs.run;
	gameStateStack_ = rhs.GameStateStack;
	clock_ = rhs.clock;
	return *this;
}

// Destructor
Game::~Game(){
	//@TODO
}