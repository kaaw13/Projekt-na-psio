#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Level.h"
#include "Pause.h"

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

	//Pauza
	Pause pause_;
	sf::RectangleShape* pauseButton_;
	sf::Text pauseText_;

	// resources
	std::map<std::string, sf::Texture*> textures_;
	std::vector<sf::Font*> fonts_;
		
	// player
	Player* player_;
	std::string playerNickname_;

	// file
	int levelFromFile_;
	int expFromFile_;
	bool playerFound_;
	std::vector<std::string> fileTextLines_;

	// level
	Level* level_;

	/// INIT FUNCTIONS
	void initWindow();
	void initTextures();
	void initPlayer();
	void initVariables();

	void initpauseMenu();
	void initButtons();
	void initText();
	void initMenu();

	//void saveNickname(const std::string& filename, const std::string& nick,unsigned poziom, unsigned xp);
	//int findNickname(const std::string& filename);
	int findNickname(const std::string& filename);
	void inputFromFile(const std::string& filename);
	void saveNickname(const std::string& filename);

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

