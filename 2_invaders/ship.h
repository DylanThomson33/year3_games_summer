//ship.h
#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {

public:
    //Constructor that takes a sprite
    explicit Ship(sf::IntRect ir);
    //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
    virtual ~Ship() = 0;
    //Update, virtual so can be overridden, but not pure virtual
    virtual void Update(const float& dt);

    //getter
    bool is_exploded() const { return _exploded; }
    virtual void Explode();

protected:
    bool _exploded = false;
    sf::IntRect _sprite;
    //Default constructor is hidden
    Ship();
};

class Invader : public Ship {

public:
    static bool direction;
    static float speed;
    Invader(sf::IntRect ir, sf::Vector2f pos);
    Invader();
    void Update(const float& dt) override;
};

class Player : public Ship {

public:
    static float speed;
    Player();
    void Update(const float& dt) override;
};