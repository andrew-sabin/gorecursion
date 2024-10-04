#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <array>

using namespace std;


const int BOARD_SIZE = 9;
char savedBoard[BOARD_SIZE][BOARD_SIZE];



/*
 * void setBoard(string &s, char c[][]
 * Sets the Go Board based on the string of characters read in from the text file
 * sets each piece into a place in the two 2d array.
 *
 * string &s : the address of the text file string being read from
 * c[][] : the board being created by the text file
 */
void setBoard(const string &s, char c[BOARD_SIZE][BOARD_SIZE]){
    int count = 0;
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            c[row][col] = s[count];
            count++;
        }
    }
}

/*
 * Removes the extra spaces in the string containing the results from reading the go.txt file.
 *
 * String s = String of the read in text file.
 *
 */
string spaceRemover(string s){
    string::size_type findSpace = s.find("  ");
    for (int i = 0; i < static_cast<int>(s.size()); i++){
        if(s[i+1]!= 'b' && s[i+1]!='w' && s[i+1]!='-'){
            s.replace(findSpace+i,2,"");
        }
    }
    return s;
}

/*
 * Prints the current Go Board onto the command console.
 *
 * current_board[][] = the current go board selected to be printed onto the console.
 */

void printBoard(char current_board[BOARD_SIZE][BOARD_SIZE]){
    cout << "  ";
    for(int c = 0; c < BOARD_SIZE; c++){
        cout << c << " ";
    }
    cout <<endl;
    for(int row = 0; row < BOARD_SIZE; row++){
        cout << row << " ";
        for(int col = 0; col < BOARD_SIZE; col++){
            cout << current_board[row][col] << " ";
        }
        cout <<endl;
    }
    cout << endl;
    cout << endl;
}

/*
 * Copies one Go board onto a new copy.
 *
 * sourceBoard[][] = The original board being copied onto another board.
 *
 * newCopy[][] = The new copy of the original board.
 */

void copyBoard(char sourceBoard[BOARD_SIZE][BOARD_SIZE], char newCopy[BOARD_SIZE][BOARD_SIZE]){
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int c = 0; c < BOARD_SIZE; c++){
            newCopy[row][c] = sourceBoard[row][c];
        }
    }
}

/*
 * Recurses through a Go board and checks to see how many pieces are in a group.
 * Goes through each individual piece and continues recursing through the list until they come across a piece that isn't the color
 * selected by the user, or has been checked already.
 *
 * sourceBoard[][] = Go boards that is being recursed through.
 * moveRow = Row being examined by the function.
 * moveCol = Column being examined by the function.
 * color = The piece color that it is selected by the user from the given coordinates.
 */

int findGroup(char sourceBoard[BOARD_SIZE][BOARD_SIZE], int moveRow, int moveCol, char color){
    if(moveRow < 0 || moveCol < 0 || moveRow >= BOARD_SIZE || moveCol >= BOARD_SIZE){
        return 0;
    }
    if(sourceBoard[moveRow][moveCol] == '-' || sourceBoard[moveRow][moveCol] == 'B' || sourceBoard[moveRow][moveCol] == 'W'){
        return 0;
    }

    char oppositeColor;
    if(color == 'w'){
        oppositeColor = 'b';
    }
    else if(color == 'b'){
        oppositeColor = 'w';
    }
    else{
        return 0;
    }
    if(sourceBoard[moveRow][moveCol] == oppositeColor){
        return 0;
    }
    char updatedBoard[BOARD_SIZE][BOARD_SIZE];
    copyBoard(sourceBoard,updatedBoard);
    if(sourceBoard[moveRow][moveCol] == color){
        if (color == 'b'){
            updatedBoard[moveRow][moveCol] = 'B';
        }
        else if (color == 'w'){
            updatedBoard[moveRow][moveCol] = 'W';
        }
    }
    copyBoard(updatedBoard,savedBoard);
    //printBoard(savedBoard);
//  Recurses through the board in the ordered directions right,left,down, up
//  Saves the values for each direction value, where the totalGroup is equal to all direction recursions
    int moveRight = findGroup(savedBoard,moveRow,moveCol+1,color);
    int moveLeft = findGroup(savedBoard,moveRow,moveCol-1,color);
    int moveDown = findGroup(savedBoard,moveRow+1,moveCol,color);
    int moveUp = findGroup(savedBoard,moveRow-1,moveCol,color);
    int totalGroup = moveRight + moveLeft + moveDown + moveUp;
    return 1 + totalGroup;
}

/*
 * Finds the liberties in a given group, where it will continue to recurse through a the board until the board space doesn't have an open spot
 * or the space doesn't represent the user's selected color.
 *
 * sourceBoard[][] = Go board being examined by the function.
 * moveRow = current row being examined by the function.
 * moveCol = current column being examined by the function.
 *
 * visitedBoard[][] = Checks if the board area has been visited. Does not need to be copied like the sourceBoard since when recursion it occurs
 * the checked spaces have been set in cases that they have been already checked.
 */

int findLiberties(char sourceBoard[BOARD_SIZE][BOARD_SIZE], int moveRow, int moveCol, char color, int visitedBoard[BOARD_SIZE][BOARD_SIZE]){
    if(moveRow < 0 || moveCol < 0 || moveRow >= BOARD_SIZE || moveCol >= BOARD_SIZE){
        return 0;
    }
    if(visitedBoard[moveRow][moveCol] == 1){
        return 0;
    }

    visitedBoard[moveRow][moveCol] = 1;
    char updatedBoard[BOARD_SIZE][BOARD_SIZE];
    copyBoard(sourceBoard,updatedBoard);
    if(updatedBoard[moveRow][moveCol] == '-'){
        updatedBoard[moveRow][moveCol] = '*';
        copyBoard(updatedBoard,savedBoard);
        //printBoard(savedBoard);
        return 1;
    }
    if(updatedBoard[moveRow][moveCol] != color){
        return 0;
    }
    int moveRight = findLiberties(savedBoard,moveRow,moveCol+1,color, visitedBoard);
    int moveLeft = findLiberties(savedBoard,moveRow,moveCol-1,color, visitedBoard);
    int moveDown = findLiberties(savedBoard,moveRow+1,moveCol,color, visitedBoard);
    int moveUp = findLiberties(savedBoard,moveRow-1,moveCol,color, visitedBoard);
    int totalLiberties = moveRight + moveLeft + moveUp + moveDown;
    return totalLiberties;

}

int main()
{
    // Reading from go.txt and setting the values into a string value
    string currBoard;
     ifstream Inboard;
     Inboard.open("go.txt");
     while (!Inboard.eof()){
         string fBoard;
         getline(Inboard,fBoard);
         if (Inboard.fail())
             break;
        currBoard += fBoard;
     }
     char color = ' ';

     currBoard = spaceRemover(currBoard);
     char fullBoard[BOARD_SIZE][BOARD_SIZE];
     setBoard(currBoard,fullBoard);
     printBoard(fullBoard);
     int x = 0;
     int y = 0;
     cout << "Please set your row and column values to see your available liberties." << endl;
     cin >> x >> y;
     color = fullBoard[x][y];
     int numberOfGroups = findGroup(fullBoard, x,y,color);
     cout << "-------------------------------" << endl;
     color = toupper(color);
     copyBoard(savedBoard,fullBoard);
     int checkBoard[BOARD_SIZE][BOARD_SIZE] = {0};

     int numberOfLiberties = findLiberties(fullBoard,x,y,color, checkBoard);
     copyBoard(savedBoard, fullBoard);
     printBoard(fullBoard);

     cout << "You have : " << numberOfGroups << " stone(s) in your group."<< endl;
     cout << "You have : " << numberOfLiberties << " possible liberties." << endl;

}
