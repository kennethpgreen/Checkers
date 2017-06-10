/************************************
@author: kenneth green
@version: Checkers
@function: this will play a checkers game
@date: 5/11/15
***********************************/

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
//CREATE CONSTANT VARIABLES THAT WILL BE USED THROUGHOUT THE PROGRAM

const int ROW = 8;
const int COL = 8;
int turn = 1;     //if odd, turn is person 1, if even turn is person 2
int player1LostPieces = 0;    //increment each time player1 loses a piece
int player2LostPieces = 0;    //increment each time player2 loses a piece

//METHODS NEEDED
void setDefaultGrid(char [ROW][COL]);   //sets the grid to a normal starting
void askLocation(string, int&,int&);
void askDestination(string, int&, int&);
void printMoves(int [2][50]);

///THINGS TO ADD/FIX: king function, double jump



/** GRID------------------------------------------------------------
Different characters will be added to the grid at different locations
*/
class Grid
{
private:
    char grid[ROW][COL];

public:
    Grid()
    {
        //creates a null grid
        for (int i= 0; i < ROW; i++)
        {
            for (int j=0; j<COL; j++)
            {
                grid[i][j] = '-';
            }
        }
        setDefaultGrid(grid);
    }
    void print()
    {
        //prints the layout for a grid
        for (int i= -1; i < ROW; i++)
        {
            cout << i+1 << "    ";
            for (int j=0; j<COL; j++)
            {
                if (i == -1)
                {
                    cout << j+1;
                }
                else
                {
                    cout << grid[i][j];
                }
            }
            if (i == -1)
            {
                cout << endl;
            }
            cout << endl;
        }
        cout << "(x is vertical and y is horizontal)" << endl;
    }
    ///defines class methods
    void movePiece(int, int, int, int);         //old location and new location
    void capture(int, int);
    bool isPieceGood(int, int);
    bool canMove(int, int, int, int);   //old location and new location
};



/** MAIN------------------------------------------------------------
*/
/**
    @main: this will start the checkers game and prompt the user for essential data
    the main method will call other functions to operate the program
*/
int main()
{
    //ask the user for the names of the players
    string namePlayer1 = "";
    string namePlayer2 = "";
    cout << "Hello! Please enter player 1's name and player 2: " << endl;
    cout << "Player 1: ";
    cin >> namePlayer1;
    cout << "Player 2: ";
    cin >> namePlayer2;
    //start the game:
    cout << "Let's start the game!" << endl << "--------------------------------" << endl;

    //create a grid and show the grid
    Grid myGrid;
    myGrid.print();
    int player1Moves[2][50];        //allow 50 turns each
    int player2Moves[2][50];        //allow 50 turns each
    bool continueGame = true;       //this means that there has been no winner yet

    //create a while loop to keep track until the game ends or move "books" are too large
    while(turn < 100 && continueGame)
    {
        ///player 1s turn--
        ///1. ask for a piece
        int xOfPiece = -1;
        string nameOfPlayer;
        int yOfPiece = -1;
        if (turn % 2 ==1 )
        {
            nameOfPlayer = namePlayer1;
        }
        else if (turn % 2 == 0)
        {
            nameOfPlayer = namePlayer2;
        }
        START:askLocation(nameOfPlayer, xOfPiece, yOfPiece);   //adds info to the locations, also checks to make sure it's valid
        bool validPiece;
        validPiece = myGrid.isPieceGood(xOfPiece, yOfPiece);
        while (!validPiece)
        {
            cout << "Enter a valid piece:" << endl;
            askLocation(nameOfPlayer, xOfPiece, yOfPiece);   //adds info to the locations, also checks to make sure it's valid
            validPiece = myGrid.isPieceGood(xOfPiece, yOfPiece);
        }
        ///2. ask for a desired location
        int xMove = -1;
        int yMove = -1;
        askDestination(nameOfPlayer, xMove, yMove);      //adds the desired move location to the variables

        ///3. check if the location is a valid location
        bool validLocation;                 //if valid then true, if not valid, false
        int timesTried = 0;
        validLocation = myGrid.canMove(xOfPiece, yOfPiece, xMove, yMove);
        timesTried++;
        while (!validLocation && timesTried <=2)
        {
            cout << "Enter a valid location:" << endl;
            askDestination(namePlayer1, xMove, yMove);      //adds the desired move location to the variables
            validLocation = myGrid.canMove(xOfPiece, yOfPiece, xMove, yMove);
            timesTried++;
        }
        if (timesTried == 3)
        {
            timesTried =0;
            cout << "Too many invalid locations. Re-enter a piece: " << endl;
            goto START;
        }

        ///4. if it is, move the piece there and change the book
        myGrid.movePiece(xOfPiece, yOfPiece, xMove, yMove);
        system("CLS");
        myGrid.print();

        ///5. end the turn and pass it over to the other player to go

        if (turn % 2 ==1 )
        {
            player1Moves[0][turn/2] = xMove;
            player1Moves[1][turn/2] = yMove;
        }
        else if (turn % 2 == 0)
        {
            player2Moves[0][turn/2] = xMove;
            player2Moves[1][turn/2] = yMove;
        }
        if (player1LostPieces == 8)
        {
            continueGame = false;
        }
        if (player2LostPieces == 8)
        {
            continueGame = false;
        }
        turn++;

        //player 2s turn----
    }
    system("CLS");
    if (player1LostPieces > player2LostPieces)
    {
        cout << "Player 2 won!" << endl;
    }
    else if (player2LostPieces > player1LostPieces)
    {
        cout << "Player 1 won!" << endl;
    }
    else
    {
        cout << "TIE!!" << endl;
    }
    cout << "Here are the list of moves: " << endl;
    printMoves(player1Moves);
    printMoves(player2Moves);
    return 0;
}




/** setDefaultGrid------------------------------------------------------------
*************************************************
* @setDefaultGrid: this will set the grid to it's starting info
* @param: the grid
* @post: the grid will have the correct grid in it
*
*************************************************/
void setDefaultGrid(char grid [ROW][COL])                //sets the grid to default settings
{
    //creates the grid by determining where there should be x's and where there should be o's
    for (int i=0; i < ROW; i++)
    {
        for (int j = 0; j<COL; j++)
        {
            if (i %2 == 0)
            {
                if (j%2 == 1)
                {
                    if (i < 3)
                    {
                        grid[i][j] = 'o';
                    }
                    else if (i>4)
                    {
                        grid[i][j] = 'x';
                    }
                }
            }
            if (i%2 == 1)
            {
                if (j%2 == 0)
                {
                    if (i < 3)
                    {
                        grid[i][j] = 'o';
                    }
                    else if (i>4)
                    {
                        grid[i][j] = 'x';
                    }
                }
            }
        }
    }

    //Player 2

}




/** askLocation--------------------------------------------------
**************************************************
* @askLocation: this will ask for a location
* @param: the name of the user
* @post:the x and the y variables will be changed byREF
*
*************************************************/
void askLocation(string name, int& x,int&y)                            //finds the piece at location (X, Y)
{
    cout << name << " enter a piece to move." << endl;
    cout << "X: ";
    cin >> x;
    while (x<=0 || x >8)
    {
        cout << "Enter a valid X: ";
        cin >> x;
    }
    cout << "Y: ";
    cin >> y;
    while (y<=0 || y >8)
    {
        cout << "Enter a valid Y: ";
        cin >> y;
    }
}




/** askDestination---------------------------------------------
**************************************************
* @askDestination: this will ask for a destination
* @param: the name of the user
* @post:the x and the y variables will be changed byREF
*
*************************************************/
void askDestination(string name, int&x, int&y)                        //gets the new destination for piece at location (X, Y)
{
    cout << name << " where would you like to move?" << endl;
    cout << "X: ";
    cin >> x;
    while (x<=0 || x >8)
    {
        cout << "Enter a valid X: ";
        cin >> x;
    }
    cout << "Y: ";
    cin >> y;
    while (y<=0 || y >8)
    {
        cout << "Enter a valid Y: ";
        cin >> y;
    }
}




/** Grid::isPieceGood------------------------------------
**************************************************
* @isPieceGood: this will see if the piece picked is a valid piece
* @param: the x and y of the piece chosen
* @post:none
* @return: a boolean value with true or false
************************************************/
bool Grid::isPieceGood(int x, int y)
{
    char character = grid[x-1][y-1];
    if (character == '-')
    {
        return false;
    }
    else
    {
        if (toupper(character) == 'O' && turn %2==1)
        {
            return true;
        }
        else if (toupper(character) == 'X' && turn%2==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}





/** Grid::canMove-------------------------------------
**************************************************
* @canMove: this will see if the user can move
* @param: x and y of the piece; x and y of the move location
* @post: none
* @return: true or false about whether the piece can move
*************************************************/
bool Grid::canMove(int xLocation, int yLocation, int xMove, int yMove)          //check if the new destination is a valid location
{
    if (turn %2 == 1 || isupper(grid[xLocation-1][yLocation-1]) )
    {
        int xPos = xLocation+1;
        int xPos2 = xLocation+2;
        int yPos1 = yLocation-1;
        int yPos2 = yLocation+1;
        if (xMove == xPos)
        {
            if ((yMove) == yPos1 && grid[xPos-1][yPos1-1] == '-')   //empty space
            {
                return true;
            }
            else if ((yMove) == yPos2 && grid[xPos-1][yPos2-1] == '-')
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (xMove = xPos2 )
        {
            if ((yMove) == (yPos1-1) && grid[xPos-1][yPos1-1] == 'x')  //the user is trying to capture a piece
            {
                if (grid[xPos][yPos1-2] == '-')
                {
                    capture(xPos, yPos1);          ///FIX THIS!
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if((yMove) == (yPos2+1) && grid[xPos-1][yPos2-1] == 'x')   //the user is trying to capture a piece
            {
                if (grid[xPos][yPos2] == '-')
                {
                    capture(xPos, yPos2);          ///FIX THIS!
                    return true;
                }
                else
                {
                    return false;
                }
            }

        }


    }

    if (turn %2 == 0 || isupper(grid[xLocation-1][yLocation-1]))
    {
        int xPos = xLocation-1;
        int yPos1 = yLocation-1;
        int yPos2 = yLocation+1;
        int xPos2 = xLocation-2;

        if (xMove == xPos)
        {
            if ((yMove) == yPos1 && grid[xPos-1][yPos1-1] == '-')
            {
                return true;
            }
            else if ((yMove) == yPos2 && grid[xPos-1][yPos2-1] == '-')
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (xMove == xPos2)
        {
            if((yMove) == (yPos1-1) && grid[xPos-1][yPos1-1] == 'o')
            {
                if (grid[xPos-2][yPos1-2] == '-')
                {
                    capture(xPos, yPos1);          ///FIX THIS!
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if ((yMove) == (yPos2+1) && grid[xPos-1][yPos2-1] == 'o')
            {
                if (grid[xPos-2][yPos2] == '-')
                {
                    capture(xPos, yPos2);          ///FIX THIS!
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

}





/** Grid::movePiece----------------------------------------
**************************************************
* @movePiece: this will move the piece
* @pre: canMove was true
* @param: x and y of the piece; x and y of the move location
* @post: the piece is moved in the grid
*
*************************************************/
void Grid::movePiece(int xLocation, int yLocation, int xMove, int yMove)        //moves the piece if it is valid, calls the capture method if needed
{
    if (turn %2 == 1)
    {
       if (xMove == 8 ||  grid[xLocation-1][yLocation-1] == 'O')
       {
           grid[xMove-1][yMove-1] = 'O';
       }
       else
       {
           grid[xMove-1][yMove-1] = 'o';
       }
    }


    else if (turn %2 == 0 || grid[xLocation-1][yLocation-1] == 'X')
    {
        if (xMove == 1)
       {
           grid[xMove-1][yMove-1] = 'X';
       }
       else
       {
           grid[xMove-1][yMove-1] = 'x';
       }
    }
    grid[xLocation-1][yLocation-1] = '-';


}




/** Grid::capture-------------------------------------
**************************************************
* @capture: this will capture a piece
* @pre: capture was called when a piece moved two vertical spaces
* @param: x and y of the piece
* @post: a piece is captured and the counter is incremented
*
*************************************************/
void Grid::capture(int xPos, int yPos)                  //takes away the value in which the piece is hopping over incrementing static variables
{
    grid[xPos-1][yPos-1] = '-';
    if (turn %2 == 1)
    {
       player2LostPieces++;
    }

    else if (turn %2 == 0)
    {
       player1LostPieces++;
    }                                                      //captures also checks if there are other possible captures,
                                                        //if so, the user will capture those pieces
}





/** printMoves---------------------------------------------
**************************************************
* @printMoves: this will print all of the moves of the user
* @param: the move book
* @post: the move book is printed out in a formatted chart for the user
*
*************************************************/
void printMoves(int moves[2][50])
{
    cout << "X,Y" << endl;
    for (int i=0; i<50; i++)
    {
        for(int j=0;j<2;j++)
        {
            cout << moves[j][i] << " " << endl;
        }
    }

}
