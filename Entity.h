#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Entity
{
private:
	// VARIABLES
	sf::Sprite* sprite_;
	sf::FloatRect hitBox_;

	float movementSpeed_;
	unsigned damage_;
	unsigned maxHp_;
	unsigned hp_;

	// INIT FUNCTIONS
	virtual void initVariables() = 0;
	void initSprite(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale);
	void initHitBox();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Entity(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, float speed, unsigned damage, unsigned hp);
	virtual ~Entity();

	/// GETTERS
	// inline
	inline const sf::Vector2f& getPos()    const { return this->sprite_->getPosition(); };
	inline const sf::FloatRect getBounds() const { return this->sprite_->getGlobalBounds(); };
	inline const sf::FloatRect getHitbox() const { return this->hitBox_; };
	inline const unsigned&	   getMaxHp()  const { return this->maxHp_; };
	inline const int&		   getHp()	   const { return this->hp_; };
	inline const unsigned&	   getDamage() const { return this->damage_; };
	inline const float&		   getSpeed()  const { return this->movementSpeed_; };

	/// SETTERS
	void move(sf::Vector2f displacement);
	void setPosition(const float x, const float y);
	void setTexture(sf::Texture* texture);
	virtual void damage(unsigned damage);
	virtual void heal(unsigned heal);
	void setCurrentHp(unsigned new_hp);
	void setMaxHp(unsigned new_max_hp);
	void changeDamage(int amount);

	/// FUNCTIONS
	virtual void update() = 0;

	void render(sf::RenderTarget& target);
};

