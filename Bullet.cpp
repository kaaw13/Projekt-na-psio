#include "Bullet.h"

///
/// INIT FUNCTIONS
///

void Bullet::initVariables(sf::Vector2f player_pos, sf::Vector2f mouse_pos)
{
	/*
		returns @void
	
		funkcja przyjmuje w argumentach aktualn� pozycje gracza oraz myszki, 
		inicjalizuje zmienn� movementSpeed_, nast�pnie oblicza sk�adowe pr�dko�ci [Vx, Vy], z kt�rymi kula b�dzie si� porusza� i przekazuje je do wektora displacement_
		- inicjalizacja pr�dko�ci kuli oraz zmiennych pomocniczych Vx i Vy
		- obliczenie wektora [rx, ry], przesuni�cia pomi�dzy pozycjami gracza i myszy
		- je�eli ry nie jest r�wne zeru, obliczamy
			> ratio - stosunek pr�dko�ci Vx do Vy
			> warto�� Vy z przekszta�conego twierdzenia pitagorasa
			> zwrot Vy
			> Vx = ratio * Vy
		- je�eli ry jest r�wne zeru
			> Vy = 0
			> Vx = pr�dko�ci kuli
		- zainicjalizowanie wektora displacement warto�ciami Vx i Vy
	*/

	this->movementSpeed_ = 8.f;
	float Vx, Vy;

	// przesuni�cie
	float rx = mouse_pos.x - player_pos.x;
	float ry = mouse_pos.y - player_pos.y;

	// obliczenie Vx i Vy
	if (ry != 0)
	{
		float ratio = rx / ry;

		Vy = this->movementSpeed_ / sqrt(pow(ratio, 2) + 1);
		if (ry < 0) 
			Vy = -Vy;

		Vx = ratio * Vy;
	}
	else
	{
		Vy = 0;
		Vx = this->movementSpeed_;
	}

	// zainicjowanie displacement_
	this->displacement_ = sf::Vector2f(Vx, Vy);
}

void Bullet::initSprite(sf::Vector2f position, sf::Texture* texture)
{
	/*
		@returns void

		initialises Bullet's sprite
		- texture - given in constructor
		- position - given in constructor
		- scale
	*/

	this->sprite_.setTexture(*texture);
	this->sprite_.setPosition(position);
	this->sprite_.setScale(sf::Vector2f(0.2f, 0.2f));
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Bullet::Bullet(sf::Vector2f player_pos, sf::Vector2f mouse_pos, sf::Texture* texture, unsigned damage)
	: damage_(damage)
{
	// initialises damage_ and calls init function

	this->initVariables(player_pos, mouse_pos);
	this->initSprite(player_pos, texture);
}

Bullet::~Bullet()
{
	//
}

///
/// FUNCTIONS
///

void Bullet::update()
{
	// moves the Bullet with speeds from Bullet::displacement_, <sf::Vector2f>

	this->sprite_.move(this->displacement_);
}

void Bullet::render(sf::RenderTarget& target)
{
	// renders the Bullet on a target (Game::window)

	target.draw(this->sprite_);
}