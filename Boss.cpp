#include "Boss.h"

///
/// INIT FUNCTIONS
///

void Boss::initGui()
{
	/*
		@returns void

		initialises the healthbar
	*/

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
	// wywo³uje konstruktor klasy enemy i funkcje initGui() - inicjalizuj¹c¹ healthbar

	this->initGui();
}

Boss::~Boss()
{
	//
}

///
/// FUNCTIONS
///

void Boss::updateGui()
{
	/*
		@returns void

		funkcja aktualizuje healthbar
		- oblicza procent wype³nienia dziel¹c aktualne zdrowie przez maksymalne
		- zmienia d³ugoœæ paska zdrowia
		- przesuwa pasek zdrowia razem z bossem
	*/

	float hpPercent = static_cast<float>(this->getHp()) / this->getMaxHp();
	this->healthbar_.setSize(sf::Vector2f(hpPercent * this->healthbarBack_.getSize().x, this->healthbar_.getSize().y));

	this->healthbarBack_.setPosition(sf::Vector2f(this->getPos().x, this->getPos().y - 20));
	this->healthbar_.setPosition(sf::Vector2f(this->getPos().x, this->getPos().y - 20));
}

void Boss::renderGui(sf::RenderTarget& target)
{
	// renders healthbar on a given RenderTarget (Game::window_)

	target.draw(this->healthbarBack_);
	target.draw(this->healthbar_);
}