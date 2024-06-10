#pragma once

#include "Bullet.h"
#include "Entity.h"

class Player : public Entity
{
private:
	/// VARIABLES
	sf::Clock shotClock_;
	sf::Time shotCooldown_;
	sf::Time timeSinceLastShot_;

	bool immunity_;
	sf::Clock immunityClock_;
	sf::Time immunityDuration_;
	sf::Time timeSinceDamaged_;

	/// INIT FUNCTIONS
	void initVariables();
	void initClocks();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Player(sf::Vector2f position, sf::Texture* texture);
	virtual ~Player();

	/// GETTERS
	const float getTimeSinceLastShoot() const;
	const float getShootCooldown() const;

	/// SETTERS
	void damage(unsigned damage);
	void resetTimeSinceLastShot();

	/// FUNCTIONS.
	void moveWasd();
	void updateImmunity();
	void update();
};

