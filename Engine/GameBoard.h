#pragma once
#include <iostream>
#include "../MySTL/vector.h"

template <int row, int col, typename T>
class Board
{
protected:
    Vector<Vector<T>> game_board;
public:
    // Initializes the board
    virtual void init()
    {
        game_board.resize(row);
        for(int i=0;i<row;++i)
        {
            game_board[i] = Vector<T>(col);
        }
    };

    // Displays the board
    virtual void display(){}

    // Checks if the game is over
    template <typename U>
    U check_terminal();

    // Checks if the move is valid
    template <typename U>
    bool playable(U loc);

    // Makes a move
    template <typename U, typename V>
    void move(U loc, V turn);

    template <typename U>
    Vector<U> get_valid_moves();
};
