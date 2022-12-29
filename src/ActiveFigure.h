#pragma once
#include <vector>
#include "Block.h"

// Wymiary planszy do gry (w klockach)
const int BOARD_WIDTH = 10;
// Wymiary planszy do gry (w klockach)
const int BOARD_HEIGHT = 20;

class ActiveFigure
{
private:
	std::vector<Block> m_blocks;
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