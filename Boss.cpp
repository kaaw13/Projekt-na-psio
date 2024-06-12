#include "Boss.h"

///
/// INIT FUNCTIONS
///

void Boss::initVariables()
{
	//
}

void Boss::initGui()
{
	// healthbar
	this->healthbar_.setSize(sf::Vector2f(this->getBounds().width, 15.f));
	this->healthbar_.setFillColor(sf::Color::Red);
	this->healthbar_.setPosition(this->getPos().x, this->getPos().y - 20);

	this->healthbarBack_ = this->healthbar_;
	this->healthbarBack_.setFillColor(sf::Color(25, 25, 25, 200));
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Boss::Boss(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, float speed, unsigned damage, unsigned maxHp, sf::Time stun)
	: Enemy(position, texture, scale, speed, damage, maxHp, stun) 
{
	this->initGui();
}

Boss::~Boss()
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

void Boss::updateGui()
{
	// healthbar
	float hpPercent = static_cast<float>(this->getHp()) / this->getMaxHp();
	this->healthbar_.setSize(sf::Vector2f(hpPercent * this->healthbarBack_.getSize().x, this->healthbar_.getSize().y));

	this->healthbarBack_.setPosition(this->getPos());
	this->healthbar_.setPosition(this->getPos());
}

void Boss::renderGui(sf::RenderTarget& target)
{
	// healthbar
	target.draw(this->healthbarBack_);
	target.draw(this->healthbar_);
}