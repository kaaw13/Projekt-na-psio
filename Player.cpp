#include "Player.h"

///
/// INIT FUNCTIONS
///

void Player::initVariables()
{
    this->movementSpeed_ = 5.0f;
    this->maxHp_ = 10;
    this->hp_ = maxHp_;
}

void Player::initSprite(sf::Texture* texture)
{
	// Sets the texture to the sprite
	this->sprite_.setTexture(*texture);

	// Resize the sprite
    this->sprite_.scale(sf::Vector2f(0.2f, 0.2f));
}

///
/// CONSTRUCTORS AND DESTRUCTORS
/// 

Player::Player(sf::Texture* texture)
{
    /*
        @constructor

        - na liœcie inicjalizacyjnej ustawia texture podan¹ przez game
        - wywo³uje funkcje init
    */

    std::cout << "new player\n";

	this->initVariables();
	this->initSprite(texture);
}

Player::~Player()
{

}

///
/// GETTERS
///



///
/// SETTERS
///

void Player::setPosition(const float x, const float y)
{
	this->sprite_.setPosition(x, y);
}

void Player::setCurrentHp(unsigned new_hp)
{
    this->hp_ = new_hp;
}

void Player::changeCurrentHp(int amount)
{
    /*
        @returns void

        funckja odpowiada za zmianê hp o wartoœæ podan¹ w argumencie (amount),
        dotyczy to zarówno leczenia i obra¿eñ -> wartoœci dodatnich i ujemnych
        - zmiana hp_
        - sprawdzenie czy hp_ < 0
        - sprawdzenie czy hp_ > maxHp_
    */

    this->hp_ += amount;

    if (this->hp_ < 0)
        this->hp_ = 0;
    else if (this->hp_ > this->maxHp_)
        this->hp_ = this->maxHp_;
}

void Player::setMaxHp(unsigned new_max_hp)
{
    this->maxHp_ = new_max_hp;
}

///
/// FUNCTIONS
///



void Player::move()
{
    // Move player up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->sprite_.move(0.f, -this->movementSpeed_);
    }
    // Move player down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->sprite_.move(0.f, this->movementSpeed_);
    }
    // Move player left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->sprite_.move(-this->movementSpeed_, 0.f);
    }
    // Move player right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->sprite_.move(this->movementSpeed_, 0.f);
    }
}

void Player::update()
{
    this->move();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_);
}
