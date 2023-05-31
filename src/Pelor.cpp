#include "D:\MakeFileTemplate-main\C++\_SFML\include\Pelor.h"

pelor::pelor()
{	
}

pelor::pelor(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*texture);

	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

pelor::~pelor()
{
}

const sf::FloatRect pelor::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void pelor::update()
{
	//Movement
	this->shape.move(this->movementSpeed * this->direction);
}

void pelor::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}
