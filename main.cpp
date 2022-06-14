#include <iostream>
#include <bitset>
#include <string>



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
typedef  uint64_t BitBoard;

class GameBoard;

//create a state machine for containing the next game operation that is going to be done
typedef void(*GameState)(GameBoard&);

void StartGame(GameBoard& board);
//print out what the state is based on the function pointer that you have
void MakeMove(GameBoard&);
void PromptUser(GameBoard&);






struct GameBoard
{
    //initilize memory to prevent bad data on construction
    BitBoard Player1 = 0;
    BitBoard Player2 = 0;
    // will hold the current height we can place a token at for the player
    int height[6] = {0};

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

void StartGame(GameBoard& board)
{
    board.state = StartGame;
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
void printBoard(uint64_t board);
void printBoard(GameBoard& board);
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


//used for debug purposes


void printBitBoard(uint64_t board, uint64_t board2)
{
    /*
    for(int i =6 ;  i >= 0; i--)
    {
        int startVal = i - 7;
        for(int j =0; j < 9; j++)
        {
            startVal += 7;
            std::cout<<startVal<<" ";
        }
        if(startVal == 56) std::cout<<startVal+7;
        std::cout<<"\n";
    }
    std::cout<<std::endl;
     */
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

int main() {
    //working with bit boards
    /*
     * A bit board can be used to represent a board game board along with all possible states in a very low memory overhead syste
     * rather than using arrays of intergers we can just use bits instead and then use bitwise operations on it
     *
     */

    //A bit board is made up of two longs, to make sure that it is not compiler or os dependent what the memory looks like
    //I have opted to use an uint64_t
    uint64_t BitBoard = 0;
    uint64_t BitBoard2 = 2;
    /*
     * So I should be able to put a 1 down any row by listing the row 6 apart
     */

    /*
    char value;
    std::cin>>value;
    while(value != 'q') {

        BitBoard |= 1<<(int)(value - '0');
        auto Board3 = BitBoard ^ BitBoard2;
        printBitBoard(BitBoard, Board3);
        std::cin>>value;
    }
    */

    uint64_t vchar = 15;

    uint64_t vchar2 = 1;
    vchar2 = vchar2 << 7;
    vchar = vchar | vchar2 | vchar2<<7 | vchar2<<14 | vchar2<<21;


    for(int i = 0; i < 4; i++)
    {
        uint64_t board = vchar & (vchar >> 7);

        printBitBoard(vchar, board);
        vchar = board;

    }

    GameBoard board;
    UserPrompt(board);




    return 0;
}
