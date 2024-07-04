#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include "Utility.hpp"
#include "Grid.hpp"
#include "Game.hpp"

int main()
{
  try
  {
    vector<vector<int>> gridInput = Utility::readCsvFromStdin<int>('\n', ',');
    Grid *mineGrid = nullptr;
    int rows, cols, numberOfMines;
    if (gridInput.empty())
    {
      string inputRowCol;
      cout << "Enter number of rows and cols separated by ',':" << endl;
      cin >> inputRowCol;
      cout << "Enter number of mines to be placed:" << endl;
      cin >> numberOfMines;
      pair<int, int> rowCol = Utility::getRowCol(Utility::splitStrOn(inputRowCol, ','));
      rows = rowCol.first;
      cols = rowCol.second;
      mineGrid = new Grid(rows, cols, numberOfMines);
      Utility::validateMines(numberOfMines, rows, cols);
    }
    else
    {
      throw runtime_error("TODO: validate and setup grid using grid file input");
    }

    Game minesweeper = Game(mineGrid);
    minesweeper.mineGrid->initGrid();
    minesweeper.mineGrid->show();
  }
  catch (const std::exception &e)
  {
    cerr << "Encountered error: " << e.what() << '\n';
  }

  return 0;
}