#include "Game.h"

///
/// INIT FUNCTIONS
/// 

void Game::initWindow()
{
	/*
		@returns void

		initialises the window
		- size and style
		- limiting framerate
	*/

	this->window_ = new sf::RenderWindow(sf::VideoMode(1920, 1080), "window", sf::Style::Fullscreen);	// okno docelowe
	//this->window_ = new sf::RenderWindow(sf::VideoMode(1200, 900), "window", sf::Style::Close);			// okienko tymczasowe do wygodniejszego testowania
	this->window_->setFramerateLimit(144);
	this->window_->setVerticalSyncEnabled(false);
	std::cout << "initWindow\n";
}

void Game::initPlayer()
{
	// creates a default player

	this->player_ = new Player(sf::Vector2f(this->window_->getSize().x / 2, this->window_->getSize().y / 2),
		textures_["PLAYER_SHEET"], textures_["PLAYER_IMMUNITY"], this->window_->getSize(), this->fonts_[1]);
}

void Game::initVariables()
{
	// initialises variabels

	this->levelFromFile_ = 1;
	this->expFromFile_ = 0;
	this->playerFound_ = false;
	this->playerNickname_ = " ";
}

void Game::initTextures()
{
	/*
		@returns void

		wczytuje wszystkie textury i dodaje je do wektora textures_
		- player textures
		- bullet
		- backgrounds
		- enemies
		- bosses
		- drops
	*/

	this->textures_["PLAYER_SHEET"] = new sf::Texture;
	if (!this->textures_["PLAYER_SHEET"]->loadFromFile("Textures/playerSheet.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load playerSheet.png\n";
	}

	this->textures_["PLAYER_IMMUNITY"] = new sf::Texture;
	if (!this->textures_["PLAYER_IMMUNITY"]->loadFromFile("Textures/playerImmunity.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load playerImmunity.png\n";
	}

	this->textures_["BULLET"] = new sf::Texture;
	if (!this->textures_["BULLET"]->loadFromFile("Textures/bullet.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load bullet.png\n";
	}

	this->textures_["BACKGROUND_1"] = new sf::Texture;
	if (!this->textures_["BACKGROUND_1"]->loadFromFile("Textures/background1.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load background1.png\n";
	}

	this->textures_["BACKGROUND_2"] = new sf::Texture;
	if (!this->textures_["BACKGROUND_2"]->loadFromFile("Textures/background2.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load background2.png\n";
	}

	this->textures_["ENEMY_1"] = new sf::Texture;
	if (!this->textures_["ENEMY_1"]->loadFromFile("Textures/enemy1.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load enemy1.png\n";
	}

	this->textures_["ENEMY_2"] = new sf::Texture;
	if (!this->textures_["ENEMY_2"]->loadFromFile("Textures/enemy2.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load enemy2.png\n";
	}

	this->textures_["ENEMY_3"] = new sf::Texture;
	if (!this->textures_["ENEMY_3"]->loadFromFile("Textures/enemy3.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load enemy3.png\n";
	}

	this->textures_["BOSS_1"] = new sf::Texture;
	if (!this->textures_["BOSS_1"]->loadFromFile("Textures/boss1.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load boss1.png\n";
	}

	this->textures_["BOSS_2"] = new sf::Texture;
	if (!this->textures_["BOSS_2"]->loadFromFile("Textures/boss2.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load boss2.png\n";
	}

	this->textures_["BOSS_3"] = new sf::Texture;
	if (!this->textures_["BOSS_3"]->loadFromFile("Textures/boss3.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load boss3.png\n";
	}

	this->textures_["EXP_DROP"] = new sf::Texture;
	if (!this->textures_["EXP_DROP"]->loadFromFile("Textures/expDrop.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load expDrop.png\n";
	}

	this->textures_["MEDKIT"] = new sf::Texture;
	if (!this->textures_["MEDKIT"]->loadFromFile("Textures/medkit.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load medkit.png\n";
	}
}

void Game::initText()
{
	/*
		@returns void

		- initialises fonts and adds them to the fonts_ vector
		- initialises menu texts
	*/

	this->fonts_.push_back(new sf::Font);	
	if (!this->fonts_[0]->loadFromFile("Fonts/ARCADECLASSIC.ttf"))
	{
		std::cout << "GAME::INITFONTS::Failed to load ARCADECLASSIC.ttf\n";
	}

	this->fonts_.push_back(new sf::Font);
	if (!this->fonts_[1]->loadFromFile("Fonts/FFFFORWA.ttf"))
	{
		std::cout << "GAME::INITFONTS::Failed to load FFFFORWA.ttf\n";
	}

	this->menuTexts_.push_back(new sf::Text("Very epic game", *this->fonts_[0], 64));
	this->menuTexts_[0]->setFillColor(sf::Color::White);
	this->menuTexts_[0]->setPosition(sf::Vector2f(this->window_->getSize().x/2 - this->menuTexts_[0]->getGlobalBounds().width/2, 30.f));

	this->menuTexts_.push_back(new sf::Text("Enter your nick", *this->fonts_[0], 44));
	this->menuTexts_[1]->setFillColor(sf::Color::White);
	this->menuTexts_[1]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - this->menuTexts_[1]->getGlobalBounds().width - 20, 400.f));

	this->menuTexts_.push_back(new sf::Text("", *this->fonts_[0], 44));
	this->menuTexts_[2]->setFillColor(sf::Color::White);
	this->menuTexts_[2]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 + 20, 400.f));

	this->menuTexts_.push_back(new sf::Text("Level 1", *this->fonts_[0], 44));
	this->menuTexts_[3]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[3]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - this->menuTexts_[3]->getGlobalBounds().width / 2 - 250, 250.f));
	this->menuTexts_.push_back(new sf::Text("Level 2", *this->fonts_[0], 44));
	this->menuTexts_[4]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[4]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - this->menuTexts_[4]->getGlobalBounds().width / 2 + 50, 250.f));
	this->menuTexts_.push_back(new sf::Text("Level 3", *this->fonts_[0], 44));
	this->menuTexts_[5]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[5]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - this->menuTexts_[5]->getGlobalBounds().width / 2 + 350, 250.f));

	this->menuTexts_.push_back(new sf::Text("Exit", *this->fonts_[0], 44));
	this->menuTexts_[6]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[6]->setPosition(sf::Vector2f(this->buttons_[3]->getPosition().x + 50, 650.f));

	this->menuTexts_.push_back(new sf::Text("Enter nick", *this->fonts_[0], 44));
	this->menuTexts_[7]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[7]->setPosition(sf::Vector2f(this->buttons_[4]->getPosition().x + 50, 650.f));
	
}

void Game::initButtons()
{
	/*
		@returns void

		initialises menu buttons and adds them to buttons_ vector
	*/

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[0]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - this->buttons_[0]->getGlobalBounds().width / 2 - 300, 200.f));
	this->buttons_[0]->setFillColor(sf::Color::White);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[1]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - this->buttons_[1]->getGlobalBounds().width / 2, 200.f));
	this->buttons_[1]->setFillColor(sf::Color::White);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[2]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - this->buttons_[2]->getGlobalBounds().width / 2 + 300, 200.f));
	this->buttons_[2]->setFillColor(sf::Color::White);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[3]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - 2*this->buttons_[3]->getGlobalBounds().width, 600.f));
	this->buttons_[3]->setFillColor(sf::Color::Blue);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[4]->setPosition(sf::Vector2f(this->window_->getSize().x / 2 + 1*this->buttons_[0]->getGlobalBounds().width, 600.f));
	this->buttons_[4]->setFillColor(sf::Color::Yellow);
}

void Game::initpauseMenu()
{
	/*
		@returns void

		initialises pause menu
		- text
		- button
	*/

	pauseText_.setFont(*this->fonts_[0]);
	pauseText_.setString("Pause");
	pauseText_.setCharacterSize(72);
	pauseText_.setFillColor(sf::Color::Red);
	pauseText_.setPosition(this->window_->getSize().x / 2 - pauseText_.getGlobalBounds().width / 2, this->window_->getSize().y / 2 - pauseText_.getGlobalBounds().height / 2 - 200);

	this->pauseButton_ = new sf::RectangleShape(sf::Vector2f(200.f, 50.f));
	this->pauseButton_->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - 100.f, this->window_->getSize().y / 2 - 100.f));
	this->pauseButton_->setFillColor(sf::Color::Green);
}

void Game::initMenu()
{
	/*
		@returns void

		initialises the menu
		- sets isMenu_ flag to true
		- creates menu texts
		- creates buttons
	*/

	this->isMenu_ = true;
	this->initButtons();
	this->initText();
		
}

///
/// CONSTRUCTORS AND DESTRUCTORS
///

Game::Game()
{
	// calls all the init-Functions
	this->initWindow();
	this->initTextures();
	this->initMenu();
	this->initPlayer();
	this->initpauseMenu();
	this->initVariables();
}

Game::~Game()
{
	// deletes all objects

	delete this->player_;

	for (auto& el : this->textures_)
	{
		delete el.second;
	}
	for (auto& el : this->buttons_)
	{
		delete el;
	}
	for (auto& el : this->fonts_)
	{
		delete el;
	}
	for (auto& el : this->menuTexts_)
	{
		delete el;
	}

	delete this->pauseButton_;

	delete this->window_;
}

///
/// FUNCTIONS
///

// obs³uga plików

int Game::findNickname()
{
	/*
		@returns int

		funkcja odpowiada za znalezienie w wektorze Game::fileTextLines_ szukanego nicku, a nastêpnie zwrócenie jego pozycji w wektorze
		- je¿eli nick nie zostanie znaleziony zwracana jest wartoœæ -1
	*/

	int line_number = 0;

	for (line_number; line_number < this->fileTextLines_.size(); ++line_number)
	{
		std::cout << "-" << fileTextLines_[line_number].substr(0, fileTextLines_[line_number].find(' ')) << "-" << playerNickname_.substr(1, playerNickname_.size()) << "\n";

		if (fileTextLines_[line_number][0] == ' ')
		{
			if (fileTextLines_[line_number].substr(1, fileTextLines_[line_number].find(' ')) == playerNickname_.substr(1, playerNickname_.size()))
			{
				std::cout << line_number << std::endl;
				return line_number;
			}
		}
		else
		{
			if (fileTextLines_[line_number].substr(0, fileTextLines_[line_number].find(' ')) == playerNickname_.substr(1, playerNickname_.size()))
			{
				std::cout << line_number << std::endl;
				return line_number;
			}
		}
	}

	return -1;
}

void Game::inputFromFile(const std::string& filename)
{
	/*
		@returns void

		funkcja odpowiada za wczytanie z pliku poziomu gracza, o podanym nicku, aby móg³ kontynuowaæ rozgrywkê ze swoj¹ postaci¹
		- otwrcie pliku i zapisanie wszystkich jego linii w wektorze
		- znaleienie linii, w której znajduje siê szukany nick i zapisanie jej numeru w zmiennej line_number
		- je¿eli nick zosta³ znaleziony, ze stringa fileTextLines_[line_number] odczytywane i zapisywane sa wartoœci levelFromFile_ oraz expFromFile_
		- w przeciwnym wypadku przypisywane im s¹ kolejno wartoœci 1 oraz 0
		- plik jest zamykany
	*/

	std::ifstream file(filename);
	std::string line;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			this->fileTextLines_.push_back(line);
		}
	}

	int line_number = findNickname();

	std::cout << "input frrom file line " << line_number << std::endl;

	if (line_number != -1)
	{
		size_t spacePos = fileTextLines_[line_number].find(' ');
		size_t nextSpacePos = fileTextLines_[line_number].find(' ', spacePos + 1);

		this->levelFromFile_ = std::stoi(fileTextLines_[line_number].substr(spacePos + 1, nextSpacePos - spacePos - 1));

		spacePos = nextSpacePos;
		nextSpacePos = fileTextLines_[line_number].find(' ', spacePos + 1);

		this->expFromFile_ = std::stoi(fileTextLines_[line_number].substr(spacePos + 1, nextSpacePos - spacePos - 1));

		std::cout << "level from file " << levelFromFile_ << " exp from file " << expFromFile_ << "\n";
	}
	else
	{
		this->levelFromFile_ = 1;
		this->expFromFile_ = 0;

		std::cout << "level " << levelFromFile_ << " exp " << expFromFile_ << "\n";
	}

	file.close();
}

void Game::saveNickname(const std::string& filename) 
{
	/*
		@returns void

		funckja odpowiedzialna za zapisanie do pliku nicku gracza, wraz z poziomem i doœwiadczeniem
		- otwarcie pliku
		- u¿ycie funkcji findNickname() do znalezienia linii, w której znajduj¹ siê ju¿ informacje o graczu
		- je¿eli tak¹ linie znaleziono nale¿y je usun¹æ z wektora fileTextLines_
		- w obu przypadkach nastepnie na koniec wektora dodaje siê informacje o graczu
		- plik jest zamykany
	*/

	std::ofstream file;
	file.open(filename, std::ios::out | std::ios::trunc);

	if (file.is_open())
	{
		int line_number = findNickname();
		std::cout << line_number << std::endl;

		if (line_number != -1)
		{
			std::cout << line_number << " line_number != -1, erase\n";
			this->fileTextLines_.erase(this->fileTextLines_.begin() + line_number);
		}

		this->fileTextLines_.push_back(this->playerNickname_ + " " + std::to_string(this->player_->getLevel()) + " " + std::to_string(this->player_->getCurrentExp()));

		for (auto line : fileTextLines_)
		{
			if (line[0] == ' ')
			{
				file << line.substr(1, line.size() - 1) << std::endl;
			}
			else
			{
				file << line << std::endl;
			}
			std::cout << " ping in saving: " << line << std::endl;
		}

		file.close();
		this->fileTextLines_.clear();
	}
	else {
		std::cerr << "Nie mo¿na otworzyæ pliku: " << filename << "\n";
	}
}

// Main loop
void Game::run()
{
	/*
		@returns void

		Runs the main game loop while the window is open.
		- main loop
			> event polling
			> updating the program's state
			> rendering to the window
	*/

	while (window_->isOpen())
	{
		this->updatePollEvents();
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	/*
		@returns void

		window event polling
		- updating mouse position
		- pausing and unpausing
		- exiting the level
		- entering player nickname
		- backspace
	*/

	this->mousePos_ = sf::Mouse::getPosition(*this->window_);

	while (this->window_->pollEvent(this->e))
	{
		// pauzowanie
		if (this->e.type == sf::Event::KeyReleased && this->e.key.code == sf::Keyboard::Escape && isMenu_==false)
		{
			if (pause_.isPaused()) {
				pause_.resume();
			}
			else {
				pause_.pause();
			}
		}
		
		if (this->pause_.isPaused()) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->pauseButton_->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
			{
				// Przejœcie do menu
				std::cout << "paused click\n";
				
				delete this->level_;
				this->isMenu_ = true;

				this->levelFromFile_ = this->player_->getLevel();
				this->expFromFile_ = this->player_->getCurrentExp();

				this->saveNickname("Nickname/wyniki.txt");

				pause_.resume();
			}
		}

		// wpisywanie nicku
		if (this->e.type == sf::Event::TextEntered && enteringNickname_ == true )
		{
			if (this->e.text.unicode < 128)
			{
				this->playerNickname_ += static_cast<char>(this->e.text.unicode);
				this->menuTexts_[2]->setString(this->playerNickname_);
			}		
		}

		// backspace
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) )
		{
			if (!this->playerNickname_.empty())
			{
				this->playerNickname_.pop_back();
				this->menuTexts_[2]->setString(this->playerNickname_);
			}
		}		
	}
}

// UPDATES

void Game::updateMenu()
{
	/*
		@returns void

		funkcja odpowiadaj¹ca za obs³ugê wciœniêtych przycisków
		- wybór poziomów 1, 2, 3
			> prze³¹cza isMenu = false
			> tworzy poziom przy u¿yciu danych z pliku tekstowego
		- wyjœcie
		- rozpoczêcia wpisywania nicku
		- wciœniêcie entera w trakcie pisania
			> sprawdzenie czy w pliku istnieje ju¿ taki gracz
			> stworzenia gracza o poziomie i doœwiadczeniu z pliku
		- backspace
	*/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->buttons_[0]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 1 
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level1.txt", this->fonts_[1]);
		}
		else if (this->buttons_[1]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 2
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level2.txt", this->fonts_[1]);
		}
		else if (this->buttons_[2]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 3
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level3.txt", this->fonts_[1]);
		}
		else if (this->buttons_[3]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// wyjscie
			this->window_->close();
		}
	
		else if (this->buttons_[4]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{	
			enteringNickname_ = true;
		}			 
	}

	// wczytywanie nicku
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->enteringNickname_)
	{
		this->playerNickname_.pop_back();

		std::cout << "Nick: " << this->playerNickname_ << "\n";

		this->inputFromFile("Nickname/wyniki.txt");

		delete this->player_;
		this->player_ = new Player(sf::Vector2f(this->window_->getSize().x / 2, this->window_->getSize().y / 2),
			textures_["PLAYER_SHEET"], textures_["PLAYER_IMMUNITY"], this->window_->getSize(), this->fonts_[1],
			this->levelFromFile_, this->expFromFile_);

		this->enteringNickname_ = false;	
	}

	//obsluga backspace
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && this->backspaceKeyReleased_)
	{
		if (!this->playerNickname_.empty())
		{
			this->playerNickname_.pop_back();
			this->menuTexts_[2]->setString(this->playerNickname_);
		}
		this->backspaceKeyReleased_ = false;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->backspaceKeyReleased_ = true;
	}

}

void Game::updateLevel()
{
	/*
		@returns void

		funkcja odpowiedzialna za aktualizowanie rozgrywki oraz jej zakoñczenie
		- wywo³anie Level::update() - aktualizacja rozgrywki
		- zakoñczenie rozgrywki - wygrana
			> sprawdzenie czy pokonano bossa
			> reset poziomu
			> powrót do menu
			> zapisanie postêpu
		- zakoñczenie rozgrywki - przegrana
			> sprawdzenie czy zdrowie gracza nie spad³o do 0
			> reset poziomu
			> powrót do menu
			> zapisanie postêpu
	*/

	// updating
	this->level_->update();

	// winning
	if (this->level_->bossDefeated())
	{
		delete this->level_;

		this->menuTexts_[0]->setString("Great win!");
		this->isMenu_ = true;

		this->levelFromFile_ = this->player_->getLevel();
		this->expFromFile_ = this->player_->getCurrentExp();

		this->saveNickname("Nickname/wyniki.txt");
	}

	// losing
	else if (this->level_->getPlayerHp() <= 0)
	{
		delete this->level_;

		this->menuTexts_[0]->setString("skill issue");
		this->isMenu_ = true;

		this->levelFromFile_ = this->player_->getLevel();
		this->expFromFile_ = this->player_->getCurrentExp();

		this->saveNickname("Nickname/wyniki.txt");
	}
}

void Game::update()
{
	/*
		@returns void

		funkcja odpowiedzialna za aktualizacje stanu programu w pêtli g³ównej Game::run()
		- je¿eli isMenu_==true aktualizuje menu
		- je¿eli isMenu_==false i rozgrywka nie jest zapauzowana aktualizuje stan poziomu
	*/

	if (this->isMenu_)
		this->updateMenu();
	else if (!this->pause_.isPaused())
		this->updateLevel();
}

// RENDERS

void Game::renderMenu()
{
	// renders all menu texts and buttons

	for (auto& btn : buttons_)
	{
		this->window_->draw(*btn);
	}
	for (auto& txt : menuTexts_)
	{
		this->window_->draw(*txt);
	}
}

void Game::render()
{
	/*
		@returns void
	
		funkcja odpowiedzialna za wyrysowywanie aktualnego stanu programu na ekranie
		- czyœci okno programu
		- wyrysowanie stanu programu w oknie
			> je¿eli isMenu_==true renderuje menu
			> je¿eli isMenu_==false renderuje poziom
			> je¿eli rozgrywka jest zapauzowana renderuje menu pauzy
		- wyœwietla wyrenderowan¹ klatkê na ekranie
	*/

	// Clearing
	this->window_->clear();

	// Drawing
	if (this->isMenu_)
		this->renderMenu();
	else
		this->level_->render();
	//pauza
	if (pause_.isPaused())
	{
		this->window_->draw(this->pauseText_);
		this->window_->draw(*this->pauseButton_);		
	}

	// Displaying
	this->window_->display();
}



