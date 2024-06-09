#include "Game.h"

///
/// INIT FUNCTIONS
/// 

void Game::initWindow()
{
	//this->window_ = new sf::RenderWindow(sf::VideoMode(1920, 1080), "nazwa", sf::Style::Fullscreen);	// okno docelowe
	this->window_ = new sf::RenderWindow(sf::VideoMode(800, 600), "nazwa", sf::Style::Close);		// okienko tymczasowe do wygodniejszego testowania
	this->window_->setFramerateLimit(144);
	this->window_->setVerticalSyncEnabled(false);
	std::cout << "initWindow\n";
}

void Game::initTextures()
{
	/*
		@returns void

		wczytuje wszystkie textury i dodaje je do wektora textures_
		- playerSheet
		- enemySheet
	*/

	this->textures_["PLAYER_SHEET"] = new sf::Texture;
	if (!this->textures_["PLAYER_SHEET"]->loadFromFile("Textures/playerSheet.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load playerSheet.png\n";
	}

	this->textures_["ENEMY_SHEET"] = new sf::Texture;
	if (!this->textures_["ENEMY_SHEET"]->loadFromFile("Textures/enemySheet.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load enemySheet.png\n";
	}

	this->textures_["BACKGROUND_1"] = new sf::Texture;
	if (!this->textures_["BACKGROUND_1"]->loadFromFile("Textures/background1.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load background1.png\n";
	}

	this->textures_["BULLET"] = new sf::Texture;
	if (!this->textures_["BULLET"]->loadFromFile("Textures/bullet.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load bullet.png\n";
	}
}

void Game::initPlayer()
{
	this->player_ = new Player(textures_["PLAYER_SHEET"]);
}

void Game::initMenu()
{
	/*
		WORK IN PROGRESS
	 
		@returns void

		initialises the menu
		- sets isMenu_ flag to true
		- creates buttons for levels
		- creates button for exit
	*/

	this->isMenu_ = true;

	// testowy przycisk
	this->button_1 = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));
	this->button_1->setPosition(sf::Vector2f(100.f, 200.f));
	this->button_1->setFillColor(sf::Color::White);
	this->button_2 = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));
	this->button_2->setPosition(sf::Vector2f(300.f, 200.f));
	this->button_2->setFillColor(sf::Color::White);
	this->button_3 = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));
	this->button_3->setPosition(sf::Vector2f(500.f, 200.f));
	this->button_3->setFillColor(sf::Color::White);
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Game::Game()
{
	// calls all init-Functions
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initMenu();
}

Game::~Game()
{
	// deletes all objects
	delete this->player_;
	delete this->button_1;
	delete this->button_2;
	delete this->button_3;

	for (auto& el : this->textures_)
	{
		delete el.second;
	}

	delete this->window_;
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

void Game::updateMenu()
{
	/*
		@returns void

		funkcja odpowiadaj¹ca za wybór poziomu
		- sprawdza czy wciœniêto lewy przycisk myszy
		- sprawdza czy klikniêto na przycisk 
		- wy³¹cza menu ustawiaj¹c isMenu_ na false
		- wywo³uje odpowiedni poziom
	*/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button_1->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			this->isMenu_ = false;
			std::cout << "button_1 clicked\n";

			// tworzenie poziomu
			this->level_ = new Level(this->player_, this->window_, &this->textures_,"Level/Level1.txt");
		}
		else if (this->button_2->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			this->isMenu_ = false;
			std::cout << "button_2 clicked\n";

			// tworzenie poziomu
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level2.txt");
		}
		else if (this->button_3->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			this->isMenu_ = false;
			std::cout << "button_3 clicked\n";

			// tworzenie poziomu
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level3.txt");
		}
	}
}

void Game::update()
{
	this->mousePos_ = sf::Mouse::getPosition(*this->window_);

	if (this->isMenu_)
		this->updateMenu();
	else
		this->level_->update();
}

// RENDERS

void Game::renderMenu()
{
	this->window_->draw(*this->button_1);
	this->window_->draw(*this->button_2);
	this->window_->draw(*this->button_3);
}

void Game::render()
{
	// Clearing
	this->window_->clear();

	// Drawing
	if (this->isMenu_)
		this->renderMenu();
	else
		this->level_->render();

	// Displaying
	this->window_->display();
}



