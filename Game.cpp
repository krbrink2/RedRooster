#include "Game.h"
#include "Globals.h"

// Constructor
Game::Game():
	window_(sf::VideoMode(200, 200), GAME_TITLE),//, sf::Style::Fullscreen),
	run_(true){
}

// Copy constructor
Game::Game(Game& rhs){
	run_ = rhs.run_;
	gameStateStack_ = rhs.gameStateStack_;
	clock_ = rhs.clock_;
}

// Assignment operator
Game& Game::operator=(Game& rhs){
	run_ = rhs.run_;
	gameStateStack_ = rhs.gameStateStack_;
	clock_ = rhs.clock_;
	return *this;
}

// Destructor
Game::~Game(){
	//@TODO
}

void Game::takeInput(sf::Event event)
{
	return; //@TODO
}