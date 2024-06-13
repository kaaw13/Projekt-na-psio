#include "Drop.h"

///
/// INIT FUNCTIONS
///

void Drop::initSprite(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale)
{
	/*
		@returns void

		funkcja inicjalizuje sprite'a
		- teksturê
		- pozycjê
		- skalê
	*/

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
	// initialises type_ and value_, calls initSprite(...)

	this->initSprite(position, texture, scale);
}

Drop::~Drop()
{
	delete this->sprite_;
}

///
/// FUNCTIONS
///

void Drop::collide(Player* player)
{
	/*
		@returns void

		funkcja odpowiedzialna za wykonanie odpowiedniej akcji gdy dojdzie do kolizji z graczem
		- je¿eli typem jest DROP_TYPE::EXP 
		- zwiêkszane jest doœwiadczenie podanego gracza
		- je¿eli typem jest DROP_TYPE::MEDKIT
		- zwiêkszane jest zdrowie gracza
	*/

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
	// renders the sprite_ on a render target (Game::window_)

	target.draw(*this->sprite_);
}