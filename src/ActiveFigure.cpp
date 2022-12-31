#include "ActiveFigure.h"

ActiveFigure::ActiveFigure(int difLevel, int setShape, sf::Color setColor)
{
	sf::Color currentColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	sf::Color nextColor = setColor;

    int nextShape = Figure::shape;

    // Losujemy kszta速 figury
    if (difLevel == 1)
    {
        shape = setShape;
    }
    else
    {
        shape = setShape;
    }

    if (shape == 0) // Kszta速 "L"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 2, nextColor);
        m_blocks.emplace_back(1, 2, nextColor);
    }
    else if (shape == 1) // Kszta速 "J"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 2, nextColor);
        m_blocks.emplace_back(-1, 2, nextColor);
    }
    else if (shape == 2) // Kszta速 "I"
    {
        m_blocks.emplace_back(-1, 0, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
        m_blocks.emplace_back(2, 0, nextColor);
    }
    else if (shape == 3) // Kszta速 "O"
    {
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
        m_blocks.emplace_back(1, 1, nextColor);
    }
    else if (shape == 4) // Kszta速 "S"
    {
        m_blocks.emplace_back(-1, 0, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(1, 1, nextColor);
    }
    else if (shape == 5) // Kszta速 "Z"
    {
        m_blocks.emplace_back(-1, 1, nextColor);
        m_blocks.emplace_back(0, 1, nextColor);
        m_blocks.emplace_back(0, 0, nextColor);
        m_blocks.emplace_back(1, 0, nextColor);
    }
    else if (shape == 6) // Kszta速 "T"
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

    // Ustawiamy pozycj� pocz靖kow� figury
    m_x = int(12 + 10 / 2);
    m_y = 0;
}

std::vector<Block> ActiveFigure::getBlocks() const
{
    return m_blocks;
}

void ActiveFigure::rotateClockwise()
{
    if (shape == 3) return; // je瞠li kszta速 to kwadrat to nie obracamy
    for (Block& block : m_blocks)
    {
        int temp = block.getX();
        block.setX(block.getY());
        block.setY(-temp);
    }
}

void ActiveFigure::rotateCounterclockwise()
{
    if (shape == 3) return; // je瞠li kszta速 to kwadrat to nie obracamy
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
