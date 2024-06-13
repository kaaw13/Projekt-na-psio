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
		- przesuwa do �rodka
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
	// inicjalizuje warto�ci szybko�ci, obra�e� i zdrowia oraz wywo�uje funkcje incjalizuj�ce sprite i hitbox

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

		funkcja realizuj�ca przemieszczenie obiektu o zadan� warto��
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

		funkcja ustawiaj�ca obiekt w podanej pozycji
		- sprite 
		- hitbox
	*/

	this->sprite_->setPosition(x, y);
	this->hitBox_.left = x;
	this->hitBox_.top = y;
}

void Entity::setTexture(sf::Texture* texture)
{
	// funkcja pzowalaj�ca zmienia� tekstur� obiektu

	this->sprite_->setTexture(*texture);
}

void Entity::damage(unsigned damage)
{
	/*
		@returns void

		funkcja realizuj�ca zadanie obra�e� obiektowi
		- zmiejszenie zdrowia o warto�� obra�e�
		- je�eli zdrowie spad�o poni�ej zera, ustawiane jest na 0
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

	funkcja realizuj�ca leczenie obiektu
	- zwi�kszenie zdrowia o zadan� warto��
	- je�eli zdrowie przekroczy�o warto�� maksymaln�, ustawiane jest na zdrowie maksymalne
	*/

	this->hp_ += heal;

	if (this->hp_ > this->maxHp_)
		this->hp_ = this->maxHp_;
}

void Entity::setCurrentHp(unsigned new_hp)
{
	// zmiana aktualnego zdrowia na zadan� warto��

	this->hp_ = new_hp;
}

void Entity::setMaxHp(unsigned new_max_hp)
{
	// zmiana maksymalnego zdrowia na zadan� warto��

	this->maxHp_ = new_max_hp;
}

void Entity::setDamage(int new_damage)
{
	// zmiana obra�e� na zadan� warto�� - nie mniejsz� ni� 1

	if (new_damage < 1)
		this->damage_ = 1;
	else
		this->damage_ = new_damage;		
}

void Entity::setSpeed(float new_speed)
{
	// zmiana pr�dko�ci na zadan� warto�� - nie mniejsz� ni� 0.5f

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
