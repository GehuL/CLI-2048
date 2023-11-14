#include "Board.h"
#include "Utils.h"

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

    // Deplace les valeurs vers le bas de la grille
    // Renvoie si le plateau est différent
    bool Board::move()
    {
        std::vector<int> copie(_tiles);

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
        return copie != _tiles;
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
        bool moved = false;
        switch (dir)
        {
        case Direction::BAS:
            moved = move();
            break;
        case Direction::HAUT:
            flipH();
            moved = move();
            flipH();
            break;
        case Direction::DROITE:
            transpose();
            flipV();
            moved = move();
            flipV();
            transpose();
            break;
        case Direction::GAUCHE:
            transpose();
            flipH();
            moved = move();
            flipH();
            transpose();
            break;
        default:
            return;
        }

        if(moved)
        {
            _tries++;
            genRandomTiles();
        }
    }

    inline int Board::randVal() const
    {
        return (rand() % 2) * 2 + 2;
    }

    void Board::restart()
    {
        _score = 0;
        _tries = 0;

        _tiles.assign(_tiles.size(), 0);

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

    std::ostream &Board::print(std::ostream &os) const
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
        // Looking for indexes where there is a zero
        std::vector<int> free_indexes;
        for(int i = 0; i < _tiles.size(); i++)
            if(_tiles[i] == 0)
                free_indexes.push_back(i);

        // Insert a value at a random available space
        if(free_indexes.size() > 0)
        {
            int index = rand() % free_indexes.size();
            _tiles[free_indexes[index]] = randVal();
        }
    }
}
