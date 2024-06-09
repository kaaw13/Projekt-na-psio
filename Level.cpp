#include "Level.h"

///
/// INIT FUNCTIONS
///

void Level::initTextures(std::map<std::string, sf::Texture*>* textures)
{
	this->textures_ptr = textures;
}

void Level::initPlayer()
{
	this->player_->setPosition(this->window_->getSize().x / 2, this->window_->getSize().y / 2);
}

void Level::initBackground()
{
	/*
		@returns void

		pierwszy * to dereferacja wska�nika prowadz�ca nas do mapy, klucz ["NAZWA_TEKSTURY"] wskazuje nam wska�nik do szukanej tekstury, kt�ry deferencj(ujemy?) i
		otrzymujemy ju� sam� tekstur�.
	*/

	this->background_ = new sf::Sprite;
	this->background_->setTexture(*(*textures_ptr)["BACKGROUND_1"]);
}

void Level::initEnemies()
{
	//
}

void Level::initClock()
{
	this->spawnCooldown_ = sf::seconds(1.f);
	this->spawnClock_ = new sf::Clock;
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Level::Level(Player* player, sf::RenderWindow* window, std::map<std::string, sf::Texture*>* textures)
	: player_(player), window_(window), textures_ptr(textures)
{
	/*
		@constructor

		Na li�cie inicjalizacyjnej kopiuje wska�niki bezpo�rednio do
		- Game::player_
		- Game::window_
		- Game::textures_
		Nast�pnie wywo�uje funkcje inicjalizacyjne
	*/

	std::cout << "new level\n";

	this->initPlayer();
	this->initBackground();
	this->initEnemies();
	this->initClock();
}

Level::~Level()
{
	for (auto& el : this->enemies_)
	{
		delete el;
	}
	for (auto& el : this->bullets_)
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
	/*
		@returns sf::Vector2f 

		funkcja generuj�ca losow� pozycj� spawnu dla przeciwnik�w, 
		w jednym z czterech obszar�w znajduj�cych si� zaraz za kraw�dzi� okna
		- tworzy tymczasow� zmienn� windowSize
		- losuje obszar pod, nad, na lewo lub na prawo od okna [switch]
		- ustala x i y
		- zwraca [x, y]
	*/

	sf::Vector2u windowSize = this->window_->getSize();
	float x, y;

	switch (rand() % 4)
	{
	case 0:		// nad oknem
		x = static_cast<float>(rand() % windowSize.x);
		y = -50.f;
		break;
	case 1:		// pod oknem
		x = static_cast<float>(rand() % windowSize.x);
		y = static_cast<float>(windowSize.y);
		break;
	case 2:		// na lewo od okna
		x = -50.f;
		y = static_cast<float>(rand() % windowSize.y);
		break;
	case 3:		// na prawo od okna
		x = static_cast<float>(windowSize.x);
		y = static_cast<float>(rand() % windowSize.y);
		break;
	default:
		x = 0.f;
		y = 0.f;
		break;
	}

	return sf::Vector2f(x, y);
}

void Level::enemySpawning()
{
	/*
		@returns void

		funckja tworzy nowego przeciwnika i dodaje do wektora enemies_, raz na czas okreslony w zmiennej spawnCooldow_
		Do konstruktora klasy enemy przekazuje pozycj� spawnu oraz tekstur�.
		- sprawdzenie czy up�yn�� czas
		- dodanie przeciwnika, z u�yciem funkcji randSpawnPosition() nadaj�cej mu pocz�tkow� pozycj�
		- restart spawnClock_
		- pierwszy * to dereferacja wska�nika prowadz�ca nas do mapy, klucz ["NAZWA_TEKSTURY"] wskazuje nam wska�nik do szukanej tekstury, kt�ry deferencj(ujemy?) i
		otrzymujemy ju� sam� tekstur�.
	
	*/

	if (this->spawnClock_->getElapsedTime().asSeconds() >= this->spawnCooldown_.asSeconds()) 
	{
		this->enemies_.push_back(new Enemy(randSpawnPosition(), (*textures_ptr)["ENEMY_SHEET"]));
		this->spawnClock_->restart();
	}
}

void Level::updateEnemies()
{
	/*
		@returns void

		functiong responsible for updating all enemies and spawning new ones
		- calls Enemy::update() for every enemy in Level::enemies_
		- calls Level::enemySpawning() that handles spawning
	*/

	for (auto el : enemies_)
	{
		//Enemy::update() b�dzie odpowiedzialne za wykonanie ruchu oraz kolizji z graczem
		el->update(this->player_->getPos());
	}

	this->enemySpawning();
}

void Level::shoting()
{
	/*
		@return void

		creating bullets
	*/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->player_->getTimeSinceLastShoot() >= this->player_->getShootCooldown())
		{
			sf::Vector2f mouse_pos = { static_cast<float>(sf::Mouse::getPosition(*this->window_).x), static_cast<float>(sf::Mouse::getPosition(*this->window_).y) };

			this->bullets_.push_back(new Bullet(this->player_->getPos(), mouse_pos, (*textures_ptr)["BULLET"]));
			
			this->player_->resetTimeSinceLastShot();
		}
	}
}

void Level::updateBullets()
{
	for (auto el : bullets_)
	{
		el->update();
	}
}

void Level::cullBullets()
{
	// to b�dzie funkcja odpowiedzialna za usuwanie pocisk�w, kt�re znajduj� si� poza ekranem
}

void Level::update()
{
	this->player_->update();
	this->updateBullets();
	this->shoting();
	//this->updateEnemies();
	this->cullBullets();
}

// rendering

void Level::renderEnemies()
{
	for (auto el : enemies_)
	{
		el->render(*this->window_);
	}
}

void Level::renderBullets()
{
	for (auto el : bullets_)
	{
		el->render(*this->window_);
	}
}

void Level::render()
{
	this->window_->draw(*this->background_);
	this->player_->render(*this->window_);

	this->renderEnemies();
	this->renderBullets();
}