#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Drop
{
private:
	/// VARIABLES
	sf::Sprite* sprite_;

	/// INIT FUNCTIONS
	void initSprite(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale);

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Drop(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale);
	virtual ~Drop();

	/// GETTERS
	// inline
	inline const sf::Vector2f& getPos()    const { return this->sprite_->getPosition(); };
	inline const sf::FloatRect getBounds() const { return this->sprite_->getGlobalBounds(); };

	/// SETTERS


	/// FUNCTIONS
	void update();
	void render(sf::RenderTarget& target);
};

