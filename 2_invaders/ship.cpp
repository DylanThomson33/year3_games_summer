//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

//declaring static variables
bool Invader::direction;
float Invader::speed;
float Player::speed;

//controls
const Keyboard::Key controls[2] = {
    Keyboard::A,   // Player1 left
    Keyboard::D,   // Player1 right
};

//-----------------------------------------

//blank ship constructor
Ship::Ship() {};

//constructor
Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;

	setTexture(spritesheet);
	setTextureRect(_sprite);
};

//ship update
void Ship::Update(const float& dt) {}

//explode
void Ship::Explode() {
    setTextureRect(IntRect(128, 32, 32, 32));
    _exploded = true;
}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;


//-------------------------------------------------------------------------------


//blank invader constructor
Invader::Invader() : Ship() {}

//invader constructor
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

//update
void Invader::Update(const float& dt) {
	Ship::Update(dt);

    //getting direction
    move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

    if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) 
    {
        direction = !direction;

        for (int i = 0; i < (ships.size() - 1); ++i) {
            ships[i]->move(0, 24);
        }
    }

}


//-------------------------------------------------------------


//player constructor
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
    setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

//player update
void Player::Update(const float& dt) {
    Ship::Update(dt);

    //Move left
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }

    //Move Right
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }

    //checking if fired
    if (Keyboard::isKeyPressed(Keyboard::W)) 
    {
        //if key is pressed, then bullet it fired
        Bullet::Fire(Player::getPosition(), true);
    }
    Player::move(direction * speed * dt, 0);

    //setting limits
    if (getPosition().x > gameWidth - 16)
    {
        setPosition(gameWidth - 16, gameHeight - 32.0f);
    }

    if (getPosition().x < 16)
    {
        setPosition(16, gameHeight - 32.0f);
    }
}