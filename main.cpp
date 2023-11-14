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
        std::cout << "Move (ZQSD): ";
        std::cin >> c;
        c = toupper(c);

        if(c == 'R')
            board.restart();
        else
            board.move((gehul::Direction) c);

        system("cls");

        std::cout << "----- 2048 -----\nEnter O to quit. R to restart" << std::endl;
        std::cout << board << std::endl;

    } while(c != 'O');
}
