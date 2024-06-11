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
	bool backspaceKeyReleased_;
	bool enterKeyPressed_;
	bool enteringNickname_;
	// resources
	std::map<std::string, sf::Texture*> textures_;
	std::vector<sf::Font*> fonts_;
	//nickname
	std::string text_;
	std::string currentNickname_;
	std::string playerNickname_;
	int playerScore_;
	
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
	void saveNickname(const std::string& filename, const std::string& nick, int wynik);
	int findNickname(const std::string& filename, const std::string& nick);

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

