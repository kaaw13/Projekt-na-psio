#include "Enemy.h"

///
/// INIT FUNCTIONS
///

void Enemy::initSprite(sf::Vector2f position, sf::Texture* texture)
{
	this->sprite_.setTexture(*texture);
	this->sprite_.setPosition(position);
	this->sprite_.setScale(sf::Vector2f(0.4f, 0.4f));
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Enemy::Enemy(sf::Vector2f position, sf::Texture* texture, float speed, unsigned maxHp, unsigned damage)
	: movementSpeed_(speed), maxHp_(maxHp), hp_(maxHp), damage_(damage)
{
	this->initSprite(position, texture);
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
	this->hp_ -= damage;

	if (this->hp_ < 0)
		this->hp_ = 0;
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

	// 1) wektor przesuniêcia
	float rx = px - this->getPos().x;
	float ry = py - this->getPos().y;

	// 2) stosunek Vx/Vy
	float ratio = rx / ry;

	// 3) obliczenie Vy
	Vy = this->movementSpeed_ / sqrt(pow(ratio, 2) + 1);

	// 4) zwrot Vy
	if (ry < 0)
		Vy = -Vy;

	// 5) obliczenie Vx
	Vx = ratio * Vy;

	// 6) ruch
	this->sprite_.move(sf::Vector2f(Vx, Vy));
}

void Enemy::update(sf::Vector2f playerPos)
{
	this->move(playerPos.x, playerPos.y);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_);
}