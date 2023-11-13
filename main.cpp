#include "Board.h"
#include "Utils.h"
#include <iostream>

int main(void)
{
    srand( time( NULL ) );

    gehul::Board board(5);
    std::cout << board << std::endl;

    char c;
    do
    {
        std::cout << "Move (ZQSD):" << std::endl;
        std::cin >> c;
        c = toupper(c);

        board.move((gehul::Direction) c);
        std::cout << board << std::endl;

    }while(c != 'O');
}
