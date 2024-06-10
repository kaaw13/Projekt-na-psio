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
	std::vector<sf::RectangleShape*> buttons_;
	std::vector<sf::Text*> menuTexts_;
	bool isMenu_;

	// resources
	std::map<std::string, sf::Texture*> textures_;
	std::vector<sf::Font*> fonts_;

	// player
	Player* player_;

	// level
	Level* level_;

	/// INIT FUNCTIONS
	void initWindow();
	void initTextures();
	void initPlayer();

	void initButtons();
	void initText();
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
	void updateLevel();
	
	void update();

	void renderMenu();

	void render();
};

