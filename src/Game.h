#pragma once
#include "globalValues.h"
#include "SFML/Graphics.hpp"
#include "Block.h"
#include "ActiveFigure.h"

class Game
{
private:
	sf::Font techno_font;
	sf::RenderWindow gameWindow;
	sf::Event event;
	sf::Clock clock;

	ActiveFigure activeFigure;
	Figure nextFigure;

	std::vector<Block> fixedFigures;

	float currentTime;
	float previousTime;

	int points = 0;

	// Inicjowanie warto�ci
	void initValues(int diffChoice);

	// Obs�uga zdarze� (naci�ni�� przycisk�w na klawiaturze, przycisku "X" na oknie)
	void eventPolling();

	// Aktualizacja stanu gry
	void updateGameLogic();

	// Wy�wietlanie
	void render();

	// G��wna p�tla otwartego okna
	void openWindow();

	// Otworzenie pierwszego okna z wyborem poziomu trudno��i
	void menuSetup();

	// Zako�czenie gry
	void endGame();

public:
	void run();
};