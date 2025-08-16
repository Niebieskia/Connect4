#include "c4lib.h"
#include <iostream>
using namespace std;

// Prototype internal helper functions
/**
 * @brief returns the smallest y coordinate that is BLANK in 
 *        column x or -1 if no location is BLANK
 */
int findYValue(BoardValue** board, int ydim, int x);


// ------------------------------------------------------------
// Global variabes - the ONLY we allow in this program

// converts integer player value: 0 or 1 to appropriate enum
enum BoardValue playerToValue[2] = {RED, YELLOW};

// ----------------------------------------------------------------------


// Helper function 
int findYValue(BoardValue** board, int ydim,  int x) //pointer to pointers
{
// You complete!
//put in x and find where it is and why - going over board
//some operation with board //return integer - finding some integer to return
 for(int i=0; i<ydim; i++){ //iterate through rows & column x to find first blank cell
  if(board[i][x] == BLANK){
    return i; //return first empty row
  }

 }
 return -1; //if no empty row return -1
}

BoardValue** allocateBoard(int ydim,  int xdim)
{
  // You complete!
  //allocate - initializing defining, creating board- return board - 
  //probably creating dynamic array to hold board and return it
  BoardValue** board = new BoardValue*[ydim]; //lists of lists
  for(int i=0; i<ydim;i++){//column
    board[i] = new BoardValue[xdim]; //allocate space for each
    //^more lists inside eacch bigger list 
    for(int j=0; j<xdim;j++){//row
      board[i][j] = BLANK; //initialize cell to blank circle
    }
  }
  return board; //return board

}
void deallocateBoard(BoardValue** board,  int ydim)
{
  // You complete!
  // delete board correctly - cleaning up mess 
  for(int i=0; i<ydim; i++){ //iterate through my lists row
    delete [] board[i]; //delete each housing lease whatever 
    //f^ree memroy in each row
  }
  delete[] board;  //free memory for row pointers

}

void printBoard(BoardValue** board,  int ydim, int xdim)
{
  // Complete - Do not alter
  const char* boardToString[] = { "\U000026ab", "\U0001F534", "\U0001F7E1" }; 
                                  //  "⚫",          "🔴",         "🟡"}
  for(int y = ydim-1; y >= 0; y--){ //for y dimension
    for(int x = 0; x < xdim; x++) { //for x 
      cout << boardToString[(int)board[y][x]] << " "; //printing out board
    }
    cout << endl;
  }
  cout << endl;
}

bool getNextHumanInput( 
  BoardValue** board, 
  int ydim,  int xdim, 
  int *y, int *x, 
  int currentPlayer)
{
  // You complete!
 //cin cout - put in variables
 //user input will be the column 1 integer
 int choice; 
 //cout << "placeholder input: ";
 cin >> choice; 
  if(!(choice >= 0 && choice <= xdim-1)){ //if invalid
    return true; //retry
  }
  int row = findYValue(board, ydim, choice); //found row 
  if (row == -1){ //if no available row
    return true; //retry
  }
  if (currentPlayer == 0){ //place red for player 0 and yello for 1
    board[row][choice] = RED;
  }
  else {
    board[row][choice] = YELLOW; 
  }

  //update coordinates where piece is placed
  *y = row; //integer at this address y = row
  *x = choice;

  return false; //placed a piece successfully
  
  

}

bool hasWon(
  BoardValue** board,
  int ydim,  int xdim,
  int sy, int sx,
  int currentPlayer)
{
  // Keep, modify, or delete these as you desire
  const int NDIRS=8;
  const int yDirDelta[NDIRS] = {+1,  0, +1, +1, -1, +1, +1, -1};
  const int xDirDelta[NDIRS] = { 0, +1, -1, +1, +1, -1, +1, -1};
  // You complete!
//are there 4 in a row? 
//loop over board and check if winning conditions
//get point 
  // check left, right, up, down, diagonal (->, ^, v, <-)
  //if point has 4 in those directions then whoever current player is wins
  
  //int directions[NDIRS] = {(+1, 0), (-1, 0), (0, +1), (0, -1)} //right, left, up, down
  int directionsX[NDIRS] = {+1, -1, 0, 0, +1, -1, +1, -1};
  int directionsY[NDIRS] = {0, 0, +1, -1, -1, +1, +1, -1};

  int currentPiece = playerToValue[currentPlayer]; //get current player piece (r or y)
  
  //loop over all cells
  for (int i=0; i <xdim;i++){ //iterate through column
    for(int j=0; j<ydim; j++){ //loop through row
      //cout << "Starting from: ( " << j << ", " << i << ")" << endl;
      if(board[j][i] == currentPiece){ //going over entire board if its equal to current player color
      //check all 8 directions
        cout << "\tcurrent piece matches current player" << endl;
        for(int dir=0; dir < NDIRS; dir++){ //dir=0 one direction dir=1 new direction
          int deltaX = directionsX[dir];
          int deltaY = directionsY[dir];

          int count = 1; //count current pieces
          cout << "\tTrying direction with dy, dx = " << deltaY << "," << deltaX << endl;          
          for( int k=1; k<4;k++){ //check 3 cells next to piece in current directions
            //if i=1 j=1 dir=0 k=1
            //if deltaX == dir[0](+1)
            //deltaY == dir[0](0)
            int newX = i+deltaX*k; //1
            int newY = j+deltaY*k; //0
            cout << "\tExamining newY,newX = " << newY << "," << newX << endl;          

            
            //cout << "newx: " << newX << ", newY: " << newY << endl;
            //int new_column = i+xDirDelta[dir] * k; //new column index
            //int new_row = j+yDirDelta[dir] * k; //new row index
          //check if new coords are iwthin boundaries
            if(!((newX >= 0) && (newX < xdim) && (newY >= 0) && (newY < ydim))){ //
              cout << "\tout of bounds...breaking" << endl;
              break;
            }


          //check if not matching
          //cout << newX << ", " << newY << endl;

         // cout << "value returned by board[newx][newy]" << board[newY][newX] << ", current piece = "
         // << currentPiece << endl;
            if (board[newY][newX] != currentPiece){
              cout << "\tPiece doens't match...breaking" << endl;
              break;
            }
            count++; 
            cout << "\tPiece does match...inc. count to " << count << endl;
          }
          //for(int k=1; k<4;k++){
          //  int newX = i - deltaX * k;
          //  int newY = j-deltaY*k;
          //}
         // cout << "count: " << count <<endl; 
          if (count >= 4) { //if 4 or more consecutive pieces found match
          //  cout << "return true" ;
            return true; //player wins
          }
        }
      }
    }
  } 
  //cout << "return false";
  return false; // if no 4 pieces aroe found (no win)
}
 



bool isDraw(
  BoardValue** board,
  int ydim,  int xdim)
{
  // You complete!
  //if board is full  - no blanks then return true 
  //if not return false
  //iterate through board
  for(int i=0; i<xdim;i++){
    if (board[ydim-1][i]==BLANK) { //check top row only
      return false; //not full
    }
  }
  return true; //no empty spaces, game draw
}




bool getUserAIInput(
  BoardValue** board, 
  int ydim,  int xdim, 
  int *y, int *x,
  int currentPlayer)
{
  // You complete!
  // Check if the current player can win
  //play move- check if it can win haswon- return
  //check if current player can win
  for(int i=0; i<xdim; i++){//list of moves are columns
  
    int row = findYValue(board, ydim, i); //find available row
    if(row == -1){
      continue; //means you can't play the move in the full column
    }
    //play tile
    board[row][i]=playerToValue[currentPlayer];//gives color of current player to board
    if(hasWon(board, ydim, xdim, row, i, currentPlayer)){
      *y = row;
      *x = i; //played the move
      return false; //no error
    }
    board[row][i] = BLANK; //revert the move if no win
  }

  // Check if we need to block 
  //  We can greedily play the first blocking location since
  //  if they can win in multiple ways it does not matter which
  //  we choose.

  //check if the other player can win - use same logic, except if other player can win then 
  //set board at row and column == our piece - determine opponents piece- have them play all poss moves
  //if its a winning move then we play our piece 
  
  int op; //determine opponent player number
  if(currentPlayer == BLANK){
    op = 1; 
  } 
  else {
    op = 0;
  }
  for(int column =0; column<xdim; column++){
    int row=findYValue(board, ydim, column); //find availablerow in the column
    if(row == -1){
      continue; //column full, skip
    }
    board[row][column] = playerToValue[op]; //place piece
    //check move result in win - should block
    if (hasWon(board, ydim, xdim, row, column, op)) {
      //block
      *y=row;
      *x = column; //block op's winning move
       board[row][column] = playerToValue[currentPlayer]; //placeo wn piece
      return false; //has blocked
    }
    board[row][column]=BLANK; //revert if no block
  }

  // Add any other logic for how to choose a location to play
  // if neither case above occurs

  //any blank 
  for(int column = 0; column <xdim; column++){
    int row = findYValue(board, ydim, column); //find next avail row
    if(row != -1) { //if there's space
      *y=row;
      *x = column; //save move coordinates
      board[row][column] = playerToValue[currentPlayer]; //place piece
      return false; //successfully moved
    }
  }
  return true; //if not- board is full
  
}

// Complete - Do not alter
bool getRandomAIInput(
  BoardValue** board, 
  int ydim, int xdim, 
  int *y, int *x,
  int currentPlayer)
{
  // Allocate variable size array (we don't know xdim when we compile)
  //possible places
  int* possible = new int[xdim*2]; //allocate array with possible spots
  int numX = 0; //keep track of possible columns
  bool error = true;
  // find all the possible columns with a blank
  for(int i = 0; i < xdim; i++){
    if(board[ydim-1][i] == BLANK){
      possible[numX++] = i; //add valid columsn to array
    }
  }
  // If at least 1 column has a blank
  //choose 1 column w a spot
  if(numX != 0){
    // Choose one column
    for(int i=0; i<numX; i++){
      *x =possible[i]; //x val = possible index 
      *y =findYValue(board, ydim, *x);  // y val = y value

      if(hasWon(board, ydim, xdim, *y, *x, currentPlayer)){ //if has won
        board[*y][*x] = playerToValue[currentPlayer]; //board(y, x) = player
        error = false; //get out cause someone won
        break;
      }
    }
    //check if op can win /block
    if(error){ 
      int op; //determine ops number
      if(currentPlayer == BLANK){
        op = 1; 
      } 
      else {
        op = 0;
      }
      for(int i=0; i<numX;i++){
        *x = possible[i];
        *y =findYValue(board, ydim, *x);
        if(hasWon(board, ydim, xdim, *y, *x, op)){
          board[*y][*x] = playerToValue[currentPlayer];
          error = false;
          break;
        }
      }
    }
    if(error) { //no winning - choose other valid option
      *x = possible [rand() % numX]; //randomly choose valid column
      *y = findYValue(board, ydim, *x); //find corresponding row
      board[*y][*x] = playerToValue[currentPlayer];
      error = false;
    }
  }
  delete[] possible; //clean up memory
  return error; //return true if not valid move was made
  
}

//Ai needs to be able to block, check if they can win, 
