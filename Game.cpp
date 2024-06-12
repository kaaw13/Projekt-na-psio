#include "Game.h"

///
/// INIT FUNCTIONS
/// 

void Game::initWindow()
{
	//this->window_ = new sf::RenderWindow(sf::VideoMode(1920, 1080), "nazwa", sf::Style::Fullscreen);	// okno docelowe
	this->window_ = new sf::RenderWindow(sf::VideoMode(1200, 900), "nazwa", sf::Style::Close);			// okienko tymczasowe do wygodniejszego testowania
	this->window_->setFramerateLimit(144);
	this->window_->setVerticalSyncEnabled(false);
	std::cout << "initWindow\n";
}

void Game::initPlayer()
{
	this->player_ = new Player(sf::Vector2f(this->window_->getSize().x / 2, this->window_->getSize().y / 2),
		textures_["PLAYER_SHEET"], textures_["PLAYER_IMMUNITY"], this->window_->getSize());
}

void Game::initTextures()
{
	/*
		@returns void

		wczytuje wszystkie textury i dodaje je do wektora textures_
		- playerSheet
		- enemySheet
	*/

	this->textures_["PLAYER_SHEET"] = new sf::Texture;
	if (!this->textures_["PLAYER_SHEET"]->loadFromFile("Textures/playerSheet.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load playerSheet.png\n";
	}

	this->textures_["ENEMY_1"] = new sf::Texture;
	if (!this->textures_["ENEMY_1"]->loadFromFile("Textures/enemy1.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load enemy1.png\n";
	}

	this->textures_["BACKGROUND_1"] = new sf::Texture;
	if (!this->textures_["BACKGROUND_1"]->loadFromFile("Textures/background1.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load background1.png\n";
	}

	this->textures_["BULLET"] = new sf::Texture;
	if (!this->textures_["BULLET"]->loadFromFile("Textures/bullet.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load bullet.png\n";
	}

	this->textures_["PLAYER_IMMUNITY"] = new sf::Texture;
	if (!this->textures_["PLAYER_IMMUNITY"]->loadFromFile("Textures/playerImmunity.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load playerImmunity.png\n";
	}

	this->textures_["BOSS_1"] = new sf::Texture;
	if (!this->textures_["BOSS_1"]->loadFromFile("Textures/boss1.png"))
	{
		std::cout << "GAME::INITTEXTURES::Failed to load boss1.png\n";
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
	this->fonts_.push_back(new sf::Font);	
	if (!this->fonts_[0]->loadFromFile("Fonts/ARCADECLASSIC.ttf"))
	{
		std::cout << "GAME::INITFONTS::Failed to load ARCADECLASSIC.ttf\n";
	}

	this->menuTexts_.push_back(new sf::Text("Balls of death", *this->fonts_[0], 44));
	this->menuTexts_[0]->setFillColor(sf::Color::White);
	this->menuTexts_[0]->setPosition(sf::Vector2f(50.f, 10.f));
	this->menuTexts_.push_back(new sf::Text("Enter your nick:", *this->fonts_[0], 44));
	this->menuTexts_[1]->setFillColor(sf::Color::White);
	this->menuTexts_[1]->setPosition(sf::Vector2f(50.f, 50.f));
	this->menuTexts_.push_back(new sf::Text("", *this->fonts_[0], 44));
	this->menuTexts_[2]->setFillColor(sf::Color::White);
	this->menuTexts_[2]->setPosition(sf::Vector2f(500.f, 50.f));
	this->menuTexts_.push_back(new sf::Text("Level 1", *this->fonts_[0], 44));
	this->menuTexts_[3]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[3]->setPosition(sf::Vector2f(150.f, 250.f));
	this->menuTexts_.push_back(new sf::Text("Level 2", *this->fonts_[0], 44));
	this->menuTexts_[4]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[4]->setPosition(sf::Vector2f(350.f, 250.f));
	this->menuTexts_.push_back(new sf::Text("Level 3", *this->fonts_[0], 44));
	this->menuTexts_[5]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[5]->setPosition(sf::Vector2f(550.f, 250.f));
	this->menuTexts_.push_back(new sf::Text("Exit", *this->fonts_[0], 44));
	this->menuTexts_[6]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[6]->setPosition(sf::Vector2f(150.f, 450.f));
	this->menuTexts_.push_back(new sf::Text("Wyniki", *this->fonts_[0], 44));
	this->menuTexts_[7]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[7]->setPosition(sf::Vector2f(350.f, 450.f));
	this->menuTexts_.push_back(new sf::Text("Twój nick", *this->fonts_[0], 44));
	this->menuTexts_[8]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[8]->setPosition(sf::Vector2f(550.f, 450.f));
	this->menuTexts_.push_back(new sf::Text("", *this->fonts_[0], 44));
	this->menuTexts_[9]->setFillColor(sf::Color::Magenta);
	this->menuTexts_[9]->setPosition(sf::Vector2f(750.f, 450.f));
	
}


void Game::initButtons()
{
	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[0]->setPosition(sf::Vector2f(100.f, 200.f));
	this->buttons_[0]->setFillColor(sf::Color::White);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[1]->setPosition(sf::Vector2f(300.f, 200.f));
	this->buttons_[1]->setFillColor(sf::Color::White);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[2]->setPosition(sf::Vector2f(500.f, 200.f));
	this->buttons_[2]->setFillColor(sf::Color::White);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[3]->setPosition(sf::Vector2f(100.f, 400.f));
	this->buttons_[3]->setFillColor(sf::Color::Blue);

	this->buttons_.push_back(new sf::RectangleShape(sf::Vector2f(100.f, 100.f)));
	this->buttons_[4]->setPosition(sf::Vector2f(300.f, 400.f));
	this->buttons_[4]->setFillColor(sf::Color::Yellow);

	
}

void Game::initpauseMenu()
{
	sf::Text pauseText;
	pauseText.setFont(*this->fonts_[0]);
	pauseText.setString("Pauza");
	pauseText.setCharacterSize(72);
	pauseText.setFillColor(sf::Color::Red);
	pauseText.setPosition(this->window_->getSize().x / 2 - pauseText.getGlobalBounds().width / 2,
		this->window_->getSize().y / 2 - pauseText.getGlobalBounds().height / 2);
	this->window_->draw(pauseText);
	this->menuButton_ = new sf::RectangleShape(sf::Vector2f(200.f, 50.f));
	this->menuButton_->setPosition(sf::Vector2f(this->window_->getSize().x / 2 - 100.f, this->window_->getSize().y / 2 + 100.f));
	this->menuButton_->setFillColor(sf::Color::Green);
	
	
	
}
void Game::initMenu()
{
	/*
		@returns void

		initialises the menu
		- sets isMenu_ flag to true
		- creates menu text
		- creates buttons
	*/

	this->isMenu_ = true;
	this->initText();
	this->initButtons();
	
	
}

//zapisywanie nicku
void Game::saveNickname(const std::string& filename, const std::string& nick, int wynik)
{
	std::ofstream file;
	file.open(filename, std::ios::app);

	if (file.is_open()) {
		file << nick << " " << wynik << "\n";
		file.close();
		std::cout << "Zapisano do pliku tekstowego.\n";
	}
	else {
		std::cerr << "Nie mo¿na otworzyæ pliku: " << filename << "\n";
		perror("B³¹d");
	}
}

int Game::findNickname(const std::string& filename, const std::string& nick) {
	std::ifstream file(filename);
	std::string line;
	bool found = false;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			size_t spacePos = line.find(' ');
			currentNickname_ = line.substr(0, spacePos);
			try {
				playerScore_ = std::stoi(line.substr(spacePos + 1));
			}
			catch (const std::invalid_argument& e) {
				// Obs³uga wyj¹tku std::invalid_argument
				std::cerr << "Nieprawid³owy format liczby: " << e.what() << std::endl;
				playerScore_ = 0; // Ustawienie wartoœci domyœlnej
			}

			if (currentNickname_ == nick) {
				std::cout << "Znaleziono nick: " << nick << "\n";
				found = true;
				return 1;
			}
		}
		file.close();
		if (!found) {
			std::cout << "Gracz o nicku " << nick << " nie znaleziony.\n";
			return 0;
		}
	}
	else {
		std::cerr << "Nie mo¿na otworzyæ pliku.\n";
	}

	return -1; // Dodane dla pe³noœci, aby upewniæ siê, ¿e funkcja zawsze zwraca wartoœæ
}




///
/// CONSTRUCTORS AND DESTRUCTORS
///

Game::Game()
{
	// calls all init-Functions
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initMenu();
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
	delete this->menuButton_;
	delete this->window_;
}

///
/// FUNCTIONS
///

// Main loop
void Game::run()
{
	/*
		@returns void

		Runs the main game loop while the window is open.
		- main loop
		- updating
		- rendering
	*/

	while (window_->isOpen())
	{
		this->updatePollEvents();

		if (!pause_.isPaused()) {
			this->update();
		}

		this->render();
		//this->enterNickname();
	}
}


void Game::updatePollEvents()
{
	/*
		@returns void

		Checks all events in the poll
		- closing via escape key
	*/

	while (this->window_->pollEvent(this->e))
	{
		//powracanie do menu
		if (this->e.type == sf::Event::KeyPressed && this->e.key.code == sf::Keyboard::Escape && isMenu_==false)
		{
			if (pause_.isPaused()) {
				pause_.resume();
			}
			else {
				pause_.pause();
			}
		}
		if (this->e.type == sf::Event::TextEntered && enteringNickname_ == true )
		{
			if (this->e.text.unicode < 128)
			{
				this->text_ += static_cast<char>(this->e.text.unicode);
				this->menuTexts_[2]->setString(this->text_);
			}
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) )
		{
			if (!this->text_.empty())
			{
				this->text_.pop_back();
				this->menuTexts_[2]->setString(this->text_);
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (this->menuButton_ != nullptr && this->menuButton_->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
			{
				if (this->menuButton_->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
				{
					// Przejœcie do menu
					this->isMenu_ = true;
					pause_.resume();
				}
			}
		}
		
		
	}
}

// UPDATES

void Game::updateMenu()
{
	/*
		@returns void

		funkcja odpowiadaj¹ca za wybór poziomu
		- sprawdza czy wciœniêto lewy przycisk myszy
		- sprawdza czy klikniêto na przycisk 
		- wy³¹cza menu ustawiaj¹c isMenu_ na false
		- wywo³uje odpowiedni poziom
	*/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->buttons_[0]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 1 
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level1.txt");
		}
		else if (this->buttons_[1]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 2
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level2.txt");
		}
		else if (this->buttons_[2]->getGlobalBounds().contains(this->mousePos_.x, this->mousePos_.y))
		{
			// poziom 3
			this->isMenu_ = false;
			this->level_ = new Level(this->player_, this->window_, &this->textures_, "Level/Level3.txt");
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
	//wczytywanie nicku

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		this->playerNickname_ = text_;
		this->menuTexts_[2]->setString(this->playerNickname_);
		int wyniki = 0;
		switch (this->findNickname("Nickname/wyniki.txt", this->playerNickname_))
		{
		case 0: // Nick nie zosta³ znaleziony
			this->saveNickname("Nickname/wyniki.txt", this->playerNickname_, wyniki);
			break;
		case 1: // Nick zosta³ znaleziony
			this->findNickname("Nickname/wyniki.txt", this->playerNickname_);
			break;
		default:

			break;
		}
		this->menuTexts_[9]->setString(this->playerNickname_ + " " + std::to_string(playerScore_));
		this->enteringNickname_ = false;
		
	}
	//obsluga backspace
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && this->backspaceKeyReleased_)
	{
		if (!this->text_.empty())
		{
			this->text_.pop_back();
			this->menuTexts_[2]->setString(this->text_);
		}
		this->backspaceKeyReleased_ = false;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->backspaceKeyReleased_ = true;
	}
	//obsluga enter

	
	
	
	

}

void Game::updateLevel()
{
	/*
		@returns void

		funkcja odpowiedzialna za aktualizowanie rozgrywki oraz jej zakoñczenie
		- wywo³anie Level::update() - aktualizacja rozgrywki
		- zakoñczenie rozgrywki - wygrana
			> dzieje siê po zabiciu wszystkich przeciwników
			> reset poziomu
			> prze³¹czenie Game::update() i Game::render() na menu
		- zakoñczenie rozgrywki - przegrana
			> dzieje siê gdy zdrowie gracza spadnie do 0
			> reset poziomu
			> reset gracza
			> prze³¹czenie Game::update() i Game::render() na menu
	*/

	// updating
	this->level_->update();

	// winning
	if (this->level_->bossDefeated())
	{
		delete this->level_;

		this->menuTexts_[0]->setString("Great win!");
		this->isMenu_ = true;
	}

	// losing
	else if (this->level_->getPlayerHp() <= 0)
	{
		delete this->level_;
		delete this->player_;
		this->initPlayer();

		this->menuTexts_[0]->setString("skill issue");
		this->isMenu_ = true;
	}
}

void Game::update()
{
	/*
		@returns void

		funkcja odpowiedzialna za aktualizacje stanu programu w pêtli g³ównej Game::run()
		- zapisuje bie¿¹c¹ pozycjê myszy
		- na podstawie flagi Game::isMenu_ wywo³uje
			> true   ->  updateMenu() 
			> false  ->  updateLevel()
	*/

	this->mousePos_ = sf::Mouse::getPosition(*this->window_);

	if (this->isMenu_)
		this->updateMenu();
	else
		this->updateLevel();
}

// RENDERS

void Game::renderMenu()
{
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
		- na podstawie flagi Game::isMenu_ wyrysowuje klatkê na oknie Game::window_, wywo³uj¹c
			> true   ->  renderMenu() 
			> false  ->  renderLevel()
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
		
		this->initpauseMenu();
		this->window_->draw(*this->menuButton_);
		
	}

	// Displaying
	this->window_->display();
}



