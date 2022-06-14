//
// Created by Mark Minch  on 6/14/22.
//

#include "BitBoard.h"


void UserPrompt(GameBoard& board)
{
    //depending on the move count the player will be known
    BitBoard player = board.move%2 ? board.Player1 : board.Player2;

    //select the column that you want to use for the game
    char userInput = 'q';
    std::cout<<"User "<< (board.move%2 ? "Player 1" : "Player 2") <<" input a value between 1 and 7 to select where to place a token or quit the game with (q)"<<std::endl;
    std::cin>>userInput;
    if(userInput == 'q')
    {
        std::cout<<"You have Quit and forfit the game so "<< (board.move%2 ? "Player 2" : "Player 1")<< "Wins by default "<<std::endl;
        return;
    }
    else if(userInput >= '1' && userInput <= '7')
    {
        //check if the column that it was put in is full
        int Column = (int)(userInput- '0') -1;
        if(board.height[Column] > 5)
        {
            //the column is full, so you can not place an ime there
            std::cout<<"<------ERROR------>\nThe column that you place that token in is full try a different number"<<std::endl;
            UserPrompt(board);
        }
        else
        {
            //add token to the board
            player |= 1<<(board.height[Column] + Column*7);

            //set the values
            board.move%2 ? board.Player1 = player : board.Player2 = player;
            board.move++;
            board.height[Column]++;
            printBoard(board);
            //check if the player won the game
            if(checkIfWon(player))
            {
                std::cout<<"Congradulation "<<(board.move%2 ? "Player 2 " : "Player 1 ")<<" Has won, please brag about it to everyone because your better than them!!!!!";
            }
            else
            {
                UserPrompt(board);
            }

        }
    }

}


void printBoard(uint64_t board) {
    std::cout << "THE BIT SET VALUE for this number is " << board << std::endl;
    auto set = std::bitset<64>(board);
    for (int i = 6; i >= 0; i--) {
        int startVal = i - 7;
        for (int j = 0; j < 9; j++) {
            startVal += 7;
            std::cout << i + j * 7 << ": " << set[i + j * 7] << "\t";
        }
        std::cout<<std::endl;
    }
}
void printBoard(GameBoard& board) {
    std::cout << "This is the current layout of the game board"<<std::endl;
    auto dataSet1 = std::bitset<64>(board.Player1);
    auto dataSet2 = std::bitset<64>(board.Player2);
    for (int i = 6; i >= 0; i--) {
        for (int j = 0; j < 9; j++) {
            int currentBit = i + j * 7;
            char token = '-';
            if(dataSet1[currentBit]) token = 'X';
            else if(dataSet2[currentBit]) token = 'O';
            std::cout << i + j * 7 << ": " <<token<< "\t";
        }
        std::cout<<std::endl;
    }
}
void printBoard(uint64_t board, uint64_t board2)
{
    std::cout<<"THE BIT SET VALUE for this number is "<< board<<std::endl;
    auto set = std::bitset<64>(board);
    auto set2 = std::bitset<64>(board2);
    for(int i =6 ;  i >= 0; i--)
    {
        int startVal = i - 7;
        for(int j = 0 ; j < 9; j++)
        {
            startVal += 7;
            std::cout<<i+j*7<<": "<< set[i + j*7]<<"\t";
        }
        //if(startVal == 56) std::cout<<startVal+7<<": "<<set[9];


        startVal = i - 7;
        std::cout<<"  ";
        for(int j =0; j < 9; j++)
        {
            startVal += 7;
            std::cout<<i+j*7<<": "<< set[i + j*7]<<"\t";
        }
        //if(startVal == 56) std::cout<<startVal+7<<": "<<set2[9];
        std::cout<<"\n";

    }

}

bool checkIfWon(BitBoard board)
{
    //check the diagonal /
    if(board & (board>>8) & (board>>16) & (board >>24)) return true;
    //check the diagonal the other direction
    if(board & (board>>6) & (board>>12) & (board >> 18)) return true;
    //check horizontal
    if(board & (board>>1) & (board>>2) & (board >> 3)) return true;
    if(board & (board>>7) & (board>>14) & (board >>21)) return true;

    //if none of the above conditions are true then you have not won the game you loser

    return false;

}

