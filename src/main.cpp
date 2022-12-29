#include <SFML/Graphics.hpp>
#include "Block.h"
#include "ActiveFigure.h"
#include <iostream>

// Wymiary pojedynczego klocka
const int BLOCK_SIZE = 40;

// Wymiary całego okna
const int WIDTH = BOARD_WIDTH * BLOCK_SIZE + 200;
// Wymiary całego okna
const int HEIGHT = BOARD_HEIGHT * BLOCK_SIZE;



// Prędkość spadania klocka, większa wartość - wolniejsze spadanie
const float FALL_SPEED = 0.5f;

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tetris Bieda Edition");

    float currentTime = 0.0f;
    float previousTime = 0.0f;

    // Zmienna przechowująca aktualnie spadający klocek
    ActiveFigure activeFigure;

    // Wektor przechowujący klocki pozostające na planszy po opadnięciu
    std::vector<Block> fixedFigures;

    //Czcionka
    sf::Font open_sans;
    //open_sans.loadFromFile("D:\\Dokumenty\\Projekty_Visual\\C++\\Tetris-Bieda_edition\\Dependencies\\Fonts\\static\\OpenSans\\OpenSans-Medium.ttf");
    open_sans.loadFromFile("Dependencies\\Fonts\\static\\OpenSans\\OpenSans-Medium.ttf");


    sf::Clock clock;
    static int points = 0;

    while (window.isOpen())
    {
        // Obsługa zdarzeń, naciśnięć klawiszy
        sf::Event event;
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

                if (event.key.code == sf::Keyboard::Q)
                {
                    //if (activeFigure.canMove(0, 0, fixedFigures)) 
                    activeFigure.rotateClockwise();
                }

                if (event.key.code == sf::Keyboard::E)
                {
                    //if (activeFigure.canMove(0, 0, fixedFigures)) 
                    activeFigure.rotateCounterclockwise();
                }

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

                    if (fullRow)
                    {
                        // Jeśli znaleziono pełny wiersz, usuwamy go i przesuwamy wszystkie klocki powyżej o jedną pozycję w dół
                        fixedFigures.erase(std::remove_if(fixedFigures.begin(), fixedFigures.end(), [&](Block& block) { return block.getY() == i; }), fixedFigures.end());
                        points++;

                        for (Block& block : fixedFigures)
                        {
                            if (block.getY() < i)
                                block.setY(block.getY() + 1); //TODO sprawdzić, zwiększenie m_y o jeden
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
        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            for (int j = 0; j < BOARD_HEIGHT; j++)
            {
                //Linie poziome
                sf::RectangleShape horizontalLines(sf::Vector2f(WIDTH, 1));
                horizontalLines.setPosition(0, j * BLOCK_SIZE);
                horizontalLines.setFillColor(sf::Color::Black);

                //Linie pionowe
                sf::RectangleShape verticalLines(sf::Vector2f(HEIGHT, 1));
                verticalLines.rotate(90);
                verticalLines.setPosition(i * BLOCK_SIZE, 0);
                verticalLines.setFillColor(sf::Color::Black);

                //Białe tło
                sf::RectangleShape whiteBackground(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                whiteBackground.setPosition(i * BLOCK_SIZE, j * BLOCK_SIZE);
                whiteBackground.setFillColor(sf::Color::White);

                //Kolorowy prawy bok
                sf::RectangleShape colorRightSide(sf::Vector2f(200, HEIGHT));
                colorRightSide.setPosition(400, 0);
                colorRightSide.setFillColor(sf::Color(153, 204, 255));

                window.draw(whiteBackground);
                window.draw(verticalLines);
                window.draw(horizontalLines);
                window.draw(colorRightSide);
            }
        }
        // Rysowanie klocków pozostających na planszy
        for (Block block : fixedFigures)
        {
            sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            rectangle.setPosition(block.getX() * BLOCK_SIZE, block.getY() * BLOCK_SIZE);
            rectangle.setFillColor(block.getColor());
            window.draw(rectangle);
        }
        // Rysowanie aktualnie spadającego klocka
        for (Block block : activeFigure.getBlocks())
        {
            sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            rectangle.setPosition((activeFigure.getX() + block.getX())* BLOCK_SIZE, (activeFigure.getY() + block.getY())* BLOCK_SIZE);
            rectangle.setFillColor(block.getColor());
            window.draw(rectangle);
        }

        //Rysowanie tekstu z punktami
        sf::Text pointsNumber;
        pointsNumber.setFont(open_sans);
        std::string s_points = "Punkty:\n     " + std::to_string(points);
        pointsNumber.setString(s_points);
        pointsNumber.setPosition(410, 350);
        pointsNumber.setCharacterSize(50);
        pointsNumber.setFillColor(sf::Color::Red);
        window.draw(pointsNumber);

        window.display();
    }

    return 0;
}