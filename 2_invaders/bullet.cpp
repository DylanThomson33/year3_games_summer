//bullet.cpp
#include "bullet.h"
#include "game.h"
#include "ship.h"
using namespace sf;
using namespace std;

//constructor
Bullet::Bullet(const sf::Vector2f& pos, const bool mode)
{
    setPosition(pos);
    _mode = mode;
    setTexture(spritesheet);
    setTextureRect(IntRect(64, 32, 32, 32));
};

//Non static update function
void Bullet::Update(const float & dt) 
{
    for (Bullet b : bullets)
    {
        b.move(0.0f, dt * 200.0f * (b._mode ? 1.0f : -1.0f));
    }
};

void Bullet::Render(sf::RenderWindow &window)
{
    for (Bullet b : bullets)
    {
        window.draw(b);
    }
};

//chose an inactive bullet and use it
void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{
    bullets[++bulletPointer].setPosition(pos);
    bullets[bulletPointer]._mode = mode;
};

void Bullet::_Update(const float& dt) {
    //if position isn't on the y axis of the screen
    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        //off screen - do nothing
        return;
    }
    else {
        //update the bullets position
        move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
        const FloatRect boundingBox = getGlobalBounds();
        //for all ships including player 
        for (auto s : ships) 
        {
            //if mode is false(player) and current ship is player
            if (!_mode && s == ships.back()) {
                //player bullets don't collide with player
                continue;
            }
            //if bullet is from invader and current ship isn't player
            if (_mode && s != ships.back()) {
                //invader bullets don't collide with other invaders
                continue;
            }
            //if current ship hasn't exploded yet and has been hit by a bullet
            if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) 
            {
                //Explode the ship
                s->Explode();
                //warp bullet off-screen
                setPosition(-100, -100);
                return;
            }
        }
    }
};

