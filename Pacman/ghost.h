//player.h
#pragma once
#include "enitity.h";

class Ghost : public Entity {
private:
	float _speed;

public:
	void Update(double dt) override;
	Ghost();
	void Render(sf::RenderWindow& window) const override;

	void SetColour(sf::Color c) { _shape->setFillColor(c); }

};
