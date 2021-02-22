#include <iostream>
#include <unistd.h>

/* This function dynamically create a 2D array to represent the nxn grid
    An additional row is added to the array to store the placement of the queens */
void createBoard(std::string** board, int n){
    for (int i=0; i<n; i++){
        board[i] = new std::string[n];
        for (int j=0; j<n; j++){
            board[i][j] = ".";
        }
    }
    //additional row to store the placement of each queen
    board[n] = new std::string[n*2]; 
}

/* This function prints out the grid with ANSI escape sequence */
void printBoard(std::string** board, int n){
    std::cout << "[0;0H\n";
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    usleep(300000);
}

/* This function mark all the places that a queen can attack at location board[row][col] */
void mark(std::string** board, int n, int row, int col, int &count, int queen){
    //base case: stop when the function calls out of bounds and return back 
    //to the original position to continue in another direction
    if (row < 0 || row >= n || col < 0 || col >= n){
        //retrieve the intial placement of the queen that is being marked
        row = std::stoi(board[n][queen*2]);
        col = std::stoi(board[n][(queen*2)+1]);
        //count is used to switch the direction the recursive call will be going
        count++;
    }
    else if (board[row][col] == "."){
        board[row][col] = "X";
    }
    //goes through every direction that the queen can attack until out of bound
    switch(count){
        case 0: 
            mark(board, n, row+1, col+1, count, queen);
            break;
        case 1:
            mark(board, n, row+1, col-1, count, queen);
            break;
        case 2:
            mark(board, n, row-1, col-1, count, queen);
            break;
        case 3:
            mark(board, n, row-1, col+1, count, queen);
            break;
        case 4:
            mark(board, n, row, col+1, count, queen);
            break;
        case 5: 
            mark(board, n, row, col-1, count, queen);
            break;
        case 6:
            mark(board, n, row+1, col, count, queen);
            break;
        case 7:
            mark(board, n, row-1, col, count, queen);
            break;
        default:
            return;
    }
}

/* This function checks if the specified place could be attacked by any queen on the grid */
bool checkQ(std::string** board, int n, int row, int col, int &queen){
    //clears out the board
    for (int a=0; a<n; a++){
        for(int b=0; b<n; b++){
            board[a][b] = ".";
        }
    }
    //mark all the attackable place that the placed queens have
    for (int q=0; q<queen; q++){
        int r = std::stoi(board[n][q*2]);
        int c = std::stoi(board[n][(q*2)+1]);
        int count = 0;
        mark(board, n, r, c, count, q);
        board[r][c] = "Q";
    }
    //check if at the specified location that place could be attack by a queen
    if (board[row][col] != "X"){
        return true;
    }
    else {
        return false;
    }
}

/* This function finds the correct placement of each queen with recursion*/
void solve(std::string** board, int n, int col, int &queen){
    printBoard(board, n);
    //base case: if reached out of bound or enough queen is correctly placed, then stop
    if (col >= n || queen >=n){
        return;
    }
    //check the grid vertically for possible queen placement
    for(int i=0; i<n; i++){
        //check if this location is attacked by a queen
        if (checkQ(board, n, i, col, queen)){
            //record the location if the queen could be placed
            board[n][queen*2] = std::to_string(i);
            board[n][(queen*2)+1] = std::to_string(col);
            queen++;
            //check if the next column could place a queen too until it goes out of bound
            solve(board, n, col+1, queen);
            //if it went out of this recursive call then there is no possible way to 
            //achieve a solution with this queen replacement

            //check if there is enough queen already
            if (queen >= n){
                return;
            }
            //get rid of this queen placement because it led to a dead end
            queen--;
        }
    }
    return;
}
/* This function deletes the dynamically created 2D array used throughout*/
void deleteBoard(std::string** board, int n){
    for(int i; i<=n; i++){
        delete[] board[i];
    }
}
