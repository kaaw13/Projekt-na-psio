#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player
{
private:
	/// VARIABLES
	sf::Sprite sprite_;
	sf::Texture texture_;

	float movementSpeed_;

	/// INIT FUNCTIONS
	void initVariables();
	void initTexture();
	void initSprite();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Player();
	virtual ~Player();

	/// GETTERS
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	/// SETTERS.
	void setPosition(const float x, const float y);

	/// FUNCTIONS
	//void move(const float dirX, const float dirY);

	void update();
	void render(sf::RenderTarget& target);
};

