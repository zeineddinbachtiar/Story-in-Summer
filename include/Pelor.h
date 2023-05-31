#ifndef PELOR_H
#define PELOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

class pelor
{
private:

	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;

public:
	pelor();
	pelor(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~pelor();

	//Accessor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif // !PELOR_H