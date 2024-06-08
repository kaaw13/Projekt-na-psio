#pragma once

#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Bullet.h"

class Player
{
private:
	/// VARIABLES
	sf::Sprite sprite_;

	float movementSpeed_;
	unsigned maxHp_;
	int hp_;

	sf::Clock shotClock_;
	float shotCooldown_;
	bool canShot_;

	/// INIT FUNCTIONS
	void initVariables();
	void initSprite(sf::Texture* texture);
	void initClock();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Player(sf::Texture* texture);
	virtual ~Player();

	/// GETTERS
	const float getShotCd() const;
	const float getShotClockElapsed() const;

	// inline
	inline const sf::Vector2f& getPos()       const { return this->sprite_.getPosition(); };
	inline const sf::FloatRect getBounds()    const { return this->sprite_.getGlobalBounds(); };
	inline const unsigned	   getMaxHp()     const { return this->maxHp_; };
	inline const int		   getHp()		  const { return this->hp_; };
	inline const bool		   getCanShot()   const { return this->canShot_; };

	/// SETTERS
	void setPosition(const float x, const float y);
	void setCurrentHp(unsigned new_hp);
	void changeCurrentHp(int amount);
	void setMaxHp(unsigned new_max_hp);
	void resetShotClock();

	/// FUNCTIONS
	void move();
	void updateCanShoot();
	
	void update();
	void render(sf::RenderTarget& target);
};

