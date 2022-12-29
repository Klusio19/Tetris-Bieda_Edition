#pragma once
#include "SFML/Graphics.hpp"

class Block
{
private:
	int m_x, m_y;
	sf::Color color;
public:
	Block(int x, int y, sf::Color color);
	int getX() const;
	int getY() const;
	sf::Color getColor() const;
	void setX(int x);
	void setY(int y);
};

