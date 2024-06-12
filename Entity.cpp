#include "Entity.h"

///
/// INIT FUNCTIONS
///

void Entity::initSprite(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale)
{
	this->sprite_ = new sf::Sprite(*texture);
	this->sprite_->setPosition(position);
	this->sprite_->setScale(scale);
}

void Entity::initHitBox()
{
	this->hitBox_ = this->getBounds();
	this->hitBox_.width *= 0.7f;
	this->hitBox_.height *= 0.7f;
	this->hitBox_.left += hitBox_.width * 0.2f;
	this->hitBox_.top += hitBox_.height * 0.2f;
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Entity::Entity(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, float speed, unsigned damage, unsigned hp)
	: movementSpeed_(speed), damage_(damage), maxHp_(hp), hp_(hp)
{
	this->initSprite(position, texture, scale);
	this->initHitBox();
}

Entity::~Entity()
{

}

///
/// GETTERS
///


///
/// SETTERS
///

void Entity::move(sf::Vector2f displacement)
{
	this->sprite_->move(displacement);
	this->hitBox_.left += displacement.x;
	this->hitBox_.top += displacement.y;
}

void Entity::setPosition(const float x, const float y)
{
	this->sprite_->setPosition(x, y);
}

void Entity::setTexture(sf::Texture* texture)
{
	this->sprite_->setTexture(*texture);
}

void Entity::damage(unsigned damage)
{
	this->hp_ -= damage;

	if (this->hp_ <= 0)
	{
		this->hp_ = 0;
	}
}

void Entity::heal(unsigned heal)
{
	this->hp_ += heal;

	if (this->hp_ > this->maxHp_)
		this->hp_ = this->maxHp_;
}

void Entity::setCurrentHp(unsigned new_hp)
{
	this->hp_ = new_hp;
}

void Entity::setMaxHp(unsigned new_max_hp)
{
	this->maxHp_ = new_max_hp;
}

void Entity::setDamage(int new_damage)
{
	this->damage_ = new_damage;

	if (this->damage_ < 1)
		this->damage_ = 1;
}

void Entity::setSpeed(float new_speed)
{
	this->movementSpeed_ = new_speed;

	if (this->damage_ < 0.5f)
		this->damage_ = 0.5f;
}

///
/// FUNCTIONS
///

void Entity::render(sf::RenderTarget& target)
{
	target.draw(*this->sprite_);
}
