#include "D:\MakeFileTemplate-main\C++\_SFML\include\Londo.h"


void Londo::initVariables()
{
	this->pointCount = rand() % 8 + 3; 
	this->type		= 0;
	this->speed		= static_cast<float>(this->pointCount/3);
	this->hpMax		= static_cast<int>(this->pointCount);
	this->hp		= this->hpMax;
	this->damage	= this->pointCount;
}

void Londo::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Londo::Londo(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Londo::~Londo()
{
}

//Accessors
const sf::FloatRect Londo::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int & Londo::getDamage() const
{
	return this->damage;
}

//Functions
void Londo::update()
{
	this->shape.move(0.f, this->speed);
}

void Londo::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}
