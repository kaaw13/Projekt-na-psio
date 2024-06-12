#pragma once

#include "Player.h"
#include "Boss.h"
#include "Drop.h"

#include <fstream>
#include <vector>

class Level
{
private:
	/// VARIABLES

	// FROM FILE
	// textures
	std::string background_texture_key;
	std::string enemy_texture_key;
	std::string boss_texture_key; 

	// enemy stats
	float enemySpeed_;
	unsigned enemyMaxHp_;
	unsigned enemyDamage_;
	sf::Vector2f enemyScale_;
	sf::Time enemyStun_;

	unsigned numberOfEnemies_;
	unsigned enemyCounter_;

	// boss stats
	float bossSpeed_; 
	unsigned bossMaxHp_; 
	unsigned bossDamage_; 
	sf::Vector2f bossScale_; 
	sf::Time bossStun_; 

	// STATIC
	// window
	sf::RenderWindow* window_;
	sf::Sprite* background_;

	// textures
	std::map<std::string, sf::Texture*>* textures_ptr;

	// player
	Player* player_;
	std::vector<Bullet*> bullets_;

	// enemies
	std::vector<Enemy*> enemies_;
	Boss* boss_;

	sf::Clock* spawnClock_;
	sf::Time spawnCooldown_;

	// drops
	std::vector<Drop*> drops_;
	unsigned dropHeal_;
	unsigned dropExp_;

	// waves
	sf::Clock* waveCooldownClock_;
	sf::Time waveCooldown_;
	bool wave_1, wave_2, wave_3, bossFight_;

	/// INIT FUNCTIONS.
	void initVariables();
	void initFromFiles(std::string path);
	void initBackground();
	void initClocks();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Level(Player* player, sf::RenderWindow* window, std::map<std::string, sf::Texture*>* textures, std::string path);
	virtual ~Level();

	/// GETTERS
	const bool bossDefeated() const;

	// inline
	inline const unsigned getPlayerHp() const { return this->player_->getHp(); };

	/// SETTERS


	/// FUNCTIONS
	// window related
	void shoting();
	void playerWindowCollision();

	// enemy related
	sf::Vector2f randSpawnPosition();
	void createEnemy();
	void nextWave(bool& prev_wave, bool& next_wave, float enemy_amount_change, float spawn_cooldown_change);
	void updateWave();

	void enemyCollision(Enemy* enemy);
	void enemyKnockback(Enemy* enemy, Entity* entity, float knockback);
	void updateEnemies();
	void deleteEnemy(unsigned& counter);

	void updateBoss();

	// drop related
	void createDrop(sf::Vector2f position);
	void updateDropCollision();

	// bullet related
	bool bulletEnemyCollision(Bullet* bullet, unsigned& counter);
	bool cullBullet(Bullet* bullet, unsigned& counter);
	void deleteBullet(unsigned& counter);
	void updateBullets();

	// main update
	void update();

	// remdering
	void renderEnemies();
	void renderBullets();
	void renderDrops();
	void render();
};

