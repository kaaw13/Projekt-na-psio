#include "Player.h"

///
/// INIT FUNCTIONS
///

void Player::initVariables()
{
    this->movementSpeed_ = 5.0f;
}

void Player::initTexture()
{
	// Loads a texture from a file
	if (!this->texture_.loadFromFile("Textures/playerSheet.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::failed loading playerShip.png\n";
	}
}

void Player::initSprite()
{
	// Sets the texture to the sprite
	this->sprite_.setTexture(this->texture_);

	//Resize the sprite
	
    this->sprite_.scale(sf::Vector2f(0.2f, 0.2f));
}

///
/// CONSTRUCTORS AND DESTRUCTORS
/// 

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

///
/// GETTERS
///

const sf::Vector2f& Player::getPos() const
{
	return this->sprite_.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite_.getGlobalBounds();
}


///
/// SETTERS
///

void Player::setPosition(const float x, const float y)
{
	this->sprite_.setPosition(x, y);
}

///
/// FUNCTIONS
///

void Player::update()
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

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite_);
}
