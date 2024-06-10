#include "Player.h"

///
/// INIT FUNCTIONS
///

void Player::initVariables()
{
    this->shotCooldown_ = sf::seconds(0.7f);
    this->immunityDuration_ = sf::seconds(2.f);
    this->immunity_ = false;
}

void Player::initClocks()
{
    this->timeSinceLastShot_ = sf::Time::Zero;
    this->shotClock_.restart();

    this->timeSinceDamaged_ = sf::Time::Zero;
    this->immunityClock_.restart();
}

///
/// CONSTRUCTORS AND DESTRUCTORS
/// 

Player::Player(sf::Vector2f position, sf::Texture* texture)
    : Entity(position, texture, {0.6f, 0.6f}, 4.f, 5, 10)
{
    /*
        @constructor

        - na liœcie inicjalizacyjnej ustawia texture podan¹ przez game
        - wywo³uje funkcje init
    */

    std::cout << "new player\n";

	this->initVariables();
    this->initClocks();
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

void Player::damage(unsigned damage)
{
    if (!immunity_)
    {
        this->Entity::damage(damage);

        this->immunity_ = true;
        this->timeSinceDamaged_ = sf::Time::Zero;
    }
}

void Player::resetTimeSinceLastShot()
{
    this->timeSinceLastShot_ = sf::Time::Zero;
}

void Player::updateImmunity()
{
    this->timeSinceDamaged_ += this->immunityClock_.restart();

    if (this->timeSinceDamaged_ > this->immunityDuration_)
        this->immunity_ = false;
}

///
/// FUNCTIONS
///

void Player::moveWasd()
{
    // Move player up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->Entity::move(sf::Vector2f(0.f, -this->Entity::getSpeed()));
    }
    // Move player down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->Entity::move(sf::Vector2f(0.f, this->Entity::getSpeed()));
    }
    // Move player left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->Entity::move(sf::Vector2f(-this->Entity::getSpeed(), 0.f));
    }
    // Move player right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->Entity::move(sf::Vector2f(this->Entity::getSpeed(), 0.f));
    }
}

void Player::update()
{
    this->timeSinceLastShot_ += this->shotClock_.restart();
    this->updateImmunity();
    this->moveWasd();
}
