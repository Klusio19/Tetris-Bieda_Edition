#include "ActiveFigure.h"

ActiveFigure::ActiveFigure(int difLevel, int setShape, sf::Color setColor)
{
	sf::Color currentColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	sf::Color nextColor = setColor;

    int nextShape = Figure::shape;

    // Losujemy kszta³t figury
    if (difLevel == 1)
    {
        shape = setShape;
    }
    else
    {
        shape = setShape;
    }

    if (shape == 0) // Kszta³t "L"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 2, nextColor);
        m_blocks.emplace_back(1, 2, nextColor);
    }
    else if (shape == 1) // Kszta³t "J"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 2, nextColor);
        m_blocks.emplace_back(-1, 2, nextColor);
    }
    else if (shape == 2) // Kszta³t "I"
    {
        m_blocks.emplace_back(-1, 0, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
        m_blocks.emplace_back(2, 0, nextColor);
    }
    else if (shape == 3) // Kszta³t "O"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
        m_blocks.emplace_back(1, 1, nextColor);
    }
    else if (shape == 4) // Kszta³t "S"
    {
        m_blocks.emplace_back(-1, 0, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(1, 1, nextColor);
    }
    else if (shape == 5) // Kszta³t "Z"
    {
        m_blocks.emplace_back(-1, 1, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
    }
    else if (shape == 6) // Kszta³t "T"
    {
        m_blocks.emplace_back(-1, 1, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(1, 1, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
    }
    else if (shape == 7) //Pojednynczy klocek
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

void ActiveFigure::rotateClockwise()
{
    if (shape == 3) return; // je¿eli kszta³t to kwadrat to nie obracamy
    for (Block& block : m_blocks)
    {
        int temp = block.getX();
        block.setX(block.getY());
        block.setY(-temp);
    }
}

void ActiveFigure::rotateCounterclockwise()
{
    if (shape == 3) return; // je¿eli kszta³t to kwadrat to nie obracamy
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
        for (Block fixedBlock : fixedFigures)
        {
            if (newX == fixedBlock.getX() && newY == fixedBlock.getY()) return false;
        }
    }
    return true;
}

void ActiveFigure::move(int x, int y)
{
    m_x += x;
    m_y += y;
}
