//
// Created by Mark Minch  on 6/14/22.
//

#include "BitBoard.h"


namespace Game {

    //hide implementation details about how the program run from users if I was to compile it to an intermediate file option
    bool checkIfWon(const BitBoard board);

    void UserPrompt(GameBoard &board);

    void addToken(GameBoard &board);

    void printBoard(const BitBoard board);

    void printBoard(const GameBoard &board);

    void printBoard(const BitBoard board, const BitBoard board2);



    inline void UserPrompt(GameBoard &board) {


        //select the column that you want to use for the game
        char userInput = 'q';
        std::cout << "User " << (board.move % 2 ? "Player 2" : "Player 1")
                  << " input a value between 1 and 7 to select where to place a token or quit the game with (q)"
                  << std::endl;
        std::cin >> userInput;
        if (userInput == 'q') {
            std::cout << "You have Quit and forfeit the game so " << (board.move % 2 ? "Player 1" : "Player 2")
                      << " Wins by default " << std::endl;
            board.state = Close;
        }
        else if (userInput >= '1' && userInput <= '7') {
            //check if the column that it was put in is full
            int variable = (int) (userInput - '0') - 1;
            board.moves[board.move] = variable;
            //addToken(board);
            board.state = addToken;
        }


    }

    inline void addToken(GameBoard &board) {
        int Column = board.moves[board.move];
        bool winState = false;
        if (board.height[Column] > 5) {
            //the column is full, so you can not place an ime there
            std::cout << "<------ERROR------>\nThe column that you place that token in is full try a different number"
                      << std::endl;
        }
        else {
            //add token to the board
            BitBoard player;
            board.move % 2 ? player = board.Player2 : player = board.Player1;
            player |= 1 << (board.height[Column] + Column * 7);

            //set the values
            board.move % 2 ? board.Player2 = player : board.Player1 = player;
            board.move++;
            board.height[Column]++;
            printBoard(board);
            //check if the player won the game
            winState = checkIfWon(player);

        }
        if (winState) {
            std::cout << "Congratulation " << (board.move % 2 ? "Player 1 " : "Player 2 ")
                      << " Has won, please brag about it to everyone because your better than them!!!!!";
            board.state = Close;
        }
        else
        {
            board.state = UserPrompt;
        }
    }

    void Run(GameBoard &board)
    {
        board.state = UserPrompt;
        while(board.state != Close)
        {

            board.state(board);
        }
        board.state(board);
    }


    inline void printBoard(const BitBoard board) {
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

    inline void printBoard(const GameBoard &board) {
        std::cout << "This is the current layout of the game board" << std::endl;
        auto dataSet1 = std::bitset<64>(board.Player1);
        auto dataSet2 = std::bitset<64>(board.Player2);
        for (int i = 5; i >= 0; i--) {
            std::cout <<i+1<<"\t";
            for (int j = 0; j < 7; j++) {
                int currentBit = i + j * 7;
                char token = '-';
                if (dataSet1[currentBit]) token = 'X';
                else if (dataSet2[currentBit]) token = 'O';
                std::cout << "[" << token<<"]" << "\t";
            }
            std::cout << std::endl;
        }
        std::cout<<"\t 1\t 2\t 3\t 4\t 5\t 6\t 7"<<std::endl;
    }

    inline void printBoard(const BitBoard board, const BitBoard board2) {
        std::cout << "THE BIT SET VALUE for this number is " << board << std::endl;
        auto set = std::bitset<64>(board);
        auto set2 = std::bitset<64>(board2);
        for (int i = 6; i >= 0; i--) {
            int startVal = i - 7;
            for (int j = 0; j < 9; j++) {
                startVal += 7;
                std::cout << i + j * 7 << ": " << set[i + j * 7] << "\t";
            }
            //if(startVal == 56) std::cout<<startVal+7<<": "<<set[9];


            startVal = i - 7;
            std::cout << "  ";
            for (int j = 0; j < 9; j++) {
                startVal += 7;
                std::cout << i + j * 7 << ": " << set[i + j * 7] << "\t";
            }
            //if(startVal == 56) std::cout<<startVal+7<<": "<<set2[9];
            std::cout << "\n";

        }

    }

    inline bool checkIfWon(const BitBoard board) {
        //check the diagonal /
        if (board & (board >> 8) & (board >> 16) & (board >> 24)) return true;
        //check the diagonal the other direction
        if (board & (board >> 6) & (board >> 12) & (board >> 18)) return true;
        //check horizontal
        if (board & (board >> 1) & (board >> 2) & (board >> 3)) return true;
        if (board & (board >> 7) & (board >> 14) & (board >> 21)) return true;

        //if none of the above conditions are true then you have not won the game you loser

        return false;

    }
    void Close(GameBoard& board)
    {
        //this is mostly a dummy function but in the future I plan to have it hold information about closing files for user input and logging

    }

}