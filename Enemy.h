#pragma once

#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy
{
private:
	/// VARIABLES
	sf::Sprite sprite_;

	float movementSpeed_;
	unsigned maxHp_;
	int hp_;

	/// INIT FUNCTIONS
	void initVariables();
	void initSprite(sf::Vector2f position, sf::Texture* texture);

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Enemy(sf::Vector2f position, sf::Texture* texture);
	virtual ~Enemy();

	/// GETTERS
	// inline
	inline const sf::Vector2f& getPos()    const { return this->sprite_.getPosition(); };
	inline const sf::FloatRect getBounds() const { return this->sprite_.getGlobalBounds(); };

	/// SETTERS


	/// FUNCTIONS
	void move(float px, float py);
	void update(sf::Vector2f playerPos);

	void render(sf::RenderTarget& target);
};