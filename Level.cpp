#include "Level.h"

///
/// INIT FUNCTIONS
///

void Level::initVariables()
{
	this->enemyCounter_ = 0;
}

void Level::initFromFiles(std::string path)
{
	/*
		@returns void

		funkcja wczytujaca dane z pliku
		- otwarcie pliku
		- sprawdzenie czy plik jest otwarty
		- wczytanie danych
		- zamkniecie pliku
	*/

	std::ifstream file(path);

	if (file.is_open())
	{

		std::string line;
		std::vector<std::string> data;

		while (std::getline(file, line))
		{
			data.push_back(line);
		}

		this->background_texture_key = data[0];
		this->enemy_texture_key		 = data[1];
		this->enemySpeed_			 = std::stof(data[2]);
		this->enemyMaxHp_			 = std::stoi(data[3]);
		this->enemyDamage_			 = std::stoi(data[4]);
		this->numberOfEnemies_		 = std::stoi(data[5]);
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

		pierwszy * to dereferacja wskaźnika prowadząca nas do mapy, klucz ["NAZWA_TEKSTURY"] wskazuje nam wskaźnik do szukanej tekstury, który deferencj(ujemy?) i
		otrzymujemy już samą teksturę.
	*/

	this->background_ = new sf::Sprite;
	this->background_->setTexture(*(*textures_ptr)[this->background_texture_key]);
}

void Level::initClock()
{
	this->spawnCooldown_ = sf::seconds(1.f);
	this->spawnClock_ = new sf::Clock;
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Level::Level(Player* player, sf::RenderWindow* window, std::map<std::string, sf::Texture*>* textures, std::string path)
	: player_(player), window_(window), textures_ptr(textures)
{
	/*
		@constructor

		Na liście inicjalizacyjnej kopiuje wskaźniki bezpośrednio do
		- Game::player_
		- Game::window_
		- Game::textures_
		Następnie wywołuje funkcje inicjalizacyjne
	*/

	std::cout << "new level; path: " << path << "\n";

	this->initFromFiles(path);
	this->initPlayer();
	this->initBackground();
	this->initClock();
}

Level::~Level()
{
	//this->window_
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

const bool Level::allEnemiesKilled() const
{
	if ((this->enemyCounter_ == this->numberOfEnemies_) && (this->enemies_.empty()))
		return true;
	else
		return false;
}

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

		funkcja odpowiedzialna za utrzymanie gracza w oknie - cofa go jeżeli ten próbuje się z niego wydostać
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

		funkcja generująca losową pozycję spawnu dla przeciwników, 
		w jednym z czterech obszarów znajdujących się zaraz za krawędzią okna
		- tworzy tymczasową zmienną windowSize
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
		Do konstruktora klasy enemy przekazuje pozycję spawnu oraz teksturę.
		- sprawdzenie czy upłynął czas
		- dodanie przeciwnika, z użyciem funkcji randSpawnPosition() nadającej mu początkową pozycję
		- restart spawnClock_
		- pierwszy * to dereferacja wskaźnika prowadząca nas do mapy, klucz ["NAZWA_TEKSTURY"] wskazuje nam wskaźnik do szukanej tekstury, który deferencj(ujemy?) i
		otrzymujemy już samą teksturę.
	
	*/

	if ((this->spawnClock_->getElapsedTime().asSeconds() >= this->spawnCooldown_.asSeconds()) && (this->enemyCounter_ < this->numberOfEnemies_))
	{
		this->enemies_.push_back(new Enemy(randSpawnPosition(), (*textures_ptr)[enemy_texture_key], enemySpeed_, enemyMaxHp_, enemyDamage_));
		this->spawnClock_->restart();
		this->enemyCounter_++;
		std::cout << "enemy number " << enemyCounter_ << std::endl;
	}
}

void Level::enemyCollision(Enemy* enemy, Player* player)
{
	if (enemy->getBounds().intersects(player->getBounds()))
	{
		player->damage(enemy->getDamage());

		sf::FloatRect pbounds = player->getBounds();
		sf::FloatRect ebounds = enemy->getBounds();

		float rx = ebounds.left - pbounds.left;
		float ry = ebounds.top - pbounds.top;

		std::cout << rx << " - " << ry << std::endl;
		enemy->move(rx, ry);
	}
}

void Level::deleteEnemy(unsigned& counter)
{
	delete this->enemies_.at(counter);
	this->enemies_.erase(this->enemies_.begin() + counter);
	--counter;
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

		this->enemyCollision(enemy, this->player_);

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
		- jeżeli wciśnięty jest lewy przycisk myszy
		- i jeżeli minął minimalny czas od ostatniego oddanego strzału
		- tworzony jest sf::Vector2f z pozycją myszy w stosunku do okna, aby wykrozystać go w konstruktorze obiektu BULLET
		- stworzenie nowego obiektu BULLET i dodanie go do Level::bullets_
		- zresetowanie czasu od ostaniego strzału Player::resetTimeSinceLastShot()
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
		@returns bool - czy kula została usunięta?

		wykonywana w pętli funkcji Level::updateBullets() dla każdej kuli w Level::bullets_,
		sprawdza czy doszło do kolizji z którymś z przeciwników, jeśli tak to wykonuje kolizje
		- iteracja po każdym elemencie Level::enemies_
		- sprawdzenie czy doszło do kolizji
		- jeśli tak:
			> zadanie obrażeń rpzeciwnikowi
			> usunięcie kuli funkcją Level::deleteBullet(counter)
			> zwrócenie wartości true (kula została usunięta)
		- jeśli nie:
			> zwrócenie wartości false (kula nie została usunięta)
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
		@returns bool - czy kula została usunięta?

		wykonywana w pętli funkcji Level::updateBullets() dla każdej kuli w Level::bullets_,
		jeżeli kula nie została jeszcze usunięta w funkcji Level::bulletCollision(...),
		sprawdza czy kula opuściła okno programu
		- zmienna pomocnicza bounds
		- sprawdzenie czy kula opuściła okno programu
		- jeśli tak:
			> usunięcie kuli funkcją Level::deleteBullet(counter)
			> zwrócenie wartości true (kula została usunięta)
		- jeśli nie:
			> zwrócenie wartości false (kula nie została usunięta)
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

		- usuwa obiekt pod wskaźniekiem
		- usuwa wskaźnik
		- aktualizuje counter
	*/

	delete this->bullets_.at(counter);
	this->bullets_.erase(this->bullets_.begin() + counter);
	--counter;
}

void Level::updateBullets()
{
	/*
		@returns void

		funkcja odpowiada za aktualizowanie oraz usuwanie kul
		- counter - zmienna pomocnicza służąca do prawidłowego usuwania kul
		- pętla iterująca po wszystkich elementach Level::bullets_
		- przemieszczenie kuli przez Bullet::update() 
		- sprawdzenie kolizji z przeciwnikiem przez Level::bulletCollision(...)
		- jeżeli do kolizji nie doszło - sprawdzenie czy kula opuściła ekran przez Level::cullBullet(...)
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