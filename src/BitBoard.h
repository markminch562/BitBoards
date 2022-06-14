//
// Created by Mark Minch  on 6/14/22.
//

#ifndef BITBOARDS_BITBOARD_H
#define BITBOARDS_BITBOARD_H
#include <iostream>
#include <bitset>

/*
 * For this program I will be using a technique called bit boards that I learned about
 * that saves a lot of memory while also reducing the memory by saving the entire game board in
 * an unsigned Long Long, so it only takes up 64 bits of memory or 8 bytes which means that the whole board can
 * fit into a single regester, and allows for checking win state in as few as 4 or so cpu cycles
 *
 * the board stores every bit that is used for the board in a form like this
 * 6 13 20 27 34 42 48     55 62
 * --------------------   this is the board
 * 5 12 19 26 33 40 47 |  54  61
 * 4 11 18 25 32 39 46 |  53  60
 * 3 10 17 24 31 38 45 |  52  59
 * 2  9 16 23 30 37 44 |  51  58
 * 1  8 15 22 29 36 43 |  50  57
 * 0  7 14 21 28 35 42 |  49  56  63
 * -------------------
 *
 * So the first 6 represent column 0 and 7-12 represent column 1
 */

struct GameBoard;
typedef  unsigned long long int BitBoard;
typedef void(*GameState)(GameBoard&);

struct GameBoard
{
    //initilize memory to prevent bad data on construction
    BitBoard Player1 = 0;
    BitBoard Player2 = 0;

    // will hold the current height we can place a token at for the player
    int height[8] = {0};

    //this will hold the state of all previous moves done, so that we can unwind and undo the game from any player and
    //any state at any point in the game
    //we will never need more than 42 game states because there can never be more than 42 tokens on the board at a time
    int move = 1;
    int moves [42];

    //typedef function pointer about what to be doing based on game states
    GameState state;
    //to get RAII Rule of zero there will be no constructor, destructor or copy constructor
    //we will let the C++ compiler to auto construct it for us
};

bool checkIfWon(BitBoard board);
void UserPrompt(GameBoard& board);

void printBoard(uint64_t board);
void printBoard(GameBoard& board);
void printBoard(uint64_t board, uint64_t board2);


#endif //BITBOARDS_BITBOARD_H
