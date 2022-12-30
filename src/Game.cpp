#include "Game.h"

//Wymiary planszy do gry (w klockach)
float BOARD_WIDTH;
// Wymiary planszy do gry (w klockach)
float BOARD_HEIGHT;

// Wymiary pojedynczego klocka
float BLOCK_SIZE;

// Prêdkoœæ spadania klocka, wiêksza wartoœæ - wolniejsze spadanie
float FALL_SPEED;

// Wymiary ca³ego okna
float WINDOW_WIDTH;

// Wymiary ca³ego okna
float WINDOW_HEIGHT;

//Wspó³rzêdna X, dla której t³o(bia³y prostok¹t) wyrysuje siê na œrodku ekranu.
//Zale¿na od rozmiaru okna oraz wielkoœci klocka.
float CENTER;

void Game::initValues()
{
    BOARD_WIDTH = 10.0f;
    BOARD_HEIGHT = 20.0f;
    BLOCK_SIZE = 54.0f;
	FALL_SPEED = 0.5f;
	WINDOW_WIDTH = 1920.0f;
    WINDOW_HEIGHT = 1080.0f;

	CENTER = (WINDOW_WIDTH / 2) - (BOARD_WIDTH * BLOCK_SIZE / 2);
	open_sans.loadFromFile("Dependencies\\Fonts\\static\\OpenSans\\OpenSans-Medium.ttf");
	window.create(sf::VideoMode(unsigned int(WINDOW_WIDTH), unsigned int(WINDOW_HEIGHT)), "Tetris Bieda Edition", sf::Style::Fullscreen);
	currentTime = 0.0f;
	previousTime = 0.0f;
	points = 0;
	
}

void Game::eventPolling()
{
    // Obs³uga naciœniêæ klawiszy
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if (event.key.code == sf::Keyboard::Left)
            {
                if (activeFigure.canMove(-1, 0, fixedFigures)) activeFigure.move(-1, 0);
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                if (activeFigure.canMove(1, 0, fixedFigures)) activeFigure.move(1, 0);
            }
            if (event.key.code == sf::Keyboard::Down)
            {
                if (activeFigure.canMove(0, 1, fixedFigures)) activeFigure.move(0, 1);
            }
            if (event.key.code == sf::Keyboard::Q) activeFigure.rotateClockwise();
            if (event.key.code == sf::Keyboard::E) activeFigure.rotateCounterclockwise();
        }
    };
}

void Game::updateGameLogic()
{
    currentTime = clock.getElapsedTime().asSeconds();
    if (currentTime - previousTime > FALL_SPEED)
    {
        // Sprawdzamy, czy klocek mo¿e opaœæ o jedn¹ pozycjê
        if (activeFigure.canMove(0, 1, fixedFigures)) activeFigure.move(0, 1);
        else
        {
            //Zakoñczenie gry
            if (activeFigure.getY() == 0)
            {
                clock.restart();
            }
            // Jeœli klocek nie mo¿e opaœæ, dodajemy go do wektora  klocków pozostaj¹cych na planszy
            for (Block& a : activeFigure.getBlocks())
            {
                fixedFigures.emplace_back(activeFigure.getX() + a.getX(), activeFigure.getY() + a.getY(), a.getColor());
            }
            // Sprawdzamy, czy nie nale¿y usun¹æ ¿adnych wierszy
            for (int i = 0; i < BOARD_HEIGHT; i++)
            {
                bool fullRow = true;
                for (int j = 12; j < 12 + BOARD_WIDTH; j++)
                {
                    bool blockFound = false;
                    for (Block& b : fixedFigures)
                    {
                        if (b.getX() == j && b.getY() == i)
                        {
                            blockFound = true;
                            break;
                        }
                    }
                    if (blockFound == false)
                    {
                        fullRow = false;
                        break;
                    }
                }

                if (fullRow == true)
                {
                    // Jeœli znaleziono pe³ny wiersz, usuwamy go i przesuwamy wszystkie klocki powy¿ej o jedn¹ pozycjê w dó³
                    fixedFigures.erase(std::remove_if(fixedFigures.begin(), fixedFigures.end(), [&](Block& block) { return block.getY() == i; }), fixedFigures.end());
                    points++;

                    for (Block& block : fixedFigures)
                    {
                        if (block.getY() < i)
                            block.setY(block.getY() + 1);
                    }
                }
            }

            // Tworzymy nowy spadaj¹cy klocek
            activeFigure = ActiveFigure();
        }
        previousTime = currentTime;
    }
}

void Game::render()
{
    // Rysowanie planszy gry
    window.clear();

    //Bia³e t³o
    sf::RectangleShape whiteBackground(sf::Vector2f(BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE));
    whiteBackground.setPosition(12 * BLOCK_SIZE, 0);
    whiteBackground.setFillColor(sf::Color::White);
    window.draw(whiteBackground);

    //Kolorowe boki
    //lewy
    sf::RectangleShape colorSide(sf::Vector2f(12 * BLOCK_SIZE, WINDOW_HEIGHT));
    colorSide.setPosition(0,0);
    colorSide.setFillColor(sf::Color(153, 204, 255));
    window.draw(colorSide);
    //prawy
    colorSide.setSize(sf::Vector2f(14 * BLOCK_SIZE, WINDOW_HEIGHT));
    colorSide.setPosition(22 * BLOCK_SIZE, 0);
    window.draw(colorSide);

    for (int i = 0; i <= BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            //Linie poziome
            sf::RectangleShape horizontalLines(sf::Vector2f(BLOCK_SIZE * BOARD_WIDTH, 1.0f));
            horizontalLines.setPosition(12 * BLOCK_SIZE, float(j * BLOCK_SIZE));
            horizontalLines.setFillColor(sf::Color::Black);

            //Linie pionowe
            sf::RectangleShape verticalLines(sf::Vector2f(BLOCK_SIZE * BOARD_HEIGHT, 1.0f));
            verticalLines.rotate(90);
            verticalLines.setPosition((12 * BLOCK_SIZE) + BLOCK_SIZE * i, 0.0f);
            verticalLines.setFillColor(sf::Color::Black);

            window.draw(verticalLines);
            window.draw(horizontalLines);
        }
    }

    //Rysowanie tekstu z punktami
    sf::Text pointsNumber;
    pointsNumber.setFont(open_sans);
    std::string s_points = "Punkty:\n     " + std::to_string(points);
    pointsNumber.setString(s_points);
    pointsNumber.setPosition(CENTER / 2 - 50, (WINDOW_HEIGHT / 2) - 100);
    pointsNumber.setCharacterSize(50);
    pointsNumber.setFillColor(sf::Color::Red);
    window.draw(pointsNumber);
    pointsNumber.setPosition((WINDOW_WIDTH) / 2 + (BOARD_WIDTH * BLOCK_SIZE) / 2 + 200, (WINDOW_HEIGHT / 2) - 100);
    window.draw(pointsNumber);

    // Rysowanie klocków pozostaj¹cych na planszy
    for (Block block : fixedFigures)
    {
        sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        rectangle.setPosition(float(block.getX() * BLOCK_SIZE), float(block.getY() * BLOCK_SIZE));
        rectangle.setFillColor(block.getColor());
        window.draw(rectangle);
    }
    // Rysowanie aktualnie spadaj¹cego klocka
    for (Block block : activeFigure.getBlocks())
    {
        sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        rectangle.setPosition(float((activeFigure.getX() + block.getX()) * BLOCK_SIZE), float((activeFigure.getY() + block.getY()) * BLOCK_SIZE));
        rectangle.setFillColor(block.getColor());
        window.draw(rectangle);
    }

    window.display();
}


void Game::openWindow()
{
	while (window.isOpen())
	{
		eventPolling();
        updateGameLogic();
        render();
	}
}


void Game::run()
{
	initValues();
    openWindow();
}