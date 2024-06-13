#include "Entity.h"

///
/// INIT FUNCTIONS
///

void Entity::initSprite(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale)
{
	/*
		@returns void

		funkcja inicjalizuje sprite'a danymi przekazanymi w konstruktorze
		- tekstura
		- pozycja
		- skala
	*/

	this->sprite_ = new sf::Sprite(*texture);
	this->sprite_->setPosition(position);
	this->sprite_->setScale(scale);
}

void Entity::initHitBox()
{
	/*
		@returns void

		funkcja inicjalizuje hitbox wykorzystywany przy kolizjach
		- kopiuje sf::FloatRect sprita
		- zmniejsza go
		- przesuwa do œrodka
	*/

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
	// inicjalizuje wartoœci szybkoœci, obra¿eñ i zdrowia oraz wywo³uje funkcje incjalizuj¹ce sprite i hitbox

	this->initSprite(position, texture, scale);
	this->initHitBox();
}

Entity::~Entity()
{
	delete this->sprite_;
}

///
/// SETTERS
///

void Entity::move(sf::Vector2f displacement)
{
	/*
		@returns void

		funkcja realizuj¹ca przemieszczenie obiektu o zadan¹ wartoœæ
		- przemieszcza sprite
		- oraz hitbox
	*/

	this->sprite_->move(displacement);
	this->hitBox_.left += displacement.x;
	this->hitBox_.top += displacement.y;
}

void Entity::setPosition(const float x, const float y)
{
	/*
		@returns void

		funkcja ustawiaj¹ca obiekt w podanej pozycji
		- sprite 
		- hitbox
	*/

	this->sprite_->setPosition(x, y);
	this->hitBox_.left = x;
	this->hitBox_.top = y;
}

void Entity::setTexture(sf::Texture* texture)
{
	// funkcja pzowalaj¹ca zmieniaæ teksturê obiektu

	this->sprite_->setTexture(*texture);
}

void Entity::damage(unsigned damage)
{
	/*
		@returns void

		funkcja realizuj¹ca zadanie obra¿eñ obiektowi
		- zmiejszenie zdrowia o wartoœæ obra¿eñ
		- je¿eli zdrowie spad³o poni¿ej zera, ustawiane jest na 0
	*/

	this->hp_ -= damage;

	if (this->hp_ <= 0)
	{
		this->hp_ = 0;
	}
}

void Entity::heal(unsigned heal)
{
	/*
	@returns void

	funkcja realizuj¹ca leczenie obiektu
	- zwiêkszenie zdrowia o zadan¹ wartoœæ
	- je¿eli zdrowie przekroczy³o wartoœæ maksymaln¹, ustawiane jest na zdrowie maksymalne
	*/

	this->hp_ += heal;

	if (this->hp_ > this->maxHp_)
		this->hp_ = this->maxHp_;
}

void Entity::setCurrentHp(unsigned new_hp)
{
	// zmiana aktualnego zdrowia na zadan¹ wartoœæ

	this->hp_ = new_hp;
}

void Entity::setMaxHp(unsigned new_max_hp)
{
	// zmiana maksymalnego zdrowia na zadan¹ wartoœæ

	this->maxHp_ = new_max_hp;
}

void Entity::setDamage(int new_damage)
{
	// zmiana obra¿eñ na zadan¹ wartoœæ - nie mniejsz¹ ni¿ 1

	if (new_damage < 1)
		this->damage_ = 1;
	else
		this->damage_ = new_damage;		
}

void Entity::setSpeed(float new_speed)
{
	// zmiana prêdkoœci na zadan¹ wartoœæ - nie mniejsz¹ ni¿ 0.5f

	if (new_speed < 0.5f)
		this->damage_ = 0.5f;
	else
		this->movementSpeed_ = new_speed;
}

///
/// FUNCTIONS
///

void Entity::render(sf::RenderTarget& target)
{
	// renders the Entity on a target (Game::window_)

	target.draw(*this->sprite_);
}
