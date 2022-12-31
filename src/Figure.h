#pragma once
#include "Block.h"
#include "globalValues.h"

class Figure
{
private:
	sf::Color figureColor;
protected:
	std::vector<Block> m_blocks;
	int figureShape = -1;
	int m_x, m_y;
	
public:
	//Figure();
	void setFigurePosition(int x, int y);
	void initFigure();
	std::vector<Block> getFigureBlocks() const;
	int getX() const;
	int getY() const;
	int getShape();
	sf::Color getColor();
};