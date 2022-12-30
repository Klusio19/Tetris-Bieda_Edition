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

	//Inicjowanie wartoœci
	void initValues();

	//Obs³uga zdarzeñ (naciœniêæ przycisków na klawiaturze, przycisku "X" na oknie)
	void eventPolling();

	//Aktualizacja stanu gry
	void updateGameLogic();

	//Wyœwietlanie
	void render();

	//G³ówna pêtla otwartego okna
	void openWindow();

public:
	void run();
};