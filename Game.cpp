#include "Game.h"
#include "Globals.h"

// Constructor
Game::Game():
	window_(sf::VideoMode(200, 200), GAME_TITLE),//, sf::Style::Fullscreen),
	run_(true){
		std::cout << "> Glb::game constructed" << std::endl;
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

void Game::pushGameState(GameState* state)
{
	gameStateStack_.pushBack(state);
};

void Game::popGameState()
{
	delete gameStateStack_.back();
	gameStateStack_.popBack;
};

void Game::takeInput(sf::Event event)
{
	gameStateStack_.back().takeInput(event);
}

int Game::clear()
{
	while(!gameStateStack_.empty())
	{
		popGameState();
	}
	window_.close();
	return 0;
}