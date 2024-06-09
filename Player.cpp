#include "Player.h"

///
/// INIT FUNCTIONS
///

void Player::initVariables()
{
    this->movementSpeed_ = 4.0f;
    this->maxHp_ = 10;
    this->hp_ = maxHp_;
    this->shotCooldown_ = sf::seconds(1.f);
    this->timeSinceLastShot_ = sf::Time::Zero;
}

void Player::initSprite(sf::Texture* texture)
{
	// Sets the texture to the sprite
	this->sprite_.setTexture(*texture);

	// Resize the sprite
    this->sprite_.scale(sf::Vector2f(0.4f, 0.4f));
}

void Player::initClock()
{
    //this->shotClock_ = new sf::Clock;
    this->shotClock_.restart();
}

///
/// CONSTRUCTORS AND DESTRUCTORS
/// 

Player::Player(sf::Texture* texture)
{
    /*
        @constructor

        - na li�cie inicjalizacyjnej ustawia texture podan� przez game
        - wywo�uje funkcje init
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

const float Player::getTimeSinceLastShoot() const
{
    return timeSinceLastShot_.asSeconds();
}

const float Player::getShootCooldown() const
{
    return shotCooldown_.asSeconds();
}

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

        funckja odpowiada za zmian� hp o warto�� podan� w argumencie (amount),
        dotyczy to zar�wno leczenia i obra�e� -> warto�ci dodatnich i ujemnych
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

void Player::resetTimeSinceLastShot()
{
    this->timeSinceLastShot_ = sf::Time::Zero;
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
    this->timeSinceLastShot_ += this->shotClock_.restart();
    this->move();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_);
}
