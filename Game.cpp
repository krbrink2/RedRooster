#include "Game.h"

// Constructor
Game::Game():
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