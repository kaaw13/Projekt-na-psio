#include "Game.h"

///
/// INIT FUNCTIONS
/// 

void Game::initWindow()
{
	this->window_ = new sf::RenderWindow(sf::VideoMode(1920, 1080), "nazwa", sf::Style::Fullscreen);
	this->window_->setFramerateLimit(144);
	this->window_->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	//
}

void Game::initPlayer()
{
	player_ = new Player();
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window_;
	delete this->player_;
}

///
/// FUNCTIONS
///

// Main loop
void Game::run()
{
	/*
		@returns void

		Runs the main game loop while the window is open.
		- main loop
		- updating
		- rendering
	*/

	while (window_->isOpen())
	{
		this->updatePollEvents();

		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	/*
		@returns void

		Checks all events in the poll
		- closing via escape key
	*/

	while (this->window_->pollEvent(this->e))
	{
		if (this->e.type == sf::Event::KeyPressed && this->e.key.code == sf::Keyboard::Escape)
		{
			this->window_->close();
		}
	}
}

// UPDATES

void Game::update()
{
	//
	player_->update();
}


// RENDERS

void Game::render()
{
	// Clearing
	this->window_->clear();

	// Drawing

	player_->render(*this->window_);

	// Displaying
	this->window_->display();
}



