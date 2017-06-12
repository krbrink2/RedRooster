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
	gameStatePtrStack_ = rhs.gameStatePtrStack_;
	clock_ = rhs.clock_;
}

// Assignment operator
Game& Game::operator=(Game& rhs){
	run_ = rhs.run_;
	gameStatePtrStack_ = rhs.gameStatePtrStack_;
	clock_ = rhs.clock_;
	return *this;
}

// Destructor
Game::~Game(){
	//@TODO
}

void Game::pushGameState(GameState* state)
{
	gameStatePtrStack_.push_back(state);
};

void Game::popGameState()
{
	delete gameStatePtrStack_.back();
	gameStatePtrStack_.pop_back();
};

void Game::takeInput(sf::Event event)
{
	gameStatePtrStack_.back()->takeInput(event);
}

int Game::clear()
{
	while(!gameStatePtrStack_.empty())
	{
		popGameState();
	}
	window_.close();
	run_ = false;
	return 0;
}