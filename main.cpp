#include <iostream>
#include "src/BitBoard.h"
inline void printBoards(const Game::BitBoard board) {
    std::cout << "THE BIT SET VALUE for this number is " << board << std::endl;
    auto set = std::bitset<64>(board);
    for (int i = 6; i >= 0; i--) {
        int startVal = i - 7;
        for (int j = 0; j < 9; j++) {
            startVal += 7;
            std::cout << i + j * 7 << ": " << set[i + j * 7] << "\t";
        }
        std::cout << std::endl;
    }
}
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
