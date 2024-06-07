#include "Enemy.h"

///
/// INIT FUNCTIONS
///

void Enemy::initVariables()
{
	this->movementSpeed_ = 1.f;
	this->maxHp_ = 10;
	this->hp_ = maxHp_;
}

void Enemy::initSprite(sf::Vector2f position, sf::Texture* texture)
{
	this->sprite_.setTexture(*texture);
	this->sprite_.setPosition(position);
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Enemy::Enemy(sf::Vector2f position, sf::Texture* texture)
{
	this->initVariables();
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

///
/// FUNCTIONS
///

void Enemy::update()
{
	
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_);
}