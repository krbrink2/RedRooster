#include "Game.h"
#include "Globals.h"

// Constructor
Game::Game()
	: window_(sf::VideoMode(200, 200), GAME_TITLE) //, sf::Style::Fullscreen),
	, run_(true)
{
}

// // Copy constructor
// Game::Game(Game& rhs){
// 	run_ = rhs.run_;
// 	gameStatePtrStack_ = rhs.gameStatePtrStack_;
// 	clock_ = rhs.clock_;
// }

// // Assignment operator
// Game& Game::operator=(Game& rhs){
// 	run_ = rhs.run_;
// 	gameStatePtrStack_ = rhs.gameStatePtrStack_;
// 	clock_ = rhs.clock_;
// 	return *this;
// }

// Destructor
Game::~Game(){
	clear();
}

void Game::pushGameState(GameState* state)
{
	gameStatePtrStack_.push(state);
};

void Game::popGameState()
{
	delete gameStatePtrStack_.top();
	gameStatePtrStack_.pop();
};

void Game::takeInput(sf::Event event)
{
	gameStatePtrStack_.top()->takeInput(event);
}

void Game::update()
{
	gameStatePtrStack_.top()->update();
}

void Game::draw()
{
	window_.clear();
	gameStatePtrStack_.top()->draw();
}

void Game::drawSprite(sf::Drawable& sprite)
{
	window_.draw(sprite);
}

bool Game::isRunning()
{
	return run_;
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