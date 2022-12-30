#include "ActiveFigure.h"

// Konstruktor tworz�cy losow� figur�
ActiveFigure::ActiveFigure()
{
    // Losujemy kolor figury
    sf::Color color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
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
        m_blocks.emplace_back(0, 0, color);
        m_blocks.emplace_back(0, 1, color);
        m_blocks.emplace_back(0, 2, color);
        m_blocks.emplace_back(1, 2, color);
    }
    else if (shape == 1) // Kszta�t "J"
    {
        m_blocks.emplace_back(0, 0, color);
        m_blocks.emplace_back(0, 1, color);
        m_blocks.emplace_back(0, 2, color);
        m_blocks.emplace_back(-1, 2, color);
    }
    else if (shape == 2) // Kszta�t "I"
    {
        m_blocks.emplace_back(-1, 0, color);
        m_blocks.emplace_back(0, 0, color);
        m_blocks.emplace_back(1, 0, color);
        m_blocks.emplace_back(2, 0, color);
    }
    else if (shape == 3) // Kszta�t "O"
    {
        m_blocks.emplace_back(0, 0, color);
        m_blocks.emplace_back(0, 1, color);
        m_blocks.emplace_back(1, 0, color);
        m_blocks.emplace_back(1, 1, color);
    }
    else if (shape == 4) // Kszta�t "S"
    {
        m_blocks.emplace_back(-1, 0, color);
        m_blocks.emplace_back(0, 0, color);
        m_blocks.emplace_back(0, 1, color);
        m_blocks.emplace_back(1, 1, color);
    }
    else if (shape == 5) // Kszta�t "Z"
    {
        m_blocks.emplace_back(-1, 1, color);
        m_blocks.emplace_back(0, 1, color);
        m_blocks.emplace_back(0, 0, color);
        m_blocks.emplace_back(1, 0, color);
    }
    else if (shape == 6) // Kszta�t "T"
    {
        m_blocks.emplace_back(-1, 1, color);
        m_blocks.emplace_back(0, 1, color);
        m_blocks.emplace_back(1, 1, color);
        m_blocks.emplace_back(0, 0, color);
    }
    else if (shape == 7) //Pojednynczy klocek
    {
        m_blocks.emplace_back(0, 0, color);
    }

    // Ustawiamy pozycj� pocz�tkow� figury
    m_x = int(12 + 10/2);
    m_y = 0;
}

std::vector<Block> ActiveFigure::getBlocks() const
{
    return m_blocks;
}

int ActiveFigure::getX() const
{
    return m_x;
}

int ActiveFigure::getY() const
{
    return m_y;
}

// Funkcja obracaj�ca figur� o 90� zgodnie ze wskaz�wkami zegara
// Ka�dy punkt (x,y) staje si� punktem (y, -x)
void ActiveFigure::rotateClockwise()
{
    if (shape == 3) return; // je�eli kszta�t to kwadrat to nie obracamy
    for (Block& block : m_blocks)
    {
        int temp = block.getX();
        block.setX(block.getY());
        block.setY(-temp);
    }
}

// Funkcja obracaj�ca figur� o 90� przeciwnie do ruchu wskaz�wek zegara
// Ka�dy punkt (x,y) staje si� punktem (-y, x)
void ActiveFigure::rotateCounterclockwise()
{
    if (shape == 3) return; // je�eli kszta�t to kwadrat to nie obracamy
    // TODO sprawdzenie czy mo�na obr�ci� figur�
    for (Block& block : m_blocks)
    {
        int temp = block.getX();
        block.setX(-block.getY());
        block.setY(temp);
    }
}

// Funkcja sprawdzaj�ca, czy figura mo�e by� przesuni�ty w danym kierunku
bool ActiveFigure::canMove(int x, int y, const std::vector<Block>& fixedBlocks)
{
    for (Block i : m_blocks)
    {
        int newX = m_x + i.getX() + x;
        int newY = m_y + i.getY() + y;
        if (newX < 12 || newX >= 12 + BOARD_WIDTH || newY >= BOARD_HEIGHT) return false;
        for (Block fixedBlock : fixedBlocks)
        {
            if (newX == fixedBlock.getX() && newY == fixedBlock.getY()) return false;
        }
    }
    return true;
}

// Funkcja przesuwaj�ca figur� o podan� liczb� pozycji w danym kierunku
void ActiveFigure::move(int x, int y)
{
    m_x += x;
    m_y += y;
}


