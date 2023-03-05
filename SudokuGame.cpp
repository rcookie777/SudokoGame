#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <regex>
#include "SudokuSolver.h"


const std::regex comma(",");
SudokuGame::SudokuGame(std::string filename) {
    std::ifstream file(filename);
    std::string line{};
    while (file && getline(file, line)) {
        std::vector<std::string> row{ std::sregex_token_iterator(line.begin(),line.end(),comma,-1), std::sregex_token_iterator() };
        std::vector<int> rows;
        std::transform(row.begin(), row.end(), std::back_inserter(rows),[&](std::string s) {
            return stoi(s);
        });
        grid_.push_back(rows);
    }
}

//deep copy
SudokuGame::SudokuGame(const SudokuGame& other) {
    grid_ = other.grid_;
}

const std::vector<std::vector<int>>& SudokuGame::grid() const {
  return grid_;
}

void SudokuGame::print() const {
    for (int i = 0; i < grid_.size(); i++) {
        if(i % 3 == 0 && i != 0) {
            std::cout << "-----------------------" << std::endl;
        }
    for(int j = 0; j < grid_[i].size(); j++) {
        if(j % 3 == 0 && j != 0) {
            std::cout << "| ";
        }
        std::cout << grid_[i][j] << " ";
    }
    std::cout << std::endl;
} 
}
int SudokuGame::size() const {
  return grid_.size();
}

int SudokuGame::value(int row, int column) const {
  return grid_[row][column];
}
void SudokuGame::value(int row, int column, int newValue) {
  grid_[row][column] = newValue;
}
bool isSafe(const std::vector<std::vector<int>>& grid, int row, int column, int num) {
    for (int i = 0; i < grid.size(); i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }
    for (int i = 0; i < grid.size(); i++) {
        if (grid[i][column] == num) {
            return false;
        }
    }
    int block_row = row - row % 3;
    int block_column = column - column % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[block_row + i][block_column + j] == num) {
                return false;
            }
        }
    }
    return true;
}
bool SudokuPlayer::solve(SudokuGame& game) const {
    for (int i = 0; i < game.size(); i++) {
        for (int j = 0; j < game.size(); j++) {
            if (game.value(i, j) == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(game.grid(), i, j, num)) {
                        game.value(i, j, num);
                        if (solve(game)) {
                            return true;
                        }
                        game.value(i, j, 0);
                    }
                }
                return false;
            }
        }
    }
    return true;
}
int main() {
  SudokuGame game("sudoku.csv");
  std::cout << "Puzzle" << std::endl;
  game.print();
    std::cout << std::endl;
  SudokuPlayer player;
  bool solved = player.solve(game);
  if (solved) {
      std::cout << "Solution found!" << std::endl;
      game.print();
  } else {
      std::cout << "No solution found." << std::endl;
  }

  return 0;
}



