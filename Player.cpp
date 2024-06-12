#include "Player.h"

///
/// INIT FUNCTIONS
///

void Player::initVariables()
{
    this->shotCooldown_ = sf::seconds(0.7f);
    this->immunityDuration_ = sf::seconds(1.2f);
    this->immunity_ = false;
    this->expForLevelup_ = 10;
}

void Player::initClocks()
{
    this->timeSinceLastShot_ = sf::Time::Zero;
    this->shotClock_.restart();

    this->timeSinceDamaged_ = sf::Time::Zero;
    this->immunityClock_.restart();
}

void Player::initGui()
{
    // healthbar
    this->healthbar_.setSize(sf::Vector2f(500.f, 30.f));
    this->healthbar_.setFillColor(sf::Color::Red);
    this->healthbar_.setPosition(sf::Vector2f(30.f, this->windowSize_.y - 45.f));

    this->healthbarBack_ = this->healthbar_;
    this->healthbarBack_.setFillColor(sf::Color(25, 25, 25, 200));

    // experience bar
    this->expBar_.setSize(sf::Vector2f(this->windowSize_.x - 60, 20.f));
    this->expBar_.setFillColor(sf::Color::Green);
    this->expBar_.setPosition(sf::Vector2f(sf::Vector2f(30.f, 30.f)));

    this->expBarBack_ = this->expBar_;
    this->expBarBack_.setFillColor(sf::Color(25, 25, 25, 200));

    this->levelText_.setFont(*this->font_);
    this->levelText_.setCharacterSize(12);
    this->levelText_.setString("Level " + std::to_string(level_) + "  \\\\  " + std::to_string(currentExperience_) + "/" + std::to_string(expForLevelup_));
    this->levelText_.setPosition(sf::Vector2f(this->windowSize_.x / 2 - this->levelText_.getGlobalBounds().width / 2, 35.f));
    this->levelText_.setFillColor(sf::Color::White);
}

///
/// CONSTRUCTORS AND DESTRUCTORS
/// 

Player::Player(sf::Vector2f position, sf::Texture* default_texture, sf::Texture* immunity_texture, sf::Vector2u window_size, sf::Font* font, int level, int exp)
    : Entity(position, default_texture, {0.6f, 0.6f}, 3.f, 5, 100), defaultTexture_(default_texture), 
      immunityTexture_(immunity_texture), windowSize_(window_size), font_(font), level_(level), currentExperience_(exp)
{
    /*
        @constructor

        - na liúcie inicjalizacyjnej
            > wywo≥uje konstruktor Entity i przekazuje mu odpowiednie argumenty
            > ustawia wskaüniki do textur
        - wywo≥uje funkcje init
    */

    std::cout << "new player\n";

	this->initVariables();
    this->initClocks();
    this->initGui();
    this->initialLevelUp();
}

Player::~Player()
{

}

///
/// GETTERS
///

const float Player::getTimeSinceLastShoot() const
{
    return timeSinceLastShot_.asSeconds();
}

const float Player::getShootCooldown() const
{
    return shotCooldown_.asSeconds();
}

///
/// SETTERS
///

void Player::damage(unsigned damage)
{
    /*
        @returns void

        if player doesnt have an immunity, damage is dealt and immunity is granted
        - checking if player has immunity
        - if not damage is dealt via Entity::damage(...)
        - immunity is turned on
        - timeSinceDamaged_ is reset
        - texture is changed
    */

    if (!immunity_)
    {
        this->Entity::damage(damage);

        this->immunity_ = true;
        this->timeSinceDamaged_ = sf::Time::Zero;
        this->setTexture(immunityTexture_);
    }
}

void Player::resetTimeSinceLastShot()
{
    this->timeSinceLastShot_ = sf::Time::Zero;
}

void Player::addExp(unsigned exp)
{
    this->currentExperience_ += exp;
    this->updateLevel();
}

void Player::initialLevelUp()
{
    for (int i = 1; i < level_; ++i)
    {
        this->expForLevelup_ *= 1.2;
        this->setMaxHp(this->getMaxHp() + 15);
        this->setCurrentHp(this->getHp() + 15);
        this->setDamage(this->getDamage() + 1);
        this->setSpeed(this->getSpeed() + 0.2f);
        this->shotCooldown_ *= 0.9f;
    }
}

///
/// FUNCTIONS
///

// Updating

void Player::updateImmunity()
{
    /*
        @returns void 

        funkcja liczy czas od ostatniego otrzymania obraøeÒ i wy≥πcza nietykalnoúÊ
        - inkrementacja timeSinceDamaged_
        - jeøeli wartoúÊ ta przekroczy Player::immunityDuration_
            > nietykalnoúÊ jest wy≥πczana
            > przywracana jest podstawowa tekstura gracza
    */

    this->timeSinceDamaged_ += this->immunityClock_.restart();

    if (this->timeSinceDamaged_ > this->immunityDuration_)
    {
        this->immunity_ = false;
        this->setTexture(defaultTexture_);
    }
}

void Player::moveWasd()
{
    // Move player up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->Entity::move(sf::Vector2f(0.f, -this->Entity::getSpeed()));
    }
    // Move player down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->Entity::move(sf::Vector2f(0.f, this->Entity::getSpeed()));
    }
    // Move player left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->Entity::move(sf::Vector2f(-this->Entity::getSpeed(), 0.f));
    }
    // Move player right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->Entity::move(sf::Vector2f(this->Entity::getSpeed(), 0.f));
    }
}

void Player::updateGui()
{
    // healthbar
    float hpPercent = static_cast<float>(this->getHp()) / this->getMaxHp();
    this->healthbar_.setSize(sf::Vector2f(hpPercent * this->healthbarBack_.getSize().x, this->healthbar_.getSize().y));

    // experience bar
    float expPercent = static_cast<float>(this->currentExperience_) / static_cast<float>(this->expForLevelup_);
    this->expBar_.setSize(sf::Vector2f(expPercent * this->expBarBack_.getSize().x, this->expBar_.getSize().y));

}

void Player::updateLevel()
{
    /*
        @returns void

        funckja wywo≥ywana przy zebraniu doúwiadczenia, sprawdza czy wystarczy≥o go do level-upu i podwyøsza poziom gracza oraz jego statystyki
    */

    this->levelText_.setString("Level " + std::to_string(level_) + "  \\\\  " + std::to_string(currentExperience_) + "/" + std::to_string(expForLevelup_));

    if (this->currentExperience_ >= this->expForLevelup_)
    {
        this->level_++;
        this->expForLevelup_ *= 1.2;
        this->currentExperience_ = 0;

        this->levelText_.setString("Level " + std::to_string(level_) + "  \\\\  " + std::to_string(currentExperience_) + "/" + std::to_string(expForLevelup_));

        // stat upgrades
        this->setMaxHp(this->getMaxHp() + 15);
        this->setCurrentHp(this->getHp() + 15);
        this->setDamage(this->getDamage() + 1);
        this->setSpeed(this->getSpeed() + 0.2f);
        this->shotCooldown_ *= 0.9f;
    }
}

void Player::update()
{
    this->timeSinceLastShot_ += this->shotClock_.restart();
    this->updateImmunity();
    this->moveWasd();
    this->updateGui();
}

// Rendering

void Player::renderGui(sf::RenderTarget& target)
{
    // healthbar
    target.draw(this->healthbarBack_);
    target.draw(this->healthbar_);

    // experience bar
    target.draw(this->expBarBack_);
    target.draw(this->expBar_);

    target.draw(this->levelText_);
}

