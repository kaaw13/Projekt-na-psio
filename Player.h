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

	// Gui
	sf::Vector2f windowSize_;

	sf::RectangleShape healthbar_;
	sf::RectangleShape healthbarBack_;

	sf::RectangleShape expBar_;
	sf::RectangleShape expBarBack_;

	// level
	unsigned level_;
	unsigned currentExperience_;
	unsigned expForLevelup_;

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
	//inline
	inline const unsigned getLevel()        const { return this->level_; };
	inline const unsigned getCurrentExp()    const { return this->currentExperience_; };
	/// SETTERS
	void damage(unsigned damage);
	void resetTimeSinceLastShot();
	void addExp(unsigned exp);

	/// FUNCTIONS.
	void moveWasd();
	void updateImmunity();
	void updateGui();
	void renderGui(sf::RenderTarget& target);
	void updateLevel();
	
	void update();
	friend class Game;

};

