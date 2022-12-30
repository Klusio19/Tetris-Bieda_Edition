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

int difficultyChoice = 0;

void Game::initValues(int diffChoice)
{
    switch (diffChoice)
    {
    case 1:
    {
        FALL_SPEED = 1.0f;
        break;
    }

    case 2:
    {
        FALL_SPEED = 0.4f;
        break;
    }

    case 3:
    {
        FALL_SPEED = 0.2f;
        break;
    }
    }
    BOARD_WIDTH = 10.0f;
    BOARD_HEIGHT = 20.0f;
    BLOCK_SIZE = 54.0f;
    WINDOW_WIDTH = 1920.0f;
    WINDOW_HEIGHT = 1080.0f;

    CENTER = (WINDOW_WIDTH / 2) - (BOARD_WIDTH * BLOCK_SIZE / 2);
    techno_font.loadFromFile("Dependencies\\Fonts\\Techno.otf");
    //techno_font.loadFromFile("Dependencies\\Fonts\\OpenSans-Medium.ttf");

    gameWindow.create(sf::VideoMode(unsigned int(WINDOW_WIDTH), unsigned int(WINDOW_HEIGHT)), "Tetris Bieda Edition", sf::Style::Default);
    currentTime = 0.0f;
    previousTime = 0.0f;
    points = 0;

}

void Game::eventPolling()
{
    // Obs³uga naciœniêæ klawiszy
    while (gameWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) gameWindow.close();
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                gameWindow.close();
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
                if (difficultyChoice == 3) return;
                activeFigure.rotateClockwise();
            }
            if (event.key.code == sf::Keyboard::E)
            {
                if (difficultyChoice == 3) return;
                activeFigure.rotateCounterclockwise();
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
    // Rysowanie planszy gry
    gameWindow.clear();

    //Bia³e t³o
    sf::RectangleShape whiteBackground(sf::Vector2f(BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE));
    whiteBackground.setPosition(12 * BLOCK_SIZE, 0);
    whiteBackground.setFillColor(sf::Color::White);
    gameWindow.draw(whiteBackground);

    //Kolorowe boki
    //lewy
    sf::RectangleShape colorSide(sf::Vector2f(12 * BLOCK_SIZE, WINDOW_HEIGHT));
    colorSide.setPosition(0, 0);
    colorSide.setFillColor(sf::Color(153, 204, 255));
    gameWindow.draw(colorSide);
    //prawy
    colorSide.setSize(sf::Vector2f(14 * BLOCK_SIZE, WINDOW_HEIGHT));
    colorSide.setPosition(22 * BLOCK_SIZE, 0);
    gameWindow.draw(colorSide);

    //Linie
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

            gameWindow.draw(verticalLines);
            gameWindow.draw(horizontalLines);
        }
    }

    //Rysowanie tekstu z punktami
    sf::Text pointsNumber;
    pointsNumber.setFont(techno_font);
    std::string s_points = "Points:\n     " + std::to_string(points);
    pointsNumber.setString(s_points);
    pointsNumber.setPosition(CENTER / 2 - 200, WINDOW_HEIGHT / 2 - 100);
    pointsNumber.setCharacterSize(100);
    pointsNumber.setFillColor(sf::Color::Red);
    gameWindow.draw(pointsNumber);
    pointsNumber.setPosition((WINDOW_WIDTH) / 2 + (BOARD_WIDTH * BLOCK_SIZE) / 2 + 200, (WINDOW_HEIGHT / 2) - 100);
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
    sf::Font open_sans;
    open_sans.loadFromFile("Dependencies\\Fonts\\OpenSans-Medium.ttf");


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

        chooseDifText.setFont(open_sans);
        chooseDifText.setString("    Choose your difficulty, by\npressing the keyboard button!");
        chooseDifText.setPosition(300, 50);
        chooseDifText.setFillColor(sf::Color::Red);
        chooseDifText.setCharacterSize(50);

        option1.setFont(open_sans);
        option1.setString("   1\nEASY");
        option1.setPosition(150, 300);
        option1.setFillColor(sf::Color::Red);
        option1.setCharacterSize(50);

        description1.setFont(open_sans);
        description1.setString("Figures fall slowly,\nyou can rotate them\nand you can sometimes\nget bonus figure, which\nis single block!");
        description1.setPosition(100, 500);
        description1.setFillColor(sf::Color::Red);
        description1.setCharacterSize(25);

        option2.setFont(open_sans);
        option2.setString("       2\nNORMAL");
        option2.setPosition(525, 300);
        option2.setFillColor(sf::Color::Red);
        option2.setCharacterSize(50);

        description2.setFont(open_sans);
        description2.setString("Figures fall normally\nand you can rotate them!");
        description2.setPosition(500, 500);
        description2.setFillColor(sf::Color::Red);
        description2.setCharacterSize(25);

        option3.setFont(open_sans);
        option3.setString("    3\nHARD");
        option3.setPosition(1000, 300);
        option3.setFillColor(sf::Color::Red);
        option3.setCharacterSize(50);

        description3.setFont(open_sans);
        description3.setString("Figures fall very fast\nand you can't rotate them!");
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

void Game::run()
{
    menuSetup();
    initValues(difficultyChoice);
    openWindow();
}

int Game::getDifficultyChoice()
{
    return difficultyChoice;
}