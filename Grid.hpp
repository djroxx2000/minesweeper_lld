#ifndef Grid_hpp
#define Grid_hpp

#include <vector>
#include <iostream>
#include <utility>
#include "Utility.hpp"
#include "Node.hpp"

using namespace std;

class Grid
{
public:
  int rows;
  int cols;
  int numberOfMines;
  bool isInitiated;
  vector<vector<Node *>> grid;

  Grid(int inputRows, int inputCols, int inputNumberOfMines)
      : rows(inputRows),
        cols(inputCols),
        numberOfMines(inputNumberOfMines),
        isInitiated(false)
  {
    grid = vector<vector<Node *>>(inputRows, vector<Node *>(inputCols));
  };

  Grid(vector<vector<int>> inputGrid)
      : rows(inputGrid.size()),
        cols(inputGrid[0].size())
  {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        int point = inputGrid[i][j];
        if (point > 9 || (point > 4 && point < 9))
        {
          string message =
              "File input for grid is in invalid format. \
               Please create a file with numeric values 0,1,2,3,4 (neighboring mines) or 9 (mine)";
          throw runtime_error(message);
        }
      }
    }
  }

  void initGrid()
  {
    if (isInitiated)
    {
      return;
    }
    addMines();
    randomizeMines();
    fillSafeNodes();
  }

  void show()
  {
    cout << "Grid:" << endl;
    cout << Utility::getCharSeries('-', cols * 2 - 1) << endl;
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        cout << grid[i][j]->value << " ";
      }
      cout << endl;
    }
    cout << Utility::getCharSeries('-', cols * 2 - 1) << endl;
  }

private:
  void addMines()
  {
    int numPlanted = 0;
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        if (numPlanted >= numberOfMines)
        {
          grid[i][j] = new Node(Node::Safe);
        }
        else
        {
          grid[i][j] = new Node(Node::Mine);
          numPlanted++;
        }
      }
    }
  }

  void swapGridIndices(int leftIdx, int rightIdx)
  {
    int leftRow = leftIdx / cols;
    int leftCol = leftIdx % cols;
    int rightRow = rightIdx / cols;
    int rightCol = rightIdx % cols;
    swap(grid[leftRow][leftCol], grid[rightRow][rightCol]);
  }

  void randomizeMines()
  {
    int numNodes = rows * cols;
    srand(time(NULL));
    int indicesSwapped = 0;
    while (indicesSwapped < numNodes - 1)
    {
      int swapIdx = rand() % numNodes;
      swapGridIndices(indicesSwapped, swapIdx);
      indicesSwapped++;
    }
  }

  void updateNeighbor(int row, int col)
  {
    int directions[] = {0, 1, 0, -1, 0};
    for (int i = 0; i < 4; i++)
    {
      int nextRow = row + directions[i];
      int nextCol = col + directions[i + 1];
      if (nextRow >= 0 &&
          nextRow < rows &&
          nextCol >= 0 &&
          nextCol < cols &&
          grid[nextRow][nextCol]->value != Node::Mine)
      {
        grid[nextRow][nextCol]->value++;
      }
    }
  }

  void fillSafeNodes()
  {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        if (grid[i][j]->value != Node::Mine)
        {
          continue;
        }
        updateNeighbor(i, j);
      }
    }
  }
};

#endif /* Grid_hpp */