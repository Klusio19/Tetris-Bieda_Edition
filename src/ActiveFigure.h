#pragma once
#include "globalValues.h"
//#include "Game.h"
#include <vector>
#include "Block.h"


class ActiveFigure
{
private:
	std::vector<Block> m_blocks;

	//Pozycja klocka (w d³ugoœci bloczków)
	int m_x, m_y;
	int shape = -1;
public:
	ActiveFigure();
	std::vector<Block> getBlocks() const;
	int getX() const;
	int getY() const;
	void rotateClockwise();
	void rotateCounterclockwise();
	bool canMove(int x, int y, const std::vector<Block>& fixedFigures);
	void move(int x, int y);
};