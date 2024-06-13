#include "Enemy.h"

///
/// INIT FUNCTIONS
///

void Enemy::initVariables()
{
	// inicjalizuje pozosta�e zmienne

	this->isStunned_ = false;
	this->timeSinceStunned_ = this->stunDuration_;
}

void Enemy::initClocks()
{
	// inicjalizuje zegar odpowiedzialny za og�uszenie przeciwnika po trafieniu

	this->timeSinceStunned_ = sf::Time::Zero;
	this->stunClock_.restart();
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Enemy::Enemy(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, float speed, unsigned damage, unsigned maxHp, sf::Time stun)
	: Entity(position, texture, scale, speed, damage, maxHp), stunDuration_(stun)
{
	/*
		@constructor

		- przekazuje dane potrzebne do zainicjowania sprita oraz podstawowych statystyk do konstruktora klasy Entity
		- inicjalizuje czas og�uszenia
		- wywo�uje pozosta�e funkcje inicjalizuj�ce 
	*/ 

	this->initVariables();
	this->initClocks();
}

Enemy::~Enemy()
{
	//
}

///
/// SETTERS
///

void Enemy::stun()
{
	/*
		@returns void

		funkcja odpowiada za og�uszenie przeciwnika
		- ustawia isStunned na true
		- ustawia czas od otrzymania obra�e� (og�uszenia) na zero
	*/

	this->isStunned_ = true;
	this->timeSinceStunned_ = sf::Time::Zero;
}

void Enemy::setStunDuration(sf::Time duration)
{
	// zmiana czasu trwania og�uszenia - minimalnie 0

	if (duration < sf::Time::Zero)
		this->stunDuration_ = sf::Time::Zero;
	else
		this->stunDuration_ = duration;
}

///
/// FUNCTIONS
///

void Enemy::damage(unsigned damage)
{
	/*
		@returns void

		funckja obs�uguje otrzymywanie obra�e�
		- zmiejszenie zdrowia przez Entity::damage(...)
		- og�uszenie przecinwika przez Enemy::stun()
	*/

	this->Entity::damage(damage);
	this->stun();
}

void Enemy::move(float px, float py)
{
	/*
		returns @void

		funkcja przyjmuje w argumentach aktualn� pozycje gracza [px, py], nast�pnie oblicza
		sk�adowe pr�dko�ci [Vx, Vy], z kt�rymi przeciwnik musi si� poruszy� i wywo�uje funkcj� Entity::move(...)
		- inicjalizacja zmiennych pomocniczych
		- obliczenie przesuni�� rx i ry
		- je�eli ry nie jest r�wne zeru, obliczamy
			> ratio - stosunek pr�dko�ci Vx do Vy
			> warto�� Vy z przekszta�conego twierdzenia pitagorasa
			> zwrot Vy
			> Vx = ratio * Vy
		- je�eli ry jest r�wne zeru
			> Vy = 0
			> Vx = pr�dko�ci obiektu
		- ruszamy obiektem z pr�dko�ciami Vx i Vy
	*/

	float Vx, Vy;

	// przesuni�cie
	float rx = px - (this->getBounds().left + this->getBounds().width/2);
	float ry = py - (this->getBounds().top + this->getBounds().height/2);

	// obliczenie Vx i Vy
	if (ry != 0)
	{
		float ratio = rx / ry;
		
		Vy = this->Entity::getSpeed() / sqrt(pow(ratio, 2) + 1);

		if (ry < 0)
			Vy = -Vy;

		Vx = ratio * Vy;
	}
	else
	{
		Vy = 0;
		Vx = this->Entity::getSpeed();
	}

	// ruch
	this->Entity::move(sf::Vector2f(Vx, Vy));
}

void Enemy::updateStun()
{
	/*
		@returns void

		- funkcja nalicza czas, kt�ry up�yn�� od og�uszenia
		- je�eli przekroczy czas trwania og�uszenia, isStunned jest ustawiane na false
	*/

	this->timeSinceStunned_ += this->stunClock_.restart();

	if (this->timeSinceStunned_ > this->stunDuration_)
		this->isStunned_ = false;
}

void Enemy::update()
{
	// przeci��enie funkcji wirtualnej
}

void Enemy::update(sf::Vector2f playerPos)
{
	/*
		@returns void

		funkcja opowiedzialna za aktualizowanie stanu pobiektu
		- sprawdzenie czy przeciwnik jest og�uszony
		- je�eli nie - wywo�anie funkcji odpowiedzialnej za poruszanie si�
	*/

	this->updateStun();

	if (!this->isStunned_)
		this->move(playerPos.x, playerPos.y);
}