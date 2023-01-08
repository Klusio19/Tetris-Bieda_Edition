#include "Game.h"
#include "Font.h"

//Wymiary planszy do gry (w klockach)
const float BOARD_WIDTH = 10.0f;
// Wymiary planszy do gry (w klockach)
const float BOARD_HEIGHT = 20.0f;

// Wymiary pojedynczego klocka
const float BLOCK_SIZE = 54.0f;

// Prêdkoœæ spadania klocka, wiêksza wartoœæ - wolniejsze spadanie
float FALL_SPEED;

// Wymiary ca³ego okna
const float WINDOW_WIDTH = 1980.0f;

// Wymiary ca³ego okna
const float WINDOW_HEIGHT = 1080.0f;

//Wspó³rzêdna X, dla której t³o(bia³y prostok¹t) wyrysuje siê na œrodku ekranu.
//Zale¿na od rozmiaru okna oraz wielkoœci klocka.
float CENTER;

int difficultyChoice = 0;

void Game::run()
{
    displayControls();
    menuSetup();
    initValues(difficultyChoice);
    openWindow();
}

void Game::initValues(int diffChoice)
{
    switch (diffChoice)
    {
        case 1:
        {
            FALL_SPEED = 0.5f;
            break;
        }
        
        case 2:
        {
            FALL_SPEED = 0.3f;
            break;
        }
        
        case 3:
        {
            FALL_SPEED = 0.1f;
            break;
        }
    }

    CENTER = (WINDOW_WIDTH / 2) - (BOARD_WIDTH * BLOCK_SIZE / 2);

    gameWindow.create(sf::VideoMode(unsigned int(WINDOW_WIDTH), unsigned int(WINDOW_HEIGHT)), "Tetris Bieda Edition", sf::Style::Fullscreen);
    currentTime = 0.0f;
    previousTime = 0.0f;
    points = 0;
    nextFigure.initFigure();
}

void Game::eventPolling()
{
    // Obs³uga naciœniêæ klawiszy
    while (gameWindow.pollEvent(mainWindowEvent))
    {
        if (mainWindowEvent.type == sf::Event::Closed) gameWindow.close();
        if (mainWindowEvent.type == sf::Event::KeyPressed)
        {
            if (mainWindowEvent.key.code == sf::Keyboard::Escape)
            {
                gameWindow.close();
            }
            if (mainWindowEvent.key.code == sf::Keyboard::Left)
            {
                if (activeFigure.canMove(-1, 0, fixedFigures)) activeFigure.move(-1, 0);
            }
            if (mainWindowEvent.key.code == sf::Keyboard::Right)
            {
                if (activeFigure.canMove(1, 0, fixedFigures)) activeFigure.move(1, 0);
            }
            if (mainWindowEvent.key.code == sf::Keyboard::Down)
            {
                if (activeFigure.canMove(0, 1, fixedFigures)) activeFigure.move(0, 1);
            }
            if (mainWindowEvent.key.code == sf::Keyboard::Q)
            {
                if (difficultyChoice == 3) return;
                if (activeFigure.canRotateClockwise(fixedFigures)) activeFigure.rotateClockwise();
            }
            if (mainWindowEvent.key.code == sf::Keyboard::E)
            {
                if (difficultyChoice == 3) return;
                if (activeFigure.canRotateCounterclockwise(fixedFigures)) activeFigure.rotateCounterclockwise();
            }
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
                Game::endGame();
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

            
            // Tworzymy nowy spadaj¹cy klocek, oraz klocek kolejny
            
            //nextFigure.setFigurePosition(24, 4);
            activeFigure = ActiveFigure(difficultyChoice, nextFigure.getShape(), nextFigure.getColor());
            nextFigure.initFigure();
            if (difficultyChoice == 3)
            {
                int rotateChance = -1;
                rotateChance = rand() % 3;
                if (rotateChance == 1) activeFigure.rotateClockwise();
                if (rotateChance == 2) activeFigure.rotateCounterclockwise();
            }
        }
        previousTime = currentTime;
    }
}

void Game::render()
{
    gameWindow.clear();

    // Rysowanie ca³ego t³a
    sf::RectangleShape backgroundRectangle(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundRectangle.setPosition(0, 0);
    backgroundRectangle.setFillColor(sf::Color(153, 204, 255));
    gameWindow.draw(backgroundRectangle);


    // Rysowanie bia³ego t³a, planszy do gry
    sf::RectangleShape whiteBackgroundBoard(sf::Vector2f(BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE));
    whiteBackgroundBoard.setPosition(12 * BLOCK_SIZE, 0);
    whiteBackgroundBoard.setFillColor(sf::Color::White);
    gameWindow.draw(whiteBackgroundBoard);

    // Rysowanie linii
    for (int i = 0; i <= BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            // Linie poziome
            sf::RectangleShape horizontalLines(sf::Vector2f(BLOCK_SIZE * BOARD_WIDTH, 1.0f));
            horizontalLines.setPosition(12 * BLOCK_SIZE, float(j * BLOCK_SIZE));
            horizontalLines.setFillColor(sf::Color::Black);

            // Linie pionowe
            sf::RectangleShape verticalLines(sf::Vector2f(BLOCK_SIZE * BOARD_HEIGHT, 1.0f));
            verticalLines.rotate(90);
            verticalLines.setPosition((12 * BLOCK_SIZE) + BLOCK_SIZE * i, 0.0f);
            verticalLines.setFillColor(sf::Color::Black);

            gameWindow.draw(verticalLines);
            gameWindow.draw(horizontalLines);
        }

    }

    // Rysowanie tekstu z punktami
    sf::Text pointsNumber;
    pointsNumber.setFont(techno_font);
    std::string s_points = "Points:\n     " + std::to_string(points);
    pointsNumber.setString(s_points);
    pointsNumber.setPosition(CENTER / 2 - 200, WINDOW_HEIGHT / 2 + 100);
    pointsNumber.setCharacterSize(100);
    pointsNumber.setFillColor(sf::Color::Red);
    gameWindow.draw(pointsNumber);
    pointsNumber.setPosition((WINDOW_WIDTH) / 2 + (BOARD_WIDTH * BLOCK_SIZE) / 2 + 200, (WINDOW_HEIGHT / 2 + 100));
    gameWindow.draw(pointsNumber);

    // Rysowanie klocków pozostaj¹cych na planszy
    for (Block block : fixedFigures)
    {
        sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        rectangle.setPosition(float(block.getX() * BLOCK_SIZE), float(block.getY() * BLOCK_SIZE));
        rectangle.setFillColor(block.getColor());
        gameWindow.draw(rectangle);
    }
    // Rysowanie aktualnie spadaj¹cego klocka
    for (Block block : activeFigure.getBlocks())
    {
        sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        rectangle.setPosition(float((activeFigure.getX() + block.getX()) * BLOCK_SIZE), float((activeFigure.getY() + block.getY()) * BLOCK_SIZE));
        rectangle.setFillColor(block.getColor());
        gameWindow.draw(rectangle);
    }


    // Rysowanie t³a dla klocka, który pojawi siê jako kolejny
    sf::RectangleShape nextShapeBackground(sf::Vector2f(5 * BLOCK_SIZE, 5 * BLOCK_SIZE));
    nextShapeBackground.setFillColor(sf::Color::White);

    //Lewe t³o
    nextShapeBackground.setPosition(3 * BLOCK_SIZE, 3 * BLOCK_SIZE);
    gameWindow.draw(nextShapeBackground);
    // Linie
    for (int i = 0; i <= 5; i++)
    {
        for (int j = 0; j <= 5; j++)
        {
            // Linie poziome
            sf::RectangleShape horizontalLines(sf::Vector2f(BLOCK_SIZE * 5, 1.0f));
            horizontalLines.setPosition(3 * BLOCK_SIZE, float(3 * BLOCK_SIZE + j * BLOCK_SIZE));
            horizontalLines.setFillColor(sf::Color::Black);

            // Linie pionowe
            sf::RectangleShape verticalLines(sf::Vector2f(BLOCK_SIZE * 5, 1.0f));
            verticalLines.rotate(90);
            verticalLines.setPosition((3 * BLOCK_SIZE) + BLOCK_SIZE * i, 3 * BLOCK_SIZE);
            verticalLines.setFillColor(sf::Color::Black);

            gameWindow.draw(verticalLines);
            gameWindow.draw(horizontalLines);
        }

    }

    // Prawe t³o
    nextShapeBackground.setPosition(27 * BLOCK_SIZE, 3 * BLOCK_SIZE);
    gameWindow.draw(nextShapeBackground);
    // Linie
    for (int i = 0; i <= 5; i++)
    {
        for (int j = 0; j <= 5; j++)
        {
            // Linie poziome
            sf::RectangleShape horizontalLines(sf::Vector2f(BLOCK_SIZE * 5, 1.0f));
            horizontalLines.setPosition(27 * BLOCK_SIZE, float(3 * BLOCK_SIZE + j * BLOCK_SIZE));
            horizontalLines.setFillColor(sf::Color::Black);

            // Linie pionowe
            sf::RectangleShape verticalLines(sf::Vector2f(BLOCK_SIZE * 5, 1.0f));
            verticalLines.rotate(90);
            verticalLines.setPosition((27 * BLOCK_SIZE) + BLOCK_SIZE * i, 3 * BLOCK_SIZE);
            verticalLines.setFillColor(sf::Color::Black);

            gameWindow.draw(verticalLines);
            gameWindow.draw(horizontalLines);
        }

    }


    // Rysowanie klocka który pojawi siê jako kolejny
    for (Block block : nextFigure.getFigureBlocks())
    {
        sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        rectangle.setPosition((3 + 2) * BLOCK_SIZE + block.getX() * BLOCK_SIZE, (3 + 2) * BLOCK_SIZE + block.getY() * BLOCK_SIZE);
        rectangle.setFillColor(block.getColor());
        gameWindow.draw(rectangle);
    }

    // Rysowanie klocka który pojawi siê jako kolejny
    for (Block block : nextFigure.getFigureBlocks())
    {
        sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        rectangle.setPosition((27 + 2) * BLOCK_SIZE + block.getX() * BLOCK_SIZE, (3 + 2) * BLOCK_SIZE + block.getY() * BLOCK_SIZE);
        rectangle.setFillColor(block.getColor());
        gameWindow.draw(rectangle);
    }

    gameWindow.display();
}

void Game::openWindow()
{
    while (gameWindow.isOpen())
    {
        eventPolling();
        updateGameLogic();
        render();
    }
}

void Game::menuSetup()
{
    sf::RenderWindow menuWindow(sf::VideoMode(unsigned int(1280), unsigned int(720)), "Tetris Bieda Edition Menu", sf::Style::Close);

    //techno_font.loadFromFile("Dependencies\\Fonts\\Techno.otf");
    //techno_font.loadFromMemory(&Techno_otf, Techno_otf_len);

    while (menuWindow.isOpen())
    {
        sf::Event menuEvent;

        //Obs³uga naciœniêæ odpwiednich klawiszy z klawiatury
        while (menuWindow.pollEvent(menuEvent))
        {
            if (menuEvent.type == sf::Event::Closed) menuWindow.close();
            if (menuEvent.type == sf::Event::KeyPressed)
            {
                if (menuEvent.key.code == sf::Keyboard::Escape)
                {
                    menuWindow.close();
                }
                if (menuEvent.key.code == sf::Keyboard::Num1)
                {
                    difficultyChoice = 1;
                    menuWindow.close();
                }
                if (menuEvent.key.code == sf::Keyboard::Num2)
                {
                    difficultyChoice = 2;
                    menuWindow.close();
                }
                if (menuEvent.key.code == sf::Keyboard::Num3)
                {
                    difficultyChoice = 3;
                    menuWindow.close();
                }
            }
        };




        //Wyœwietlanie
        menuWindow.clear(sf::Color(153, 204, 255));
        sf::Text option1;
        sf::Text option2;
        sf::Text option3;
        sf::Text description1;
        sf::Text description2;
        sf::Text description3;
        sf::Text chooseDifText;

        chooseDifText.setFont(techno_font);
        chooseDifText.setString("    Choose your difficulty, by\npressing the keyboard button!");
        chooseDifText.setPosition(300, 50);
        chooseDifText.setFillColor(sf::Color::Red);
        chooseDifText.setCharacterSize(50);

        option1.setFont(techno_font);
        option1.setString("     1\nEASY");
        option1.setPosition(175, 300);
        option1.setFillColor(sf::Color::Red);
        option1.setCharacterSize(50);

        description1.setFont(techno_font);
        description1.setString("    Figures fall slowly,\n  you can rotate them\nand you can sometimes\n get bonus figure, which\n         is single block!");
        description1.setPosition(100, 500);
        description1.setFillColor(sf::Color::Red);
        description1.setCharacterSize(25);

        option2.setFont(techno_font);
        option2.setString("       2\nNORMAL");
        option2.setPosition(550, 300);
        option2.setFillColor(sf::Color::Red);
        option2.setCharacterSize(50);

        description2.setFont(techno_font);
        description2.setString("     Figures fall normally\nand you can rotate them!");
        description2.setPosition(500, 500);
        description2.setFillColor(sf::Color::Red);
        description2.setCharacterSize(25);

        option3.setFont(techno_font);
        option3.setString("     3\nHARD");
        option3.setPosition(1000, 300);
        option3.setFillColor(sf::Color::Red);
        option3.setCharacterSize(50);

        description3.setFont(techno_font);
        description3.setString("      Figures fall very fast\nand you can't rotate them!");
        description3.setPosition(925, 500);
        description3.setFillColor(sf::Color::Red);
        description3.setCharacterSize(25);

        menuWindow.draw(option1);
        menuWindow.draw(description1);
        menuWindow.draw(option2);
        menuWindow.draw(description2);
        menuWindow.draw(option3);
        menuWindow.draw(description3);
        menuWindow.draw(chooseDifText);
        menuWindow.display();
    }

    //Je¿eli zamkniêto okno, bez wybrania poziomu trudnoœci, zakoñcz program.
    if (difficultyChoice == 0)
    {
        exit(0);
    }
}

void Game::endGame()
{
    gameWindow.close();
    sf::RenderWindow endWindow(sf::VideoMode(unsigned int(WINDOW_WIDTH), unsigned int(WINDOW_HEIGHT)), "Tetris Bieda Edition", sf::Style::Fullscreen);

    sf::Event endEvent;
    while (endWindow.isOpen())
    {
        while (endWindow.pollEvent(endEvent))
        {
            if (endEvent.type == sf::Event::KeyPressed)
            {
                if (endEvent.key.code == sf::Keyboard::Escape)
                {
                    endWindow.close();
                }
            }
        }

        endWindow.clear(sf::Color(153, 204, 255));

        sf::Text gameOverText;
        std::string gameOverString = "GAME OVER! YOU GAINED " + std::to_string(points) + " POINTS !\n           PRESS ESC KEY TO EXIT!";
        gameOverText.setFont(techno_font);
        gameOverText.setString(gameOverString);
        gameOverText.setPosition(120, 400);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setCharacterSize(115);
        endWindow.draw(gameOverText);

        endWindow.display();
    }
}

void Game::displayControls()
{
    techno_font.loadFromMemory(&Techno_otf, Techno_otf_len);

    sf::RenderWindow controlsWindow(sf::VideoMode(unsigned int(1280), unsigned int(720)), "Tetris Bieda Edition Controls", sf::Style::Close);
    
    sf::Event controlsEvent;

    sf::Text controlsText;
    controlsText.setFont(techno_font);
    controlsText.setString("Use arrow keys to move, Q and E keys to rotate\n the figure. Remember, you can't rotate figures\n                                 in the hard mode!\n                       Press ENTER to continue...");
    controlsText.setPosition(sf::Vector2f(30, 200));
    controlsText.setFillColor(sf::Color::Red);
    controlsText.setCharacterSize(60);

    while (controlsWindow.isOpen())
    {
        while (controlsWindow.pollEvent(controlsEvent))
        {
            if (controlsEvent.type == sf::Event::Closed)
            {
                exit(0);
            }
            if (controlsEvent.type == sf::Event::KeyPressed)
            {
                if (controlsEvent.key.code == sf::Keyboard::Enter)
                {
                    controlsWindow.close();
                }
                if (controlsEvent.key.code == sf::Keyboard::Escape)
                {
                    exit(0);
                }
            }
        }


        



        controlsWindow.clear(sf::Color(153, 204, 255));
        controlsWindow.draw(controlsText);
        controlsWindow.display();

        


    }

    controlsWindow.close();
}