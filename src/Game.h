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

	// Inicjowanie wartoœci
	void initValues(int diffChoice);

	// Obs³uga zdarzeñ (naciœniêæ przycisków na klawiaturze, przycisku "X" na oknie)
	void eventPolling();

	// Aktualizacja stanu gry
	void updateGameLogic();

	// Wyœwietlanie
	void render();

	// G³ówna pêtla otwartego okna
	void openWindow();

	// Otworzenie pierwszego okna z wyborem poziomu trudnoœæi
	void menuSetup();

	// Zakoñczenie gry
	void endGame();

public:
	void run();
};