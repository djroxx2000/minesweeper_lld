#ifndef Game_hpp
#define Game_hpp

#include "Grid.hpp"
#include "Node.hpp"
#include "Utility.hpp"

class Game
{
private:
    enum MoveValidity
    {
        VALID,
        NODE_ALREADY_VISIBLE,
        NODE_OUT_OF_BOUNDS,
        GAME_STATE_NOT_RUNNING
    };

public:
    enum GameState
    {
        INITIALIZED,
        RUNNING,
        LOST,
        WON
    };
    Grid* mineGrid;
    GameState state;

    Game(Grid* inputGrid) : mineGrid(inputGrid), state(INITIALIZED){};

    void playMove(int row, int col)
    {
        if (state != GameState::RUNNING)
        {
            cout << "Unable to play move in current state." << endl;
            return;
        }
        MoveValidity moveValidity = isValidMove(row, col);
        if (moveValidity == MoveValidity::NODE_ALREADY_VISIBLE)
        {
            cout << "You've already seen that spot!" << endl;
        }
        else if (moveValidity == MoveValidity::NODE_OUT_OF_BOUNDS)
        {
            cout << "Can't check that spot! That's out of the map" << endl;
        }
        else if (!isSafeMove(row, col))
        {
            cout << "Oops... That's BOOM for you!" << endl;
        }
    }

    MoveValidity isValidMove(int row, int col)
    {
        if (mineGrid->grid[row][col]->isVisible)
        {
            return MoveValidity::NODE_ALREADY_VISIBLE;
        }
        if (
            row >= mineGrid->rows ||
            row < 0 ||
            col >= mineGrid->cols ||
            col < 0)
        {
            return MoveValidity::NODE_OUT_OF_BOUNDS;
        }
        return MoveValidity::VALID;
    }

    bool isSafeMove(int row, int col)
    {
        if (mineGrid->grid[row][col]->value != Node::Mine)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

#endif /* Game_hpp */