#pragma once

#include "Bullet.h"
#include "Entity.h"

class Player : public Entity
{
private:
	/// VARIABLES
	// textures
	sf::Texture* defaultTexture_;
	sf::Texture* immunityTexture_;

	// shooting
	sf::Clock shotClock_;
	sf::Time shotCooldown_;
	sf::Time timeSinceLastShot_;

	// immunity
	bool immunity_;
	sf::Clock immunityClock_;
	sf::Time immunityDuration_;
	sf::Time timeSinceDamaged_;

	// healthbar
	sf::Vector2f windowSize_;
	sf::RectangleShape healthbar_;
	sf::RectangleShape healthbarBack_;

	/// INIT FUNCTIONS
	void initVariables();
	void initClocks();
	void initGui();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Player(sf::Vector2f position, sf::Texture* default_texture, sf::Texture* immunity_texture, sf::Vector2u window_size);
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
	void updateGui();
	void renderGui(sf::RenderTarget& target);

	void update();
};

