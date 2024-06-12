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

Drop::Drop(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, DROP_TYPE type, int value)
	: type_(type), value_(value)
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

void Drop::collide(Player* player)
{
	switch (this->type_)
	{
	case DROP_TYPE::EXP:
		player->addExp(this->value_);
		break;

	case DROP_TYPE::MEDKIT:
		player->heal(this->value_);
		break;

	default:
		break;
	}
}

void Drop::render(sf::RenderTarget& target)
{
	target.draw(*this->sprite_);
}