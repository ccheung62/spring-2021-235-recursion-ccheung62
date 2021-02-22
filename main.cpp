#include <iostream>
#include <unistd.h>

#include "n-queens.h"

/* This program gives the placement of queens in a given nxn grid so that no queens can attack one another */

int main (){
    // set the grid to be 4x4
    int n = 8;
    std::string** board;
    createBoard(board, n);
    int queen = 0;
    solve(board, n, 0, queen);
    //change everything thing other than a Q to . for aesthetics
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if(board[i][j] == "X"){
                board[i][j] = ".";
            }
            else{
                board[i][j] = "Q";
            }
        }
    }
    //prints the final solution of n-queens
    printBoard(board, n);
    std::cout << "This is the solution for n-queens with " << n << " x " << n << " grid" << std::endl;
    deleteBoard(board,n);
    return 0;
}