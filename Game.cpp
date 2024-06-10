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

void Game::initPlayer()
{
	this->player_ = new Player(textures_["PLAYER_SHEET"]);
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

void Game::initText()
{
	this->fonts_.push_back(new sf::Font);	
	if (this->fonts_[0]->loadFromFile("Fonts/ARCADECLASSIC.ttf"))
	{
		std::cout << "GAME::INITFONTS::Failed to load ARCADECLASSIC.ttf\n";
	}

	this->menuTexts_.push_back(new sf::Text("Balls of death", *this->fonts_[0], 44));
	this->menuTexts_[0]->setFillColor(sf::Color::White);
	this->menuTexts_[0]->setPosition(sf::Vector2f(50.f, 10.f));
}

void Game::initButtons()
{
	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[0]->setPosition(sf::Vector2f(100.f, 200.f));
	this->buttons_[0]->setFillColor(sf::Color::White);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[1]->setPosition(sf::Vector2f(300.f, 200.f));
	this->buttons_[1]->setFillColor(sf::Color::White);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[2]->setPosition(sf::Vector2f(500.f, 200.f));
	this->buttons_[2]->setFillColor(sf::Color::White);
}

void Game::initMenu()
{
	/*
		@returns void

		initialises the menu
		- sets isMenu_ flag to true
		- creates menu text
		- creates buttons
	*/

	this->isMenu_ = true;
	this->initText();
	this->initButtons();
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

	for (auto& el : this->textures_)
	{
		delete el.second;
	}
	for (auto& el : this->buttons_)
	{
		delete el;
	}
	for (auto& el : this->fonts_)
	{
		delete el;
	}
	for (auto& el : this->menuTexts_)
	{
		delete el;
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
		if (this->buttons_[0]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 1 
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level1.txt");
		}
		else if (this->buttons_[1]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 2
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level2.txt");
		}
		else if (this->buttons_[2]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 3
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level3.txt");
		}
	}
}

void Game::updateLevel()
{
	/*
		@returns void

		funkcja odpowiedzialna za aktualizowanie rozgrywki oraz jej zakoñczenie
		- wywo³anie Level::update() - aktualizacja rozgrywki
		- zakoñczenie rozgrywki - wygrana
			> dzieje siê po zabiciu wszystkich przeciwników
			> reset poziomu
			> prze³¹czenie Game::update() i Game::render() na menu
		- zakoñczenie rozgrywki - przegrana
			> dzieje siê gdy zdrowie gracza spadnie do 0
			> reset poziomu
			> reset gracza
			> prze³¹czenie Game::update() i Game::render() na menu
	*/

	// updating
	this->level_->update();

	// winning
	if (this->level_->allEnemiesKilled())
	{
		delete this->level_;

		this->menuTexts_[0]->setString("Great win!");
		this->isMenu_ = true;
	}

	// losing
	else if (this->level_->getPlayerHp() <= 0)
	{
		delete this->level_;
		delete this->player_;
		this->initPlayer();

		this->menuTexts_[0]->setString("skill issue");
		this->isMenu_ = true;
	}
}

void Game::update()
{
	/*
		@returns void

		funkcja odpowiedzialna za aktualizacje stanu programu w pêtli g³ównej Game::run()
		- zapisuje bie¿¹c¹ pozycjê myszy
		- na podstawie flagi Game::isMenu_ wywo³uje
			> true   ->  updateMenu() 
			> false  ->  updateLevel()
	*/

	this->mousePos_ = sf::Mouse::getPosition(*this->window_);

	if (this->isMenu_)
		this->updateMenu();
	else
		this->updateLevel();
}

// RENDERS

void Game::renderMenu()
{
	for (auto& btn : buttons_)
	{
		this->window_->draw(*btn);
	}
	for (auto& txt : menuTexts_)
	{
		this->window_->draw(*txt);
	}
}

void Game::render()
{
	/*
		@returns void
	
		funkcja odpowiedzialna za wyrysowywanie aktualnego stanu programu na ekranie
		- czyœci okno programu
		- na podstawie flagi Game::isMenu_ wyrysowuje klatkê na oknie Game::window_, wywo³uj¹c
			> true   ->  renderMenu() 
			> false  ->  renderLevel()
		- wyœwietla wyrenderowan¹ klatkê na ekranie
	*/

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



