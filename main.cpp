#include "Board.h"
#include "Utils.h"

#include <iostream>
#include <time.h>

#ifdef _WIN32
#define CLEAR "CLS"
#endif

#ifdef __APPLE__
#define CLEAR "CLEAR"
#endif

int main(void)
{
    srand( time( NULL ) );

    gehul::Board board(5);
    std::cout << board << std::endl;

    bool stop = false;
    do
    {
        system(CLEAR);
        std::cout << "----- 2048 -----\nEnter O to quit. R to restart" << std::endl;
        std::cout << board << std::endl;
        
        std::string input;
        while(input.size() != 1)
        {
            std::cout << "Move (ZQSD): ";
            std::cin >> input;
            if(input.size() > 1)
                std::cout << "\nVeuillez entrer un seul caractère" << std::endl;
        }

        char c = input[0];
        c = toupper(c);

        switch(c)
        {
            case 'R':
                board.restart();
                break;
            case 'O':
                stop = true;
                break;
            default:
                board.move((gehul::Direction) c);
                break;
        }
  

    } while(!stop);
}
