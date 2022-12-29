#pragma once
#include <vector>
#include "Block.h"

// Wymiary planszy do gry (w klockach)
const int BOARD_WIDTH = 10;
// Wymiary planszy do gry (w klockach)
const int BOARD_HEIGHT = 20;

// Wymiary pojedynczego klocka
const int BLOCK_SIZE = 54;

// Wymiary ca�ego okna
//const int WINDOW_WIDTH = (BOARD_WIDTH * BLOCK_SIZE + 200);
const int WINDOW_WIDTH = 1920;
// Wymiary ca�ego okna
//const int WINDOW_HEIGHT = (BOARD_HEIGHT * BLOCK_SIZE);
const int WINDOW_HEIGHT = 1080;

//Wsp�rz�dna X, dla kt�rej t�o(bia�y prostok�t) wyrysuje si� na �rodku ekranu.
//Niezale�na od rozmiaru okna oraz wielko�ci klocka.
const int CENTER = (WINDOW_WIDTH / 2) - (BOARD_WIDTH * BLOCK_SIZE / 2);

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