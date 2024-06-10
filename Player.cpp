#include "Player.h"

///
/// INIT FUNCTIONS
///

void Player::initVariables()
{
    this->movementSpeed_ = 4.0f;
    this->maxHp_ = 10;
    this->hp_ = maxHp_;
    this->damage_ = 5;
    this->shotCooldown_ = sf::seconds(0.7f);
    this->immunityCooldown_ = sf::seconds(2.f);
    this->immunity_ = false;
}

void Player::initSprite(sf::Texture* texture)
{
	// Sets the texture to the sprite
	this->sprite_.setTexture(*texture);

	// Resize the sprite
    this->sprite_.scale(sf::Vector2f(0.4f, 0.4f));
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

void Player::setPosition(const float x, const float y)
{
	this->sprite_.setPosition(x, y);
}

void Player::setCurrentHp(unsigned new_hp)
{
    this->hp_ = new_hp;
}

void Player::damage(unsigned damage)
{
    if (!immunity_)
    {
        this->hp_ -= damage;
        if (this->hp_ < 0)
            this->hp_ = 0;

        this->immunity_ = true;
        this->timeSinceDamaged_ = sf::Time::Zero;
    }
}

void Player::heal(unsigned heal)
{
    this->hp_ += heal;

    if (this->hp_ > this->maxHp_)
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

void Player::changeDamage(int amount)
{
    this->damage_ += amount;

    if (this->damage_ < 1)
        this->damage_ = 1;
}

void Player::updateImmunity()
{
    this->timeSinceDamaged_ += this->immunityClock_.restart();

    if (this->timeSinceDamaged_ > this->immunityCooldown_)
        this->immunity_ = false;
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
    this->updateImmunity();
    this->move();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_);
}
