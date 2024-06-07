#pragma once

#include "Player.h"
#include "Enemy.h"

class Level
{
private:
	/// VARIABLES

	// base
	sf::RenderWindow* window_;

	sf::Clock spawnClock_;
	int spawnCooldown_;

	// textures
	sf::Texture* enemyTexture_;
	sf::Sprite* background_;

	// game objects
	Player* player_;
	std::vector<Enemy*> enemies_;

	/// INIT FUNCTIONS
	void initPlayer();
	void initBackground(sf::Texture* background_texture);
	void initEnemies();
	void initClock();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Level(Player* player, sf::RenderWindow* window, sf::Texture* background_texture, sf::Texture* enemy_texture);
	virtual ~Level();

	/// GETTERS


	/// SETTERS


	/// FUNCTIONS
	sf::Vector2f randSpawnPosition();
	void enemySpawning();

	void update();

	void renderEnemies();
	void render();
};

