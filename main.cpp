#include <iostream>
#include <unistd.h>
#include <vector>

enum CellStatus {
  lives,
  dies,
  reproduces,
  max_status
};


void seedBoard(int (&board)[10][10]){
  board[5][3] = 1;
  board[5][4] = 1;
  board[5][5] = 1;
  board[4][5] = 1;
  board[3][4] = 1;
}

void printBoard(int (&board)[10][10]){
  for(int row{0}; row < 10; ++row){
    for (int col = 0; col < 10; ++col) {
      std::cout << board[row][col] << " ";
      if((col+1) % 10 == 0)std::cout<<"\n";
    }
  }
}

int calculateNeighbors(int (&board)[10][10], int row, int col){
  int num_living{0};
  for (int i = row-1; i <= row+1; ++i) {
    for (int j = col-1; j <= col+1; ++j) {
      if (i >= 0 && i < 10 && j >= 0 && j < 10){
        int board_value {board[i][j]};
        if (!(i == row && j == col)){
          num_living += board_value;
        }
      }
    }
  }
//  num_living += board[row-1][col];
//  num_living += board[row+1][col];
//  num_living += board[row][col+1];
//  num_living += board[row][col-1];
//  num_living += board[row+1][col+1];
//  num_living += board[row+1][col-1];
//  num_living += board[row-1][col+1];
//  num_living += board[row-1][col-1];
  return num_living;
}

int lifeStatus(int num_living, int status){
  switch (num_living) {
    case 2:
      return (status?1:0);
    case 3:
      return 1;
    default:
      return 0;
  }
}


void lifeCycle(int (&board)[10][10]){
  std::vector<int> temp_board_values;
  std::vector<int> temp_board_row;
  std::vector<int> temp_board_col;
  for (int row = 0; row < 10; ++row) {
    for (int col = 0; col < 10; ++col) {
      int status{board[row][col]};
      int num_living{calculateNeighbors(board,row,col)};
//      if(row == 6 && col == 4){
//        int num_living{calculateNeighbors(board,row,col)};
//      }
      temp_board_values.push_back(lifeStatus(num_living,status));
      temp_board_row.push_back(row);
      temp_board_col.push_back(col);
    }
  }
  for (int i = 0; i < temp_board_values.size(); ++i) {
    board[temp_board_row[i]][temp_board_col[i]] = temp_board_values[i];
  }
}

void testBoard(int (&board)[10][10]){
  std::cout << board[9][5];
}

int main() {
  unsigned int microsecond = 1000000;
  //create game board
  int game_board[10][10]{};
  seedBoard(game_board);
  //testBoard(game_board);
  printBoard(game_board);
  for (int i = 0; i < 10; ++i) {
    usleep(2*microsecond);
    std::cout << "\n";
    lifeCycle(game_board);
    printBoard(game_board);
  }
  return 0;
}
