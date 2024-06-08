#pragma once

#include "Player.h"
#include "Enemy.h"

class Level
{
private:
	/// VARIABLES

	// base
	sf::RenderWindow* window_;

	// textures
	std::map<std::string, sf::Texture*>* textures_ptr;
	sf::Sprite* background_;

	// player
	Player* player_;
	std::vector<Bullet*> bullets_;

	// enemies.
	std::vector<Enemy*> enemies_;
	sf::Clock* spawnClock_;
	sf::Time spawnCooldown_;

	/// INIT FUNCTIONS
	void initTextures(std::map<std::string, sf::Texture*>* textures);
	void initPlayer();
	void initBackground();
	void initEnemies();
	void initClock();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Level(Player* player, sf::RenderWindow* window, std::map<std::string, sf::Texture*>* textures);
	virtual ~Level();

	/// GETTERS


	/// SETTERS


	/// FUNCTIONS
	sf::Vector2f randSpawnPosition();
	void enemySpawning();
	void updateEnemies();

	void shoting();
	void updateBullets();
	void cullBullets();

	void update();

	void renderEnemies();
	void renderBullets();
	void render();
};

