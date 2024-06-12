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
	sf::Font* font_;

	sf::RectangleShape healthbar_;
	sf::RectangleShape healthbarBack_;

	sf::RectangleShape expBar_;
	sf::RectangleShape expBarBack_;
	sf::Text levelText_;

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
	Player(sf::Vector2f position, sf::Texture* default_texture, sf::Texture* immunity_texture, sf::Vector2u window_size, sf::Font* font, int level = 1, int exp = 0);
	virtual ~Player();

	/// GETTERS
	//inline
	inline const unsigned getLevel()		const { return this->level_; };
	inline const unsigned getCurrentExp()	const { return this->currentExperience_; };

	const float getTimeSinceLastShoot() const;
	const float getShootCooldown() const;

	/// SETTERS
	void damage(unsigned damage);
	void resetTimeSinceLastShot();
	void addExp(unsigned exp);
	void initialLevelUp();

	/// FUNCTIONS.
	void moveWasd();
	void updateImmunity();
	void updateGui();
	void renderGui(sf::RenderTarget& target);
	void updateLevel();

	void update();
};

