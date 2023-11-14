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

        std::ostream& print(std::ostream& os) const;

        friend std::ostream& operator<<(std::ostream& os, Board& board);

        private:

        inline int randVal() const;

        inline int linearize(int x, int y) const;

        void flipH();

        void flipV();

        void transpose();

        bool move();

        void genRandomTiles();

        int _score;

        int _tries;

        int _longueur;

        std::vector<int> _tiles;

    };
}


#endif
