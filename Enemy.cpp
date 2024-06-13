#include "Enemy.h"

///
/// INIT FUNCTIONS
///

void Enemy::initVariables()
{
	// inicjalizuje pozosta³e zmienne

	this->isStunned_ = false;
	this->timeSinceStunned_ = this->stunDuration_;
}

void Enemy::initClocks()
{
	// inicjalizuje zegar odpowiedzialny za og³uszenie przeciwnika po trafieniu

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
		- inicjalizuje czas og³uszenia
		- wywo³uje pozosta³e funkcje inicjalizuj¹ce 
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

		funkcja odpowiada za og³uszenie przeciwnika
		- ustawia isStunned na true
		- ustawia czas od otrzymania obra¿eñ (og³uszenia) na zero
	*/

	this->isStunned_ = true;
	this->timeSinceStunned_ = sf::Time::Zero;
}

void Enemy::setStunDuration(sf::Time duration)
{
	// zmiana czasu trwania og³uszenia - minimalnie 0

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

		funckja obs³uguje otrzymywanie obra¿eñ
		- zmiejszenie zdrowia przez Entity::damage(...)
		- og³uszenie przecinwika przez Enemy::stun()
	*/

	this->Entity::damage(damage);
	this->stun();
}

void Enemy::move(float px, float py)
{
	/*
		returns @void

		funkcja przyjmuje w argumentach aktualn¹ pozycje gracza [px, py], nastêpnie oblicza
		sk³adowe prêdkoœci [Vx, Vy], z którymi przeciwnik musi siê poruszyæ i wywo³uje funkcjê Entity::move(...)
		- inicjalizacja zmiennych pomocniczych
		- obliczenie przesuniêæ rx i ry
		- je¿eli ry nie jest równe zeru, obliczamy
			> ratio - stosunek prêdkoœci Vx do Vy
			> wartoœæ Vy z przekszta³conego twierdzenia pitagorasa
			> zwrot Vy
			> Vx = ratio * Vy
		- je¿eli ry jest równe zeru
			> Vy = 0
			> Vx = prêdkoœci obiektu
		- ruszamy obiektem z prêdkoœciami Vx i Vy
	*/

	float Vx, Vy;

	// przesuniêcie
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

		- funkcja nalicza czas, który up³yn¹³ od og³uszenia
		- je¿eli przekroczy czas trwania og³uszenia, isStunned jest ustawiane na false
	*/

	this->timeSinceStunned_ += this->stunClock_.restart();

	if (this->timeSinceStunned_ > this->stunDuration_)
		this->isStunned_ = false;
}

void Enemy::update()
{
	// przeci¹¿enie funkcji wirtualnej
}

void Enemy::update(sf::Vector2f playerPos)
{
	/*
		@returns void

		funkcja opowiedzialna za aktualizowanie stanu pobiektu
		- sprawdzenie czy przeciwnik jest og³uszony
		- je¿eli nie - wywo³anie funkcji odpowiedzialnej za poruszanie siê
	*/

	this->updateStun();

	if (!this->isStunned_)
		this->move(playerPos.x, playerPos.y);
}