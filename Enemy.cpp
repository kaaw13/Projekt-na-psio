#include "Enemy.h"

///
/// INIT FUNCTIONS
///

void Enemy::initVariables()
{
	this->isStunned_ = false;
	this->stunDuration_ = sf::seconds(2.f);
}

void Enemy::initClocks()
{
	this->timeSinceStunned_ = sf::Time::Zero;
	this->stunClock_.restart();
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Enemy::Enemy(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, float speed, unsigned damage, unsigned maxHp)
	: Entity(position, texture, scale, speed, damage, maxHp)
{
	this->initVariables();
	this->initClocks();
}

Enemy::~Enemy()
{

}

///
/// GETTERS
///

///
/// SETTERS
///

void Enemy::damage(unsigned damage)
{
	this->Entity::damage(damage);
	this->stun();
}

void Enemy::stun()
{
	this->isStunned_ = true;
	this->timeSinceStunned_ = sf::Time::Zero;
}

void Enemy::setStunDuration(sf::Time duration)
{
	this->stunDuration_ = duration;
}

///
/// FUNCTIONS
///

void Enemy::move(float px, float py)
{
	/*
		returns @void

		funkcja przyjmuje w argumentach aktualn¹ pozycje gracza [px, py], nastêpnie oblicza
		sk³adowe prêdkoœci [Vx, Vy], z którymi przeciwnik musi siê poruszyæ i wywo³uje funkcjê move()
		1) [rx, ry] wektor przesuniêcia
		2) ratio - stosunek prêdkoœci Vx do Vy
		3) obliczenie Vy z twierdzenia pitagorasa:
			> V^2 = Vx^2 + Vy^2
			> Vx = ratio * Vy
			> V^2 = Vy^2 * (ratio^2 + 1)
			> Vy = V / sqrt(ratio^2 + 1)  -  ten wzór jest widoczny w kodzie
		4) ustalenie kierunku Vy
		5) obliczenie Vx
		6) poruszenie przecinikiem u¿ywaj¹c move()
	*/

	float Vx, Vy;
	sf::FloatRect bounds = this->getBounds();

	// 1) wektor przesuniêcia
	float rx = px - (bounds.left + bounds.width/2);
	float ry = py - (bounds.top + bounds.height/2);

	// 2) stosunek Vx/Vy
	float ratio = rx / ry;

	// 3) obliczenie Vy
	Vy = this->Entity::getSpeed() / sqrt(pow(ratio, 2) + 1);

	// 4) zwrot Vy
	if (ry < 0)
		Vy = -Vy;

	// 5) obliczenie Vx
	Vx = ratio * Vy;

	// 6) ruch
	this->Entity::move(sf::Vector2f(Vx, Vy));
}

void Enemy::updateStun()
{
	this->timeSinceStunned_ += this->stunClock_.restart();

	if (this->timeSinceStunned_ > this->stunDuration_)
		this->isStunned_ = false;
}

void Enemy::update()
{
	//
}

void Enemy::update(sf::Vector2f playerPos)
{
	this->updateStun();

	if (!this->isStunned_)
		this->move(playerPos.x, playerPos.y);
}