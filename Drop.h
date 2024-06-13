#pragma once

#include "Player.h"

enum DROP_TYPE
{
	EXP = 0, MEDKIT = 1
};

class Drop
{
private:
	/// VARIABLES
	sf::Sprite* sprite_;
	DROP_TYPE type_;
	int value_;			// value of experience or healing - determined by type_

	/// INIT FUNCTIONS
	void initSprite(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale);

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Drop(sf::Vector2f position, sf::Texture* texture, sf::Vector2f scale, DROP_TYPE type, int value);
	virtual ~Drop();

	/// GETTERS
	// inline
	inline const sf::Vector2f& getPos()    const { return this->sprite_->getPosition(); };
	inline const sf::FloatRect getBounds() const { return this->sprite_->getGlobalBounds(); };
	inline const DROP_TYPE	   getType()   const { return this->type_; };
	inline const int		   getValue()  const { return this->value_; };

	/// FUNCTIONS
	void collide(Player* player);
	void render(sf::RenderTarget& target);
};

