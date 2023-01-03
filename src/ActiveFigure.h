#pragma once
#include "globalValues.h"
#include "Figure.h"
class ActiveFigure : public Figure
{
private:
	int activeFigureShape;
public:

	//Konstruktor tworz¹cy losow¹ figurê
	ActiveFigure(int difLevel = 2, int setShape = rand() % 7, sf::Color setColor = sf::Color(rand() % 256, rand() % 256, rand() % 256));

	std::vector<Block> getBlocks() const;

	// Funkcja sprawdzaj¹ca czy mo¿na obróciæ figurê o 90° zgodnie ze wskazówkami zegara
	bool canRotateClockwise(const std::vector<Block>& fixedFigures);

	// Funkcja obracaj¹ca figurê o 90° zgodnie ze wskazówkami zegara
	// Ka¿dy punkt (x,y) staje siê punktem (y, -x)
	void rotateClockwise();

	// Funkcja sprawdzaj¹ca czy mo¿na obróciæ figurê o 90° przeciwnie do ruchu wskazówek zegara
	bool canRotateCounterclockwise(const std::vector<Block>& fixedFigures);

	// Funkcja obracaj¹ca figurê o 90° przeciwnie do ruchu wskazówek zegara
	// Ka¿dy punkt (x,y) staje siê punktem (-y, x)
	void rotateCounterclockwise();

	// Funkcja sprawdzaj¹ca, czy figura mo¿e byæ przesuniêty w danym kierunku
	bool canMove(int x, int y, const std::vector<Block>& fixedFigures);

	// Funkcja przesuwaj¹ca figurê o podan¹ liczbê pozycji w danym kierunku
	void move(int x, int y);

	

};