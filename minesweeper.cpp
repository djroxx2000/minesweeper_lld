#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include "Utility.hpp"
#include "Grid.hpp"
#include "Game.hpp"

int main()
{
  string inputRowCol;
  int numberOfMines;
  cout << "Enter number of rows and cols separated by ',':" << endl;
  cin >> inputRowCol;
  cout << "Enter number of mines to be placed:" << endl;
  cin >> numberOfMines;
  pair<int, int> rowCol;
  try
  {
    rowCol = Utility::getRowCol(Utility::splitStrOn(inputRowCol, ','));
    int rows = rowCol.first;
    int cols = rowCol.second;
    Utility::validateMines(numberOfMines, rows, cols);
    Grid mineGrid = Grid(rows, cols, numberOfMines);
    mineGrid.initGrid();
    mineGrid.show();
    Game minesweeper = Game(mineGrid);
  }
  catch (const std::exception &e)
  {
    cerr << "Encountered error: " << e.what() << '\n';
  }

  return 0;
}