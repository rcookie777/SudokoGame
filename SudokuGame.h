#pragma once
#include <string>
#include <tuple>
#include <vector>

class SudokuGame {
 private:
    std::vector<std::vector<int>> grid_;

 public:
  SudokuGame() = default;
  SudokuGame(std::string filename);
  ~SudokuGame() = default;
  SudokuGame(const SudokuGame& other);
  SudokuGame& operator=(const SudokuGame& other);
  SudokuGame(const SudokuGame&& other);

  const std::vector<std::vector<int>>& grid() const;
  void print() const;
  int size() const;
  int value(int row, int column) const;
  void value(int row, int column, int newValue);
};

class SudokuPlayer {

 public:
  SudokuPlayer() = default;
  bool solve(SudokuGame& game) const;
};
