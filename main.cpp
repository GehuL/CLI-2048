#include <time.h>
#include <iostream>
#include "Board.h"


int main(void)
{
    srand( time( NULL ) );

    gehul::Board board(4);
    std::cout << board << std::endl;

    do
    {
        char c;

        std::cout << "Move (ZQSD):" << std::endl;
        std::cin >> c;

        c = toupper(c);

        if(c == 'Q')
            break;

        board.move((gehul::Direction) c);
        std::cout << board << std::endl;

    }while(true);
}
