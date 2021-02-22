#pragma once

void createBoard(std::string** board, int n);
void printBoard(std::string** board, int n);
void mark(std::string** board, int n, int row, int col, int &count, int queen);
bool checkQ(std::string** board, int n, int row, int col, int &queen);
void solve(std::string** board, int n, int col, int &queen);
void deleteBoard(std::string** board, int n);