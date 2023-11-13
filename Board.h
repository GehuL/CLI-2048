#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <ostream>

namespace gehul
{
    enum class Direction
    {
        GAUCHE = 'Q',
        DROITE = 'D',
        HAUT   = 'Z',
        BAS    = 'S'
    };

    class Board
    {
        public:

        Board(int longueur);

        void move(Direction dir);

        void restart();

        void setTile(int x, int y, int value);

        int getTile(int x, int y) const;

        std::ostream& print(std::ostream& os);

        friend std::ostream& operator<<(std::ostream& os, Board& board);

        private:

        void move(int dx, int dy);

        void genRandomTiles();

        inline int linearize(int x, int y) const;

        int _score;

        int _tries;

        int _longueur;

        std::vector<int> _tiles;

    };
}


#endif
