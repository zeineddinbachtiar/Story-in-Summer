#ifndef LONDO_H
#define LONDO_H

#include <iostream>
#include<SFML/Graphics.hpp>

class Londo
{
private:
	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	void initVariables();
	void initShape();

public:
	Londo(float pos_x, float pos_y);
	virtual ~Londo();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!LONDO_H