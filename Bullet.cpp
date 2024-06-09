#include "Bullet.h"
///
/// INIT FUNCTIONS
///

void Bullet::initVariables(sf::Vector2f player_pos, sf::Vector2f mouse_pos)
{
	/*
		returns @void
	
		funkcja przyjmuje w argumentach aktualn¹ pozycje gracza oraz myszki, inicjalizuje zmienn¹ movementSpeed_,
		nastêpnie oblicza sk³adowe prêdkoœci [Vx, Vy], z którymi kula bêdzie siê poruszaæ i przekazuje je do wektora displacement_
		1) [rx, ry] wektor przesuniêcia
		2) ratio - stosunek prêdkoœci Vx do Vy
		3) obliczenie Vy z twierdzenia pitagorasa:
			> V^2 = Vx^2 + Vy^2
			> Vx = ratio * Vy
			> V^2 = Vy^2 * (ratio^2 + 1)
			> Vy = V / sqrt(ratio^2 + 1)  -  ten wzór jest widoczny w kodzie
		4) ustalenie kierunku Vy
		5) obliczenie Vx
		6) zainicjalizowanie wektora displacement
	*/

	this->movementSpeed_ = 1.f;
	float Vx, Vy;

	float px = player_pos.x;
	float py = player_pos.y;

	float mx = mouse_pos.x;
	float my = mouse_pos.y;

	float rx = mx - px;
	float ry = my - py;

	float s = rx / ry;

	Vy = this->movementSpeed_ / sqrt(pow(s, 2) + 1);

	if (ry < 0) Vy = -Vy;

	Vx = s * Vy;

	std::cout << "Player: " << px << ":" << py << " Mouse: " << mx << ":" << my << " r: " << rx << ":" << ry << " s: " << s << " disp: " << Vx << ":" << Vy << std::endl;

	this->displacement_ = sf::Vector2f(Vx, Vy);
}

void Bullet::initSprite(sf::Vector2f position, sf::Texture* texture)
{
	this->sprite_.setTexture(*texture);
	this->sprite_.setPosition(position);
	this->sprite_.setScale(sf::Vector2f(0.2f, 0.2f));
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Bullet::Bullet(sf::Vector2f player_pos, sf::Vector2f mouse_pos, sf::Texture* texture)
{
	this->initVariables(player_pos, mouse_pos);
	this->initSprite(player_pos, texture);
}

Bullet::~Bullet()
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

void Bullet::update()
{
	this->sprite_.move(this->displacement_);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_);
}