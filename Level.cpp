#include "Level.h"

///
/// INIT FUNCTIONS
///

void Level::initVariables()
{
	this->enemyCounter_ = 0;
	this->wave_1 = true;
	this->wave_2 = false;
	this->wave_3 = false;
	this->bossFight_ = false;

	this->waveCooldown_ = sf::seconds(1.f);
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
		this->spawnCooldown_         = sf::seconds(stof(data[6]));
	}
	else
	{
		std::cout << "ERROR: Level::initFromFiles() - could not open file\n";
	}

	file.close();
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

void Level::initClocks()
{
	this->spawnClock_ = new sf::Clock;
	this->waveCooldownClock_ = new sf::Clock;
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
	this->initVariables();
	this->initBackground();
	this->initClocks();
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
	delete this->boss_;
}

///
/// GETTERS
///

const bool Level::bossDefeated() const
{
	if (this->bossFight_ && this->boss_->getHp() <= 0)
	{
		std::cout << "enemy counter = " << enemyCounter_ << " - enemies_.size() = " << enemies_.size() << std::endl;
		return true;
	}
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

void Level::createEnemy()
{
	/*
		- dodanie przeciwnika, z użyciem funkcji randSpawnPosition() nadającej mu początkową pozycję
		- restart spawnClock_
		- pierwszy * to dereferacja wskaźnika prowadząca nas do mapy, klucz ["NAZWA_TEKSTURY"] wskazuje nam wskaźnik do szukanej tekstury, który deferencj(ujemy?) i
		otrzymujemy już samą teksturę.
	*/

	this->enemies_.push_back(new Enemy(randSpawnPosition(), (*textures_ptr)[enemy_texture_key], { 0.6f, 0.6f }, enemySpeed_, enemyDamage_, enemyMaxHp_));
	this->spawnClock_->restart();
	this->enemyCounter_++;
	std::cout << "enemy number " << enemyCounter_ << std::endl;
}

void Level::nextWave(bool& prev_wave, bool& next_wave, float enemy_amount_change, float spawn_cooldown_change)
{
	/*
		@returns void

		przełącza fale
	*/

	this->enemyCounter_ = 0;
	this->numberOfEnemies_ = static_cast<unsigned>(static_cast<float>(numberOfEnemies_) * enemy_amount_change);
	this->spawnCooldown_ = sf::seconds(this->spawnCooldown_.asSeconds() * spawn_cooldown_change);
	prev_wave = false;
	next_wave = true;

	this->waveCooldownClock_->restart();
}

void Level::updateWave()
{
	/*
		@returns void

		kontroluje etap rozgrywki
	*/

	if (this->waveCooldownClock_->getElapsedTime().asSeconds() >= this->waveCooldown_.asSeconds())
	{
		/// FALA 1
		if (this->wave_1)
		{
			// spawn
			if (this->spawnClock_->getElapsedTime().asSeconds() >= this->spawnCooldown_.asSeconds() && this->enemyCounter_ < this->numberOfEnemies_)
				this->createEnemy();

			// następna fala
			if (this->enemyCounter_ >= this->numberOfEnemies_)
				this->nextWave(this->wave_1, this->wave_2, 2.f, 0.5f);
		}
		/// FALA 2
		else if (this->wave_2)
		{
			// spawn
			if (this->spawnClock_->getElapsedTime().asSeconds() >= this->spawnCooldown_.asSeconds() && this->enemyCounter_ < this->numberOfEnemies_)
				this->createEnemy();

			// następna fala
			if (this->enemyCounter_ >= this->numberOfEnemies_)
				this->nextWave(this->wave_2, this->wave_3, 1.f, 0.5f);
		}
		/// FALA 3
		else if (this->wave_3)
		{
			// spawn
			if (this->spawnClock_->getElapsedTime().asSeconds() >= this->spawnCooldown_.asSeconds() && this->enemyCounter_ < this->numberOfEnemies_)
				this->createEnemy();

			// następna fala - boos fight
			if (this->enemyCounter_ >= this->numberOfEnemies_)
			{
				this->nextWave(this->wave_3, this->bossFight_, 1.f, 0.f);
				this->boss_ = new Boss({-100.f, -100.f}, (*textures_ptr)[enemy_texture_key], {2.f, 2.f}, 0.7f, 7, 200);
			}
		}
	}
}

void Level::enemyKnockback(Enemy* enemy, Entity* entity, float knockback)
{
	/*

	*/

	float Vx, Vy;

	float rx = entity->getPos().x - enemy->getPos().x;
	float ry = entity->getPos().y - enemy->getPos().y;
	float ratio = rx / ry;

	Vy = knockback / sqrt(pow(ratio, 2) + 1);
	if (ry < 0)
		Vy = -Vy;

	Vx = ratio * Vy;
	enemy->Entity::move(sf::Vector2f(-Vx, -Vy));
}

void Level::enemyCollision(Enemy* enemy)
{
	/*
		@returns void

		funkcja rozwiązująca kolizje pomiędzy Enemy, a innymi Entity, kolejno
		- enemy - player
		- enemy - boss
		- enemy - enemy
	*/

	// enemy - player collision
	if (enemy->getHitbox().intersects(this->player_->getBounds()))
	{
		this->player_->damage(enemy->getDamage());
		this->enemyKnockback(enemy, this->player_, 40.f);
		enemy->stun();
	} 
	// enemy - enemy collision
	for (auto& _enemy : this->enemies_)
	{
		if (enemy != _enemy)
		{
			if (enemy->getHitbox().intersects(_enemy->getHitbox()))
				this->enemyKnockback(enemy, _enemy, 10.f);
		}
	}
	// enemy - boss collision
	if (bossFight_)
	{
		if (enemy->getHitbox().intersects(this->boss_->getBounds()))
		{
			this->enemyKnockback(enemy, this->boss_, 10.f);
		}
	}
}

void Level::deleteEnemy(unsigned& counter)
{
	delete this->enemies_.at(counter);
	this->enemies_.erase(this->enemies_.begin() + counter);
	--counter;
}

void Level::updateBoss()
{

	// ruch
	this->boss_->update(this->player_->getPos());

	// kolizja z graczem
	if (this->boss_->getHitbox().intersects(this->player_->getBounds()))
	{
		this->player_->damage(boss_->getDamage());
		this->enemyKnockback(boss_, this->player_, 20.f);
		boss_->stun();
	}

	// gui
	this->boss_->updateGui();
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
	for (auto& enemy : this->enemies_)
	{
		enemy->update(this->player_->getPos());

		this->enemyCollision(enemy);

		if (enemy->getHp() <= 0)
			this->deleteEnemy(counter);

		++counter;
	}
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

bool Level::bulletEnemyCollision(Bullet* bullet, unsigned& counter)
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

	for (auto& enemy : this->enemies_)
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
	for (auto& bullet : this->bullets_)
	{
		bullet->update();

		bool is_deleted = false;

		// bullet - enemy
		is_deleted = this->bulletEnemyCollision(bullet, counter);
		
		// bullets out of window
		if(!is_deleted)
			is_deleted = this->cullBullet(bullet, counter);	

		// bullet - boss
		if (bossFight_ && !is_deleted)
		{
			if (bullet->getBounds().intersects(this->boss_->getHitbox()))
			{
				this->boss_->damage(bullet->getDamage());
				this->deleteBullet(counter);
			}
		}

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

	if (bossFight_)
		this->updateBoss();

	this->updateWave();
}

//			RENDERING			//

void Level::renderEnemies()
{
	for (auto& el : this->enemies_)
	{
		el->render(*this->window_);
	}
}

void Level::renderBullets()
{
	for (auto& el : this->bullets_)
	{
		el->render(*this->window_);
	}
}

void Level::render()
{
	this->window_->draw(*this->background_);

	this->renderBullets();

	this->player_->render(*this->window_);
	this->player_->renderGui(*this->window_);

	this->renderEnemies();

	if (bossFight_)
	{
		this->boss_->render(*this->window_);
		this->boss_->renderGui(*this->window_);
	}
}