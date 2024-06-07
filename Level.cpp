#include "Level.h"

///
/// INIT FUNCTIONS
///

void Level::initPlayer()
{
	this->player_->setPosition(this->window_->getSize().x / 2, this->window_->getSize().y / 2);
}

void Level::initBackground(sf::Texture* background_texture)
{
	this->background_ = new sf::Sprite;
	this->background_->setTexture(*background_texture);
}

void Level::initEnemies()
{
	//
}

void Level::initClock()
{
	this->spawnCooldown_ = 3;
	this->spawnClock_.restart();
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Level::Level(Player* player, sf::RenderWindow* window, sf::Texture* background_texture, sf::Texture* enemy_texture)
	: player_(player), window_(window), enemyTexture_(enemy_texture)
{
	/*
		@constructor

		Na liœcie inicjalizacyjnej kopiuje wskaŸniki bezpoœrednio do
		- player_
		- window_
		- enemyTexture_
		Nastêpnie wywo³uje funkcje inicjalizacyjne
	*/

	std::cout << "new level\n";

	this->initPlayer();
	this->initBackground(background_texture);
	this->initEnemies();
}

Level::~Level()
{
	for (auto& el : this->enemies_)
	{
		delete el;
	}
}

///
/// GETTERS
///

///
/// SETTERS
///

///
/// FUNCTIONS
///

sf::Vector2f Level::randSpawnPosition()
{
	sf::Vector2u windowSize = this->window_->getSize();

	float x = static_cast<float>(rand() % windowSize.x);
	float y = static_cast<float>(rand() % windowSize.y);

	return sf::Vector2f(x, y);
}

void Level::enemySpawning()
{
	//if (this->spawnClock_.getElapsedTime().asSeconds() >= this->spawnCooldown_.asSeconds()) 
	if (this->spawnClock_.getElapsedTime().asSeconds() >= 3)	// warunek dziwnie siê zachowuje -> trzeba bêdzie przkminiæ
	{
		this->enemies_.push_back(new Enemy(randSpawnPosition(), enemyTexture_));
		this->spawnClock_.restart();
	}
}

void Level::update()
{
	this->player_->update();
	this->enemySpawning();
}

// rendering

void Level::renderEnemies()
{
	for (auto el : enemies_)
	{
		el->render(*this->window_);
	}
}

void Level::render()
{
	this->window_->draw(*this->background_);
	this->player_->render(*this->window_);
	this->renderEnemies();
}