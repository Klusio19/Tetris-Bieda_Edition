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

    // Losujemy kszta�t figury
    if (difficultyChoice == 1)
    {
        shape = rand() % 8;
    }
    else
    {
        shape = rand() % 7;
    }

    if (shape == 0) // Kszta�t "L"
    {
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(0, 2, figureColor);
        m_blocks.emplace_back(1, 2, figureColor);
    }
    else if (shape == 1) // Kszta�t "J"
    {
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(0, 2, figureColor);
        m_blocks.emplace_back(-1, 2, figureColor);
    }
    else if (shape == 2) // Kszta�t "I"
    {
        m_blocks.emplace_back(-1, 0, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(1, 0, figureColor);
        m_blocks.emplace_back(2, 0, figureColor);
    }
    else if (shape == 3) // Kszta�t "O"
    {
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(1, 0, figureColor);
        m_blocks.emplace_back(1, 1, figureColor);
    }
    else if (shape == 4) // Kszta�t "S"
    {
        m_blocks.emplace_back(-1, 0, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(1, 1, figureColor);
    }
    else if (shape == 5) // Kszta�t "Z"
    {
        m_blocks.emplace_back(-1, 1, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
        m_blocks.emplace_back(1, 0, figureColor);
    }
    else if (shape == 6) // Kszta�t "T"
    {
        m_blocks.emplace_back(-1, 1, figureColor);
        m_blocks.emplace_back(0, 1, figureColor);
        m_blocks.emplace_back(1, 1, figureColor);
        m_blocks.emplace_back(0, 0, figureColor);
    }
    else if (shape == 7) //Pojednynczy klocek
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
    return shape;
}

sf::Color Figure::getColor()
{
    return figureColor;
}
