#pragma once

#include "Player.h"
#include "Enemy.h"

#include <fstream>
#include <vector>

class Level
{
private:
	/// VARIABLES
	// from file
	std::string background_texture_key;
	std::string enemy_texture_key;
	float enemySpeed_;
	unsigned enemyMaxHp_;
	unsigned enemyDamage_;

	unsigned numberOfEnemies_;
	unsigned enemyCounter_;

	// window
	sf::RenderWindow* window_;

	// textures
	std::map<std::string, sf::Texture*>* textures_ptr;
	sf::Sprite* background_;

	// player
	Player* player_;
	std::vector<Bullet*> bullets_;

	// enemies
	std::vector<Enemy*> enemies_;
	sf::Clock* spawnClock_;
	sf::Time spawnCooldown_;

	/// INIT FUNCTIONS
	void initVariables();
	void initFromFiles(std::string path);
	void initBackground();
	void initClock();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Level(Player* player, sf::RenderWindow* window, std::map<std::string, sf::Texture*>* textures, std::string path);
	virtual ~Level();

	/// GETTERS
	const bool allEnemiesKilled() const;

	// inline
	inline const unsigned getPlayerHp() const { return this->player_->getHp(); };

	/// SETTERS


	/// FUNCTIONS
	void shoting();
	void playerWindowCollision();

	sf::Vector2f randSpawnPosition();
	void enemySpawning();
	void enemyCollision(Enemy* enemy, Entity* entity);
	void enemyKnockback(Enemy* enemy, Entity* entity, float knockback);
	void updateEnemies();
	void deleteEnemy(unsigned& counter);

	bool bulletCollision(Bullet* bullet, unsigned& counter);
	bool cullBullet(Bullet* bullet, unsigned& counter);
	void deleteBullet(unsigned& counter);
	void updateBullets();

	void update();

	void renderEnemies();
	void renderBullets();
	void render();
};

