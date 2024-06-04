#include "Player.h"

///
/// INIT FUNCTIONS
///

void Player::initVariables()
{
	//
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
	//this->sprite_.scale(sf::Vector2f(0.2f, 0.2f));
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

}

void Player::render(sf::RenderTarget& target)
{

}
