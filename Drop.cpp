#include "Drop.h"

///
/// INIT FUNCTIONS
///

void Drop::initSprite(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale)
{
	this->sprite_ = new sf::Sprite(*texture);
	this->sprite_->setPosition(position);
	this->sprite_->setScale(scale);
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Drop::Drop(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale)
{
	this->initSprite(position, texture, scale);
}

Drop::~Drop()
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

void Drop::update()
{
	//
}

void Drop::render(sf::RenderTarget& target)
{
	target.draw(*this->sprite_);
}