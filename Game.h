#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#include <map>

class Game
{
private:
	/// VARIABLES
	// window
	sf::RenderWindow* window_;
	sf::Event e;

	// resources
	std::map<std::string, sf::Texture*> textures_;

	// player
	Player* player_;

	/// INIT FUNCTIONS
	void initWindow();
	void initTextures();
	void initPlayer();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Game();
	virtual ~Game();

	/// GETTERS


	/// SETTERS


	/// FUNCTIONS
	void run();

	void updatePollEvents();
	
	void update();

	void render();
};

