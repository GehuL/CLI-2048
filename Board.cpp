#include "Board.h"
#include "Utils.h"

#include <time.h>
#include <random>
#include <iostream>
#include <assert.h>

namespace gehul
{
    Board::Board(int longueur) : _longueur(longueur), _tiles(longueur * longueur, 0)
    {
        assert(longueur > 0 && "Longuer must be greater than zero");
        restart();
    }

    // Deplace les valeurs vers le bas
    void Board::move()
    {
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
                            break;
                        }
                        else if (k == _longueur - 1)
                        {
                            setTile(i, j, 0);
                            setTile(i, k, value);
                            break;
                        }
                    }
                }
            }
    }

    void Board::flipH()
    {
        for (int i = 0; i < _longueur; i++)
        {
            for (int j = 0; j < _longueur / 2; j++)
            {
                int tmp = getTile(i, j);
                setTile(i, j, getTile(i, _longueur - 1 - j));
                setTile(i, _longueur - 1 - j, tmp);
            }
        }
    }

    void Board::flipV()
    {
        for (int i = 0; i < _longueur / 2; i++)
        {
            for (int j = 0; j < _longueur; j++)
            {
                int tmp = getTile(i, j);
                setTile(i, j, getTile(_longueur - 1 - i, j));
                setTile(_longueur - 1 - i, j, tmp);
            }
        }
    }

    void Board::transpose()
    {
        for(int i=0; i< _longueur; i++)
        {
            for(int j = i + 1; j < _longueur; j++)
            {
                int tmp = getTile(i, j);
                setTile(i, j, getTile(j, i));
                setTile(j, i, tmp);
            }
        }
    }

    void Board::move(Direction dir)
    {
        switch (dir)
        {
        case Direction::BAS:
            move();
            break;
        case Direction::HAUT:
            flipH();
            move();
            flipH();
            break;
        case Direction::DROITE:
            transpose();
            flipV();
            move();
            flipV();
            transpose();
            break;
        case Direction::GAUCHE:
            transpose();
            flipH();
            move();
            flipH();
            transpose();
            break;
        }

        _tries++;
        std::vector<int> freespaces = getAvailableSpace();
        if(freespaces.size() == 0);
        else
            _tiles[rand() % freespaces.size()] = (rand() % 2) * 2 + 2;
    }

    std::vector<int> Board::getAvailableSpace()
    {
        std::vector<int> index;
        for(int i = 0; i < _tiles.size(); i++)
            if(_tiles[i] == 0) index.push_back(i);
        return index;
    }

    void Board::restart()
    {
        _score = 0;
        _tries = 0;

        genRandomTiles();
        genRandomTiles();
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

                os << "  ";
            }
            os << "\n" << std::endl;
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
        _tiles[index] = (rand() % 2) * 2 + 2;
    }
}
