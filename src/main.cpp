#include "SFML/Graphics.hpp"
#include "Block.h"
#include "ActiveFigure.h"
#include "Game.h"



// Prędkość spadania klocka, większa wartość - wolniejsze spadanie
const float FALL_SPEED = 0.5f;

int main()
{
    srand(unsigned int(time(0)));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris Bieda Edition", sf::Style::Fullscreen);
    sf::Event event;
    sf::Clock clock;

    //Czcionka
    sf::Font open_sans;
    open_sans.loadFromFile("Dependencies\\Fonts\\static\\OpenSans\\OpenSans-Medium.ttf");

    // Zmienna przechowująca aktualnie spadającą figurę
    ActiveFigure activeFigure;

    // Wektor przechowujący klocki pozostające na planszy po opadnięciu
    std::vector<Block> fixedFigures;

    float currentTime = 0.0f;
    float previousTime = 0.0f;

    static int points = 0;



    while (window.isOpen())
    {
        // Obsługa naciśnięć klawiszy
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
        }

        // Aktualizacja stanu gry
        currentTime = clock.getElapsedTime().asSeconds();
        if (currentTime - previousTime > FALL_SPEED)
        {
            // Sprawdzamy, czy klocek może opaść o jedną pozycję
            if (activeFigure.canMove(0, 1, fixedFigures)) activeFigure.move(0, 1);
            else
            {
                //Zakończenie gry
                if (activeFigure.getY() == 0)
                {
                    clock.restart();
                    break;
                }
                // Jeśli klocek nie może opaść, dodajemy go do wektora  klocków pozostających na planszy
                for (Block& a : activeFigure.getBlocks())
                {
                    fixedFigures.emplace_back(activeFigure.getX() + a.getX(), activeFigure.getY() + a.getY(), a.getColor());
                }
                // Sprawdzamy, czy nie należy usunąć żadnych wierszy
                for (int i = 0; i < BOARD_HEIGHT; i++)
                {
                    bool fullRow = true;
                    for (int j = 0; j < BOARD_WIDTH; j++)
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
                        // Jeśli znaleziono pełny wiersz, usuwamy go i przesuwamy wszystkie klocki powyżej o jedną pozycję w dół
                        fixedFigures.erase(std::remove_if(fixedFigures.begin(), fixedFigures.end(), [&](Block& block) { return block.getY() == i; }), fixedFigures.end());
                        points++;

                        for (Block& block : fixedFigures)
                        {
                            if (block.getY() < i)
                                block.setY(block.getY() + 1);
                        }
                    }
                }

                // Tworzymy nowy spadający klocek
                activeFigure = ActiveFigure();
            }
            previousTime = currentTime;
        }

        // Rysowanie planszy gry
        window.clear();

        //Białe tło
        sf::RectangleShape whiteBackground(sf::Vector2f(BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE));
        whiteBackground.setPosition(CENTER, 0);
        whiteBackground.setFillColor(sf::Color::White);
        window.draw(whiteBackground);

        //Kolorowy bok
        sf::RectangleShape colorSide(sf::Vector2f(CENTER, WINDOW_HEIGHT));
        colorSide.setPosition(10 * BLOCK_SIZE + CENTER, 0);
        colorSide.setFillColor(sf::Color(153, 204, 255));
        window.draw(colorSide);
        colorSide.setPosition(0, 0);
        window.draw(colorSide);

        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            for (int j = 0; j < BOARD_HEIGHT; j++)
            {
                //Linie poziome
                sf::RectangleShape horizontalLines(sf::Vector2f(BLOCK_SIZE * BOARD_WIDTH, 1.0f));
                horizontalLines.setPosition(CENTER, float(j * BLOCK_SIZE));
                horizontalLines.setFillColor(sf::Color::Black);

                //Linie pionowe
                sf::RectangleShape verticalLines(sf::Vector2f(BLOCK_SIZE * BOARD_HEIGHT, 1.0f));
                verticalLines.rotate(90);
                verticalLines.setPosition(float(CENTER + (i * BLOCK_SIZE)), 0.0f);
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
        pointsNumber.setPosition(CENTER/2 - 50, (WINDOW_HEIGHT/2) - 100);
        pointsNumber.setCharacterSize(50);
        pointsNumber.setFillColor(sf::Color::Red);
        window.draw(pointsNumber);
        pointsNumber.setPosition((WINDOW_WIDTH)/2 + (BOARD_WIDTH*BLOCK_SIZE)/2 + 200, (WINDOW_HEIGHT / 2) - 100);
        window.draw(pointsNumber);

        // Rysowanie klocków pozostających na planszy
        for (Block block : fixedFigures)
        {
            sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            rectangle.setPosition(float(block.getX() * BLOCK_SIZE), float(block.getY() * BLOCK_SIZE));
            rectangle.setFillColor(block.getColor());
            window.draw(rectangle);
        }
        // Rysowanie aktualnie spadającego klocka
        for (Block block : activeFigure.getBlocks())
        {
            sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            rectangle.setPosition(float((activeFigure.getX() + block.getX())* BLOCK_SIZE), float((activeFigure.getY() + block.getY())* BLOCK_SIZE));
            rectangle.setFillColor(block.getColor());
            window.draw(rectangle);
        }

        

        window.display();
    }
    return 0;
}