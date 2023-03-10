#pragma once
#include "globalValues.h"
#include "Figure.h"
class ActiveFigure : public Figure
{
private:
	int activeFigureShape;
public:

	//Konstruktor tworz?cy losow? figur?
	ActiveFigure(int setShape = rand() % 7, sf::Color setColor = sf::Color(rand() % 256, rand() % 256, rand() % 256));

	std::vector<Block> getBlocks() const;

	// Funkcja sprawdzaj?ca czy mo?na obr?ci? figur? o 90? zgodnie ze wskaz?wkami zegara
	bool canRotateClockwise(const std::vector<Block>& fixedFigures);

	// Funkcja obracaj?ca figur? o 90? zgodnie ze wskaz?wkami zegara
	// Ka?dy punkt (x,y) staje si? punktem (y, -x)
	void rotateClockwise();

	// Funkcja sprawdzaj?ca czy mo?na obr?ci? figur? o 90? przeciwnie do ruchu wskaz?wek zegara
	bool canRotateCounterclockwise(const std::vector<Block>& fixedFigures);

	// Funkcja obracaj?ca figur? o 90? przeciwnie do ruchu wskaz?wek zegara
	// Ka?dy punkt (x,y) staje si? punktem (-y, x)
	void rotateCounterclockwise();

	// Funkcja sprawdzaj?ca, czy figura mo?e by? przesuni?ty w danym kierunku
	bool canMove(int x, int y, const std::vector<Block>& fixedFigures);

	// Funkcja przesuwaj?ca figur? o podan? liczb? pozycji w danym kierunku
	void move(int x, int y);

	

};