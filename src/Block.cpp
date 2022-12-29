#include "Block.h"

Block::Block(int x, int y, sf::Color color)
	: m_x(x), m_y(y), color(color) {}

int Block::getX() const
{
	return m_x;
}

 int Block::getY() const
{
	return m_y;
}

 sf::Color Block::getColor() const
 {
	 return color;
 }

 void Block::setX(int x)
 {
	 m_x = x;
 }

 void Block::setY(int y)
 {
	 m_y = y;
 }
