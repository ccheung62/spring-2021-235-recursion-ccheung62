#include <iostream>
#include <unistd.h>

void createBoard(std::string** board, int n){
    for (int i=0; i<n; i++){
        board[i] = new std::string[n];
        for (int j=0; j<n; j++){
            board[i][j] = ".";
        }
    }
    board[n] = new std::string[n*2];
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

void mark(std::string** board, int n, int row, int col, int &count, int queen){
    if (row < 0 || row >= n || col < 0 || col >= n){
        row = std::stoi(board[n][queen*2]);
        col = std::stoi(board[n][(queen*2)+1]);
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

// void checkBoard(std::string** board, int n, int row, int col, bool &full){
//     for (int i=0; i<n; i++){
//         for (int j=0; j<n; j++){
//             if (board[i][j] == "."){
//                 full = false;
//                 // std::cout << "inside the checkBoard I made the full bool false" << std::endl;
//                 return;
//             }
//         }
//     }
// } 

bool checkQ(std::string** board, int n, int row, int col, int &queen){
    for (int a=0; a<n; a++){
        for(int b=0; b<n; b++){
            board[a][b] = ".";
        }
    }
    for (int q=0; q<queen; q++){
        int r = std::stoi(board[n][q*2]);
        int c = std::stoi(board[n][(q*2)+1]);
        // std::cout << "marking row: " << r << " col: " << c << std::endl;
        int count = 0;
        mark(board, n, r, c, count, q);
        board[r][c] = "Q";
        // std::cout << "rewriting row:" << row << "  col:" << col << std::endl;
    }
    if (board[row][col] != "X"){
        return true;
    }
    else {
        return false;
    }
}

void solve(std::string** board, int n, int row, int col, int &queen, bool &full){
    if (col >= n || queen >=n){
        return;
    }
        for(int i=0; i<n; i++){
            // for (int a=0; a<n; a++){
            //     for(int b=0; b<n; b++){
            //         board[a][b] = ".";
            //     }
            // }
            // for (int q=0; q<queen; q++){
            //     int r = std::stoi(board[n][q]);
            //     int c = std::stoi(board[n][q+1]);
            //     std::cout << "marking row: " << r << " col: " << c << std::endl;
            //     mark(board, n, r, c, count, q);
            //     board[r][c] = "Q";
            //     std::cout << "rewriting row:" << row << "  col:" << col << std::endl;
            // }
            // std::cout << "row: " << row << "  col: " << col << std::endl;

            if (checkQ(board, n, i, col, queen)){
                board[n][queen*2] = std::to_string(i);
                board[n][(queen*2)+1] = std::to_string(col);
                // mark(board, n, i, col, count, queen);
                // board[i][col] = "Q";
                queen++;
                solve(board, n, i, col+1, queen, full);
                if (queen >= n){
                    return;
                }
                std::cout << "time to backtrack" << std::endl;
                queen--;
                std::cout << "queen: " << queen << std::endl;
                // for (int a=0; a<n; a++){
                //     for (int b=0; b<n; b++){
                //         board[a][b] = ".";
                //     }
                // }
                // for (int q=0; q<queen; q++){
                //     int r = std::stoi(board[n][q]);
                //     int c = std::stoi(board[n][q+1]);
                //     board[r][c] = ".";
                //     mark(board, n, r, c, count, q);
                //     board[r][c] = "Q";
                //     std::cout << "rewriting row:" << row << "  col:" << col << std::endl;
                // }
            }
            // for (int q=0; q<queen; q++){
            //     int r = std::stoi(board[n][q]);
            //     int c = std::stoi(board[n][q+1]);
            //     board[r][c] = ".";
            //     mark(board, n, r, c, count, q);
            //     board[r][c] = "Q";
            //     std::cout << "rewriting row:" << row << "  col:" << col << std::endl;
            // }
        }







    // printBoard(board,n);
    // if (row < 0 || row >= n || col < 0 || col >= n){
    //     return;
    // }
    // else if (board[row][col] == "X"){
    //     board[row][col] = "~";
    // }
    // if (queen < n && board[row-1][col] != "Q" && board[row-1][col] != "~" && board[row][col] != "+"){
    //     solve(board, n, row-1, col, queen, full);
    // }
    // // std::cout << "row: " << row << "   col: " << col << std::endl;
    // if (queen < n && board[row][col+1] != "Q" && board[row][col+1] != "~" && board[row][col] != "+"){
    //     solve(board, n, row, col-1, queen, full);
    // }
    // // std::cout << "row: " << row << "   col: " << col << std::endl;
    // if (queen < n && board[row+1][col] != "Q" && board[row+1][col] != "~" && board[row][col] != "+"){
    //     solve(board, n, row+1, col, queen, full);
    // }
    // // std::cout << "row: " << row << "   col: " << col << std::endl;
    // if (queen < n && board[row][col+1] != "Q" && board[row][col+1] != "~" && board[row][col] != "+"){
    //     solve(board, n, row, col+1, queen, full);
    // }
    // // std::cout << "Is it a dot " << (board[row][col] == ".") << std::endl;
    // if (board[row][col] == "."){
    //     // std::cout << "queen: " << queen << std::endl;
    //     board[n][0] = std::to_string(row);
    //     board[n][1] = std::to_string(col);
    //     int count = 0;
    //     mark(board, n, row, col, count);
    //     board[row][col] = "Q";
    //     queen++;
    //     full = true;
    //     checkBoard(board, n, row, col, full);
    //     if (full && queen < n){
    //         std::cout << "wrong answer" << std::endl;
    //         return;
    //     }
    //     for(int i=0; i<n; i++){
    //         for(int j=0; j<n; j++){
    //             if(board[i][j] == "~"){
    //                 board[i][j] = "X";
    //             }
    //         }
    //     }
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
    // }
    // else if (board[row][col] == "Q"){
    //     if (row+1 >= n){
    //         row 
    //     }
    // }
    // std::cout << "queen: " << queen << std::endl;
    // full = false;
    // std::cout << "row: " << row << "   col: " << col << std::endl;
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
    int n = 4;
    std::string** board;
    createBoard(board, n);
    // int count = 0;
    // board[6][0] = "1";
    // board[6][1] = "2";
    // mark(board, 6, 1, 2, count);
    // board[1][2] = "Q";
    int row = 0;
    int col = 0;
    // board[n][2] = std::to_string(row);
    // board[n][3] = std::to_string(col);
    // std::cout << "row: " << board[n][2] << "  col: " << board[n][3] << std::endl;
    int queen = 0;
    bool full = true;
    solve(board, n, 0, 0, queen, full);
    // for (int i=0; i<n*2; i++){
    //     std::cout << "board[n][" << i << "] = " << board[n][i] << std::endl;
    // }
    // printBoard(board, n);
    std::cout << "The solution for n-queens with " << n << " x " << n << " grid is: " << std::endl;
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
    printBoard(board, n);
    deleteBoard(board,n);
    return 0;
}