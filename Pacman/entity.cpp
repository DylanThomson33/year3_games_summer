//entity.cpp
#include "enitity.h";

using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position; }

void Entity::setPosition(const Vector2f& pos) { _position = pos; }

void Entity::move(const Vector2f& pos) { _position += pos; }

void Entity::Update(const double dt) {
    _shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

void EntityManager::update(const double dt)
{
    for (std::shared_ptr<Entity> &e : list)
    {
        e->Update(dt);
    } 
}

void EntityManager::render(sf::RenderWindow& window)
{
    for (std::shared_ptr<Entity> &e : list)
    {
        e->Render(window);
    }
}