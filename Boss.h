#pragma once

#include "Enemy.h"

/*
POMYS£Y NA BOSSOW
- powolny, robi siê coraz wiêkszy
- swarm
- zatrzymuje siê, dostaje immunity i strzela w cztery strony swiata
*/

class Boss : public Enemy
{
private:
	/// VARIABLES
	
	// healthbar
	sf::RectangleShape healthbar_;
	sf::RectangleShape healthbarBack_;

	/// INIT FUNCTIONS
	void initVariables();
	void initGui();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Boss(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, float speed, unsigned damage, unsigned maxHp);
	virtual ~Boss();

	/// GETTERS


	/// SETTERS


	/// FUNCTIONS
	void updateGui();

	void renderGui(sf::RenderTarget& target);
};

