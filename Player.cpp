#include "Player.h"

///
/// INIT FUNCTIONS
///

void Player::initVariables()
{
    this->shotCooldown_ = sf::seconds(0.7f);
    this->immunityDuration_ = sf::seconds(2.f);
    this->immunity_ = false;
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
    this->healthbar_.setSize(sf::Vector2f(300.f, 25.f));
    this->healthbar_.setFillColor(sf::Color::Red);
    this->healthbar_.setPosition(sf::Vector2f(10.f, this->windowSize_.y - 35.f));

    this->healthbarBack_ = this->healthbar_;
    this->healthbarBack_.setFillColor(sf::Color(25, 25, 25, 200));
}

///
/// CONSTRUCTORS AND DESTRUCTORS
/// 

Player::Player(sf::Vector2f position, sf::Texture* default_texture, sf::Texture* immunity_texture, sf::Vector2u window_size)
    : Entity(position, default_texture, {0.6f, 0.6f}, 4.f, 5, 100), defaultTexture_(default_texture), immunityTexture_(immunity_texture), windowSize_(window_size)
{
    /*
        @constructor

        - na li�cie inicjalizacyjnej
            > wywo�uje konstruktor Entity i przekazuje mu odpowiednie argumenty
            > ustawia wska�niki do textur
        - wywo�uje funkcje init
    */

    std::cout << "new player\n";

	this->initVariables();
    this->initClocks();
    this->initGui();
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

///
/// FUNCTIONS
///

// Updating

void Player::updateImmunity()
{
    /*
        @returns void 

        funkcja liczy czas od ostatniego otrzymania obra�e� i wy��cza nietykalno��
        - inkrementacja timeSinceDamaged_
        - je�eli warto�� ta przekroczy Player::immunityDuration_
            > nietykalno�� jest wy��czana
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
}