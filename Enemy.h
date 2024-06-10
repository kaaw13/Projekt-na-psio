#pragma once

#include "Entity.h"

class Enemy : public Entity
{
private:
	/// VARIABLES
	bool isStunned_;
	sf::Clock stunClock_;
	sf::Time stunDuration_;
	sf::Time timeSinceStunned_;

	/// INIT FUNCTIONS
	void initVariables();
	void initClocks();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Enemy(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, float speed, unsigned damage, unsigned maxHp);
	virtual ~Enemy();

	/// GETTERS

	/// SETTERS
	void damage(unsigned damage);
	void stun();
	void setStunDuration(sf::Time duration);

	/// FUNCTIONS
	void move(float px, float py);
	void updateStun();
	void update();
	void update(sf::Vector2f playerPos);
};