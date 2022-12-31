#include "Figure.h"

void Figure::setFigurePosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Figure::initFigure()
{
    m_blocks.clear();
    figureColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);

    // Losujemy kszta速 figury
    if (difficultyChoice == 1)
    {
        figureShape = rand() % 8;
    }
    else
    {
        figureShape = rand() % 7;
    }

    if (figureShape == 0) // Kszta速 "L"
    {
        m_blocks.emplace_back(0, -1, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(1, 1, figureColor);
    }
    else if (figureShape == 1) // Kszta速 "J"
    {
        m_blocks.emplace_back(0, -1, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(-1, 1, figureColor);
    }
    else if (figureShape == 2) // Kszta速 "I"
    {
        m_blocks.emplace_back(-1, 0, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(1, 0, figureColor);
        m_blocks.emplace_back(2, 0, figureColor);
    }
    else if (figureShape == 3) // Kszta速 "O"
    {
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(1, 0, figureColor);
        m_blocks.emplace_back(1, 1, figureColor);
    }
    else if (figureShape == 4) // Kszta速 "S"
    {
        m_blocks.emplace_back(-1, 0, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(1, 1, figureColor);
    }
    else if (figureShape == 5) // Kszta速 "Z"
    {
        m_blocks.emplace_back(-1, 1, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(1, 0, figureColor);
    }
    else if (figureShape == 6) // Kszta速 "T"
    {
        m_blocks.emplace_back(-1, 0, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(1, 0, figureColor);
        m_blocks.emplace_back(0, -1, figureColor);
    }
    else if (figureShape == 7) //Pojednynczy klocek
    {
        m_blocks.emplace_back(0, 0, figureColor);
    }
}

std::vector<Block> Figure::getFigureBlocks() const
{
    return m_blocks;
}

int Figure::getX() const
{
	return m_x;
}

int Figure::getY() const
{
	return m_y;
}

int Figure::getShape()
{
    return figureShape;
}

sf::Color Figure::getColor()
{
    return figureColor;
}
