#include <iostream>

#include "src/BitBoard.h"

int main() {

    //improvement that I would like to see made to this code problem
    //1 I'd like to be able to read the input from a text file rather than always be dependent on user
    //2 I'd like to be able to save current game state out to a text file if the game is to be saved
    //3 I'd like to be able to load a previous game into the program from a text file
    //4 I'd like to be able to back track/undo moves made during the game


    Game::GameBoard game;
    Game::Run(game);
    //std::cout<<sizeof(game)<<std::endl;

    return 0;
}
