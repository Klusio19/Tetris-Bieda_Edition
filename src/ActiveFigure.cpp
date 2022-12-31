#include "ActiveFigure.h"

ActiveFigure::ActiveFigure(int difLevel, int setShape, sf::Color setColor)
{
	sf::Color currentColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	sf::Color nextColor = setColor;

    //int nextActiveFigureShape = Figure::figureShape;

    // Losujemy kszta³t figury
    if (difLevel == 1)
    {
        activeFigureShape = setShape;
    }
    else
    {
        activeFigureShape = setShape;
    }

    if (activeFigureShape == 0) // Kszta³t "L"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 2, nextColor);
        m_blocks.emplace_back(1, 2, nextColor);
    }
    else if (activeFigureShape == 1) // Kszta³t "J"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 2, nextColor);
        m_blocks.emplace_back(-1, 2, nextColor);
    }
    else if (activeFigureShape == 2) // Kszta³t "I"
    {
        m_blocks.emplace_back(-1, 0, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
        m_blocks.emplace_back(2, 0, nextColor);
    }
    else if (activeFigureShape == 3) // Kszta³t "O"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
        m_blocks.emplace_back(1, 1, nextColor);
    }
    else if (activeFigureShape == 4) // Kszta³t "S"
    {
        m_blocks.emplace_back(-1, 0, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(1, 1, nextColor);
    }
    else if (activeFigureShape == 5) // Kszta³t "Z"
    {
        m_blocks.emplace_back(-1, 1, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
    }
    else if (activeFigureShape == 6) // Kszta³t "T"
    {
        m_blocks.emplace_back(-1, 1, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(1, 1, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
    }
    else if (activeFigureShape == 7) //Pojednynczy klocek
    {
        m_blocks.emplace_back(0, 0, nextColor);
    }

    // Ustawiamy pozycjê pocz¹tkow¹ figury
    m_x = int(12 + 10 / 2);
    m_y = 0;
}

std::vector<Block> ActiveFigure::getBlocks() const
{
    return m_blocks;
}

bool ActiveFigure::canRotateClockwise(const std::vector<Block>& fixedFigures)
{
    if (activeFigureShape == 3) return false;

    ActiveFigure tempFigure = *this;
    tempFigure.rotateClockwise();

    // pêtla for która sprawdzi kolizjê z granicami planszy
    for (Block& block : tempFigure.m_blocks)
    {
        if (tempFigure.m_x + block.getX() < 12 || tempFigure.m_x + block.getX() > 11 + BOARD_WIDTH || tempFigure.m_y + block.getY() > BOARD_HEIGHT) return false;
    }

    // pêtla for która sprawdzi kolizjê z innymi klockami
    for (Block block : fixedFigures)
    {
        for (Block tempBlock : tempFigure.m_blocks)
        {
            if (tempFigure.m_x + tempBlock.getX() == block.getX() && tempFigure.m_y + tempBlock.getY() == block.getY()) return false;
        }
    }

    return true;
}

void ActiveFigure::rotateClockwise()
{
    if (activeFigureShape == 3) return; // je¿eli kszta³t to kwadrat to nie obracamy
    for (Block& block : m_blocks)
    {
        int temp = block.getX();
        block.setX(block.getY());
        block.setY(-temp);
    }
}

bool ActiveFigure::canRotateCounterclockwise(const std::vector<Block>& fixedFigures)
{
    if (activeFigureShape == 3) return false;

    ActiveFigure tempFigure = *this;
    tempFigure.rotateCounterclockwise();

    // pêtla for która sprawdzi kolizjê z granicami planszy
    for (Block& block : tempFigure.m_blocks)
    {
        if (tempFigure.m_x + block.getX() < 12 || tempFigure.m_x + block.getX() > 11 + BOARD_WIDTH || tempFigure.m_y + block.getY() > BOARD_HEIGHT) return false;
    }

    // pêtla for która sprawdzi kolizjê z innymi klockami
    for (Block block : fixedFigures)
    {
        for (Block tempBlock : tempFigure.m_blocks)
        {
            if (tempFigure.m_x + tempBlock.getX() == block.getX() && tempFigure.m_y + tempBlock.getY() == block.getY()) return false;
        }
    }

    return true;
}

void ActiveFigure::rotateCounterclockwise()
{
    if (activeFigureShape == 3) return; // je¿eli kszta³t to kwadrat to nie obracamy
    for (Block& block : m_blocks)
    {
        int temp = block.getX();
        block.setX(-block.getY());
        block.setY(temp);
    }
}

bool ActiveFigure::canMove(int x, int y, const std::vector<Block>& fixedFigures)
{
    for (Block i : m_blocks)
    {
        int newX = m_x + i.getX() + x;
        int newY = m_y + i.getY() + y;
        if (newX < 12 || newX >= 12 + BOARD_WIDTH || newY >= BOARD_HEIGHT) return false;
        for (Block block : fixedFigures)
        {
            if (newX == block.getX() && newY == block.getY()) return false;
        }
    }
    return true;
}

void ActiveFigure::move(int x, int y)
{
    m_x += x;
    m_y += y;
}