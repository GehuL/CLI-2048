#include "Board.h"

#include <time.h>
#include <random>
#include <iostream>

namespace gehul
{
    Board::Board(int longueur) : _longueur(longueur), _tiles(longueur * longueur, 0)
    {
        assert(longueur > 0 && "Longuer must be greater than zero");
        restart();
    }

    void Board::move(int dx, int dy)
    {
    }

    void Board::move(Direction dir)
    {
        switch (dir)
        {
        case Direction::BAS:
            for (int i = 0; i < _longueur; i++)
            {
                for (int j = _longueur - 1; j >= 0; j--)
                {
                    int value = getTile(i, j);

                    if (value == 0)
                        continue;

                    for (int k = j + 1; k < _longueur; k++)
                    {
                        int value2 = getTile(i, k);
                        if (value2 != value && value2 != 0)
                        {
                            setTile(i, j, 0);
                            setTile(i, k - 1, value);
                            break;
                        }
                        else if (value == value2)
                        {
                            setTile(i, j, 0);
                            setTile(i, k, value2 * 2);
                            std::cout << "x2" << std::endl;
                            break;
                        }
                        else if (k == _longueur - 1)
                        {
                            setTile(i, j, 0);
                            setTile(i, k, value);
                            std::cout << "l" << std::endl;
                            break;
                        }
                    }
                }
            }
            break;
        case Direction::HAUT:

            for (int i = 0; i < _longueur; i++)
            {
                for (int j = 0; j < _longueur; j++)
                {
                    int value = getTile(i, j);

                    if (value == 0)
                        continue;

                    for (int k = j - 1; k >= 0; k--)
                    {
                        int value2 = getTile(i, k);
                        if (value2 != value && value2 != 0)
                        {
                            setTile(i, j, 0);
                            setTile(i, k + 1, value);
                            break;
                        }
                        else if (value == value2)
                        {
                            setTile(i, j, 0);
                            setTile(i, k, value2 * 2);
                            std::cout << "x2" << std::endl;
                            break;
                        }
                        else if (k == 0)
                        {
                            setTile(i, j, 0);
                            setTile(i, k, value);
                            std::cout << "l" << std::endl;
                            break;
                        }
                    }
                }
            }
            break;
        }
    }

    void Board::restart()
    {
        _score = 0;
        _tries = 0;

        setTile(0, 1, 2);
        setTile(0, 2, 2);
        setTile(0, 3, 2);
        setTile(0, 0, 2);

       // genRandomTiles();
        //genRandomTiles();
    }
    void Board::setTile(int x, int y, int value)
    {
        int index = linearize(x, y);
        _tiles[index] = value;
    }
    int Board::getTile(int x, int y) const
    {
        int index = linearize(x, y);
        return _tiles.at(index);
    }

    std::ostream &Board::print(std::ostream &os)
    {
        os << std::endl;
        os << "Tries: " << _tries << std::endl;
        os << "Score: " << _score << std::endl;
        os << std::endl;

        for (int j = 0; j < _longueur; j++)
        {
            for (int i = 0;; i++)
            {
                os << getTile(i, j);

                if (i == _longueur - 1)
                    break;

                os << '.';
            }
            os << std::endl;
        }

        return os;
    }

    inline int Board::linearize(int x, int y) const
    {
        return _longueur * y + x;
    }

    std::ostream &operator<<(std::ostream &os, Board &board)
    {
        return board.print(os);
    }

    void Board::genRandomTiles()
    {
        int index = rand() % _tiles.size();
        int b = rand() % 2;

        _tiles[index] = b == 0 ? 2 : 4;
    }
}