#include <iostream>
#include <unistd.h>

void createBoard(std::string** board, int n){
    for (int i=0; i<n; i++){
        board[i] = new std::string[n];
        for (int j=0; j<n; j++){
            board[i][j] = ".";
        }
    }
    board[n] = new std::string[4];
}

void printBoard(std::string** board, int n){
    std::cout << "[0;0H\n";
    std::cout << "  0 1 2 3 4 5 6" << std::endl;
    for(int i=0; i<n; i++){
        std::cout << i << " ";
        for (int j=0; j<n; j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    usleep(600000);
}

void mark(std::string** board, int n, int row, int col, int &count){
    if (row < 0 || row >= n || col < 0 || col >= n){
        row = std::stoi(board[n][0]);
        col = std::stoi(board[n][1]);
        count++;
        // std::cout << "count: " << count << std::endl;
        // return;
    }
    else if (board[row][col] == "."){
        board[row][col] = "X";
    }
    // else {
    //     board[row][col] = "X";
    //     for (int i=-1; i<2; i++){
    //         for (int j=-1; j<2; j++){
    //             std::cout << row << " += " << i << "   " << col << " += " << j << std::endl;
    //             mark(board, n, row+i, col+j, count);
    //             // count++;
    //             // break;
    //             // std::cout << "hits break" << std::endl;
    //         }
    //         // count = i;
    //         // count++;
    //     }
    // }
    // for (int i=0; i<n; i++){
    //     board[row][i] = "X";
    //     board[i][col] = "X";
    // }
    // for (int i=count-1; i<2; i++){
    //     for (int j=count-1; j<2; j++){
    //         std::cout << row << " += " << i << "   " << col << " += " << j << std::endl;
    //         mark(board, n, row+i, col+j, count);
    //         count++;
    //         // break;
    //         // std::cout << "hits break" << std::endl;
        
    //     count = i;
    //     count++;
    //     }
    // }
    // if (row < 0 || row > n-1 || col < 0 || col > n-1){
    //     return;
    // }
    // else {
    //     board[row][col] = "X";
    // }
    // std::cout << "count: " << count << std::endl;
    switch(count){
        case 0: 
            mark(board, n, row+1, col+1, count);
            break;
        case 1:
            mark(board, n, row+1, col-1, count);
            break;
        case 2:
            mark(board, n, row-1, col-1, count);
            break;
        case 3:
            mark(board, n, row-1, col+1, count);
            break;
        case 4:
            mark(board, n, row, col+1, count);
            break;
        case 5: 
            mark(board, n, row, col-1, count);
            break;
        case 6:
            mark(board, n, row+1, col, count);
            break;
        case 7:
            mark(board, n, row-1, col, count);
            break;
        default:
            return;
    }
    // std::cout << "currently at row: " << row << "   col: " << col << std::endl;
    // std::cout << "first recursive row: " << row << "  col: " << col << std::endl;
    // mark(board, n, row+1, col+1);
    // return;
    // std::cout << "sec recursive row: " << row << "  col: " << col << std::endl;
    // mark(board, n, row-1, col-1);
    // return;
    // std::cout << "third recursive row: " << row << "  col: " << col << std::endl;
    // mark(board, n, row+1, col-1);
    // return;
    // std::cout << "fourth recursive row: " << row << "  col: " << col << std::endl;
    // mark(board, n, row-1, col+1);
    // return;
    // std::cout << "fifth recursive row: " << row << "  col: " << col << std::endl;
    // mark(board, n, row, col+1);
    // std::cout << "six recursive row: " << row << "  col: " << col << std::endl;
    // mark(board, n, row+1, col);
    // std::cout << "seven recursive row: " << row << "  col: " << col << std::endl;
    // mark(board, n, row-1, col);
    // std::cout << "eight recursive row: " << row << "  col: " << col << std::endl;
    // mark(board, n, row, col-1);
}

void checkBoard(std::string** board, int n, int row, int col, bool &full){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (board[i][j] == "."){
                full = false;
                // std::cout << "inside the checkBoard I made the full bool false" << std::endl;
                return;
            }
        }
    }
} 

void solve(std::string** board, int n, int row, int col, int &queen, bool &full){
    printBoard(board,n);
    if (row < 0 || row >= n || col < 0 || col >= n){
        return;
    }
    else if (board[row][col] == "X"){
        board[row][col] = "~";
    }
    if (queen < n && board[row-1][col] != "Q" && board[row-1][col] != "~" && board[row][col] != "+"){
        solve(board, n, row-1, col, queen, full);
    }
    // std::cout << "row: " << row << "   col: " << col << std::endl;
    if (queen < n && board[row][col+1] != "Q" && board[row][col+1] != "~" && board[row][col] != "+"){
        solve(board, n, row, col-1, queen, full);
    }
    // std::cout << "row: " << row << "   col: " << col << std::endl;
    if (queen < n && board[row+1][col] != "Q" && board[row+1][col] != "~" && board[row][col] != "+"){
        solve(board, n, row+1, col, queen, full);
    }
    // std::cout << "row: " << row << "   col: " << col << std::endl;
    if (queen < n && board[row][col+1] != "Q" && board[row][col+1] != "~" && board[row][col] != "+"){
        solve(board, n, row, col+1, queen, full);
    }
    // std::cout << "Is it a dot " << (board[row][col] == ".") << std::endl;
    if (board[row][col] == "."){
        // std::cout << "queen: " << queen << std::endl;
        board[n][0] = std::to_string(row);
        board[n][1] = std::to_string(col);
        int count = 0;
        mark(board, n, row, col, count);
        board[row][col] = "Q";
        queen++;
        full = true;
        checkBoard(board, n, row, col, full);
        if (full && queen < n){
            std::cout << "wrong answer" << std::endl;
            return;
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(board[i][j] == "~"){
                    board[i][j] = "X";
                }
            }
        }
        //     return;
        // }
        // else{
        //     for(int i=0; i<n; i++){
        //         for(int j=0; j<n; j++){
        //             if(board[i][j] == "~"){
        //                 board[i][j] = "X";
        //             }
        //         }  
        //     }
        // }
        // printBoard(board, n);
        // if (full) {
        //     for(int i=0; i<n; i++){
        //         for (int j=0; j<n; j++){
        //             board[i][j] = ".";
        //         }
        //     }
        //     if (std::stoi(board[n][2])+1 > n){
        //         board[n][2] = "0";
        //         board[n][3] = std::to_string(std::stoi(board[n][3])+1);
        //     }
        //     else {
        //         board[n][2] = std::to_string(std::stoi(board[n][2])+1);
        //     }
        //     row = std::stoi(board[n][2]);
        //     col = std::stoi(board[n][3]);
        //     queen = 1;
        //     board[row][col] = "Q";
        //     count = 0;
        //     mark(board, n, row, col, count);
        //     std::cout << "reseting the board with the starting point row: " << row << "  col: " << col << std::endl;
        // }
    }
    // else if (board[row][col] == "Q"){
    //     if (row+1 >= n){
    //         row 
    //     }
    // }
    // std::cout << "queen: " << queen << std::endl;
    // full = false;
    std::cout << "row: " << row << "   col: " << col << std::endl;
    // if (full){
    //     return;
    // }
    // if (queen < n && !full){
    //     if (row+2 < n){
    //         solve(board, n, row+2, col, queen, full);
    //     }
    //     else if (row-2 >= 0){
    //         solve(board, n, row-2, col, queen, full);
    //     }
    //     else if (col+2 < n){
    //         solve(board, n, row, col+2, queen, full);
    //     }
    //     else if {col-2 >= 0){
    //         solve(board, n, row, col-2, queen )
    //     }

    // }
    // if (queen < n){
    //     board[row][col] = "~";
    // }
    // for(int i=0; i<n; i++){
    //     for (int j=0; j<n; i++){
    //         if (board[i][j] == "~"){
    //             board[i][j] = "X";
    //         }
    //     }
    // }
    // return;
}

void deleteBoard(std::string** board, int n){
    for(int i; i<=n; i++){
        delete[] board[i];
    }
}

int main (){
    std::string** board;
    createBoard(board, 6);
    // int count = 0;
    // board[6][0] = "1";
    // board[6][1] = "2";
    // mark(board, 6, 1, 2, count);
    // board[1][2] = "Q";
    int n = 4;
    int row = 0;
    int col = 0;
    board[n][2] = std::to_string(row);
    board[n][3] = std::to_string(col);
    std::cout << "row: " << board[n][2] << "  col: " << board[n][3] << std::endl;
    int queen = 0;
    bool full = true;
    solve(board, n, 1, 2, queen, full);
    printBoard(board, n);
    deleteBoard(board,n);
    return 0;
}