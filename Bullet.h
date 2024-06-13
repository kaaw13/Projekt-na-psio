#pragma once

#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Bullet
{
private:
	/// VARIABLES
	sf::Sprite sprite_;

	unsigned damage_;
	float movementSpeed_;
	sf::Vector2f displacement_;	// wektor podawany jako argument do this->sprite_.move(displacement); zawiera [Vx, Vy];

	/// INIT FUNCTIONS
	void initVariables(sf::Vector2f player_pos, sf::Vector2f mouse_pos);
	void initSprite(sf::Vector2f player_pos, sf::Texture* texture);

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Bullet(sf::Vector2f player_pos, sf::Vector2f mouse_pos, sf::Texture* texture, unsigned damage);
	virtual ~Bullet();

	/// GETTERS
	// inline
	inline const sf::Vector2f& getPos()    const { return this->sprite_.getPosition(); };
	inline const sf::FloatRect getBounds() const { return this->sprite_.getGlobalBounds(); };
	inline const unsigned	   getDamage() const { return this->damage_; };

	/// FUNCTIONS
	void update();
	void render(sf::RenderTarget& target);
};
