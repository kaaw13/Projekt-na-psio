#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Level.h"

#include <map>

class Game
{
private:
	/// VARIABLES
	// window
	sf::RenderWindow* window_;
	sf::Event e;
	sf::Vector2i mousePos_;

	// menu
	sf::RectangleShape* button_1;
	sf::RectangleShape* button_2;
	sf::RectangleShape* button_3;
	bool isMenu_;

	// resources
	std::map<std::string, sf::Texture*> textures_;

	// player
	Player* player_;

	// level
	Level* level_;

	/// INIT FUNCTIONS
	void initWindow();
	void initTextures();
	void initPlayer();
	void initMenu();

public:
	/// CONSTRUCTORS AND DESTRUCTORS
	Game();
	virtual ~Game();

	/// GETTER

	/// SETTERS

	/// FUNCTIONS
	void run();

	void updatePollEvents();
	void updateMenu();
	
	void update();

	void renderMenu();

	void render();
};

