#pragma once
#include "globalValues.h"
#include "SFML/Graphics.hpp"
#include "Block.h"
#include "ActiveFigure.h"

class Game
{
private:

	sf::Font open_sans;
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;

	ActiveFigure activeFigure;

	std::vector<Block> fixedFigures;

	float currentTime;
	float previousTime;

	int points;

	//Inicjowanie warto�ci
	void initValues();

	//Obs�uga zdarze� (naci�ni�� przycisk�w na klawiaturze, przycisku "X" na oknie)
	void eventPolling();

	//Aktualizacja stanu gry
	void updateGameLogic();

	//Wy�wietlanie
	void render();

	//G��wna p�tla otwartego okna
	void openWindow();

public:
	void run();
};