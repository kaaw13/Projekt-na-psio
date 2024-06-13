#pragma once

#include "Enemy.h"

class Boss : public Enemy
{
private:
	/// VARIABLES
	
	// healthbar
	sf::RectangleShape healthbar_;
	sf::RectangleShape healthbarBack_;

	/// INIT FUNCTIONS
	void initGui();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Boss(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, float speed, unsigned damage, unsigned maxHp, sf::Time stun);
	virtual ~Boss();

	/// FUNCTIONS
	void updateGui();
	void renderGui(sf::RenderTarget& target);
};

