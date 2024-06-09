#include "Level.h"
#include <fstream>
#include <vector>

///
/// INIT FUNCTIONS
///
void Level::initFromFiles(std::string path)
{
	/*
		@returns void

		funkcja wczytuj¹ca dane z pliku
		- otwarcie pliku
		- sprawdzenie czy plik jest otwarty
		- wczytanie danych
		- zamkniêcie pliku
	*/

	std::ifstream file(path);

	if (file.is_open())
	{
		
		std::string line;
		std::vector<std::string> test;

		while (std::getline(file, line))
		{
			test.push_back(line);
		}

		for (auto& el : test)
		{
			std::cout << el << std::endl;
		}
		background_Texture_Key = test[0];
		enemy_Texture_key = test[1];
		enemyspeed = std::stof(test[2]);
		enemyMaxHp = std::stoi(test[3]);
		enemyDamage = std::stoi(test[4]);
	}
	else
	{
		std::cout << "ERROR: Level::initFromFiles() - could not open file\n";
	}

	file.close();
}

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

		pierwszy * to dereferacja wskaŸnika prowadz¹ca nas do mapy, klucz ["NAZWA_TEKSTURY"] wskazuje nam wskaŸnik do szukanej tekstury, który deferencj(ujemy?) i
		otrzymujemy ju¿ sam¹ teksturê.
	*/

	this->background_ = new sf::Sprite;
	this->background_->setTexture(*(*textures_ptr)[background_Texture_Key]);
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

Level::Level(Player* player, sf::RenderWindow* window, std::map<std::string, sf::Texture*>* textures,std::string path)
	: player_(player), window_(window), textures_ptr(textures)
{
	/*
		@constructor

		Na liœcie inicjalizacyjnej kopiuje wskaŸniki bezpoœrednio do
		- Game::player_
		- Game::window_
		- Game::textures_
		Nastêpnie wywo³uje funkcje inicjalizacyjne
	*/

	std::cout << "new level\n";
	this->initFromFiles(path);
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

//			PLAYER RELATED			//

void Level::playerWindowCollision()
{
	/*
		@returns void

		funkcja odpowiedzialna za utrzymanie gracza w oknie - cofa go je¿eli ten próbuje siê z niego wydostaæ
	*/

	sf::Vector2u window_size = this->window_->getSize();

	// left
	if (this->player_->getBounds().left < 0.f)
	{
		this->player_->setPosition(0.f, this->player_->getBounds().top);
	}
	// right
	else if (this->player_->getBounds().left + this->player_->getBounds().width > window_size.x)
	{
		this->player_->setPosition(window_size.x - this->player_->getBounds().width, this->player_->getBounds().top);
	}
	// top
	if (this->player_->getBounds().top < 0.f)
	{
		this->player_->setPosition(this->player_->getBounds().left, 0.f);
	}
	// bottom
	else if (this->player_->getBounds().top + this->player_->getBounds().height > window_size.y)
	{
		this->player_->setPosition(this->player_->getBounds().left, window_size.y - this->player_->getBounds().height);
	}
}

//			ENEMY RELATED			//

sf::Vector2f Level::randSpawnPosition()
{
	/*
		@returns sf::Vector2f 

		funkcja generuj¹ca losow¹ pozycjê spawnu dla przeciwników, 
		w jednym z czterech obszarów znajduj¹cych siê zaraz za krawêdzi¹ okna
		- tworzy tymczasow¹ zmienn¹ windowSize
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
		Do konstruktora klasy enemy przekazuje pozycjê spawnu oraz teksturê.
		- sprawdzenie czy up³yn¹³ czas
		- dodanie przeciwnika, z u¿yciem funkcji randSpawnPosition() nadaj¹cej mu pocz¹tkow¹ pozycjê
		- restart spawnClock_
		- pierwszy * to dereferacja wskaŸnika prowadz¹ca nas do mapy, klucz ["NAZWA_TEKSTURY"] wskazuje nam wskaŸnik do szukanej tekstury, który deferencj(ujemy?) i
		otrzymujemy ju¿ sam¹ teksturê.
	
	*/

	if (this->spawnClock_->getElapsedTime().asSeconds() >= this->spawnCooldown_.asSeconds()) 
	{
		this->enemies_.push_back(new Enemy(randSpawnPosition(), (*textures_ptr)[enemy_Texture_key],enemyspeed,enemyMaxHp,enemyDamage));
		this->spawnClock_->restart();
	}
}

void Level::deleteEnemy(unsigned& counter)
{
	delete this->enemies_.at(counter);
	this->enemies_.erase(this->enemies_.begin() + counter);
	--counter;
	std::cout << "enemy deleted\n";
}

void Level::updateEnemies()
{
	/*
		@returns void

		functiong responsible for updating all enemies and spawning new ones
		- calls Enemy::update() for every enemy in Level::enemies_
		- calls Level::enemySpawning() that handles spawning
	*/

	unsigned counter = 0;
	for (auto& enemy : enemies_)
	{
		enemy->update(this->player_->getPos());

		if (enemy->getHp() <= 0)
			this->deleteEnemy(counter);

		++counter;
	}

	this->enemySpawning();
}

//			 BULLET RELATED				//

void Level::shoting()
{
	/*
		@return void

		funkcja odpowiedzialna za strzelanie
		- je¿eli wciœniêty jest lewy przycisk myszy
		- i je¿eli min¹³ minimalny czas od ostatniego oddanego strza³u
		- tworzony jest sf::Vector2f z pozycj¹ myszy w stosunku do okna, aby wykrozystaæ go w konstruktorze obiektu BULLET
		- stworzenie nowego obiektu BULLET i dodanie go do Level::bullets_
		- zresetowanie czasu od ostaniego strza³u Player::resetTimeSinceLastShot()
	*/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->player_->getTimeSinceLastShoot() >= this->player_->getShootCooldown())
		{
			sf::Vector2f mouse_pos = { static_cast<float>(sf::Mouse::getPosition(*this->window_).x), static_cast<float>(sf::Mouse::getPosition(*this->window_).y) };

			this->bullets_.push_back(new Bullet(this->player_->getPos(), mouse_pos, (*textures_ptr)["BULLET"], this->player_->getDamage()));
			
			this->player_->resetTimeSinceLastShot();
		}
	}
}

bool Level::bulletCollision(Bullet* bullet, unsigned& counter)
{
	/*
		@returns bool - czy kula zosta³a usuniêta?

		wykonywana w pêtli funkcji Level::updateBullets() dla ka¿dej kuli w Level::bullets_,
		sprawdza czy dosz³o do kolizji z którymœ z przeciwników, jeœli tak to wykonuje kolizje
		- iteracja po ka¿dym elemencie Level::enemies_
		- sprawdzenie czy dosz³o do kolizji
		- jeœli tak:
			> zadanie obra¿eñ rpzeciwnikowi
			> usuniêcie kuli funkcj¹ Level::deleteBullet(counter)
			> zwrócenie wartoœci true (kula zosta³a usuniêta)
		- jeœli nie:
			> zwrócenie wartoœci false (kula nie zosta³a usuniêta)
	*/

	for (auto& enemy : enemies_)
	{
		if (bullet->getBounds().intersects(enemy->getBounds()))
		{
			enemy->damage(bullet->getDamage());
			this->deleteBullet(counter);
			return true;
		}
	}
	return false;
}

bool Level::cullBullet(Bullet* bullet, unsigned& counter)
{
	/*
		@returns bool - czy kula zosta³a usuniêta?

		wykonywana w pêtli funkcji Level::updateBullets() dla ka¿dej kuli w Level::bullets_,
		je¿eli kula nie zosta³a jeszcze usuniêta w funkcji Level::bulletCollision(...),
		sprawdza czy kula opuœci³a okno programu
		- zmienna pomocnicza bounds
		- sprawdzenie czy kula opuœci³a okno programu
		- jeœli tak:
			> usuniêcie kuli funkcj¹ Level::deleteBullet(counter)
			> zwrócenie wartoœci true (kula zosta³a usuniêta)
		- jeœli nie:
			> zwrócenie wartoœci false (kula nie zosta³a usuniêta)
	*/

	sf::FloatRect bounds = bullet->getBounds();
	if (bounds.left + bounds.width < 0 || bounds.left > this->window_->getSize().x ||
		bounds.top + bounds.height < 0 || bounds.top  > this->window_->getSize().y)
	{
		this->deleteBullet(counter);
		return true;
	}
	return false;
}

void Level::deleteBullet(unsigned& counter)
{
	/*
		@return void

		- usuwa obiekt pod wskaŸniekiem
		- usuwa wskaŸnik
		- aktualizuje counter
	*/

	delete this->bullets_.at(counter);
	this->bullets_.erase(this->bullets_.begin() + counter);
	--counter;
	std::cout << "bullet deleted\n";
}

void Level::updateBullets()
{
	/*
		@returns void

		funkcja odpowiada za aktualizowanie oraz usuwanie kul
		- counter - zmienna pomocnicza s³u¿¹ca do prawid³owego usuwania kul
		- pêtla iteruj¹ca po wszystkich elementach Level::bullets_
		- przemieszczenie kuli przez Bullet::update() 
		- sprawdzenie kolizji z przeciwnikiem przez Level::bulletCollision(...)
		- je¿eli do kolizji nie dosz³o - sprawdzenie czy kula opuœci³a ekran przez Level::cullBullet(...)
	*/

	unsigned counter = 0;
	for (auto& bullet : bullets_)
	{
		bullet->update();

		if (!this->bulletCollision(bullet, counter))
			this->cullBullet(bullet, counter);	

		++counter;
	}
}

//			MAIN UPDATE			//

void Level::update()
{
	this->player_->update();
	this->shoting();
	this->playerWindowCollision();

	this->updateBullets();
	this->updateEnemies();
}

//			RENDERING			//

void Level::renderEnemies()
{
	for (auto& el : enemies_)
	{
		el->render(*this->window_);
	}
}

void Level::renderBullets()
{
	for (auto& el : bullets_)
	{
		el->render(*this->window_);
	}
}

void Level::render()
{
	this->window_->draw(*this->background_);

	this->renderBullets();
	this->player_->render(*this->window_);
	this->renderEnemies();
}