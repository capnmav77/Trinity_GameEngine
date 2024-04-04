#pragma once
#include <iostream>
#include "../MySTL/vector.h"

template <int row, int col, typename T>
class Board
{
protected:
    Vector<Vector<T>> game_board;
    int remaining_moves;
public:
    // Initializes the board
    virtual void init()
    {
        game_board.resize(row);
        for(int i=0;i<row;++i)
        {
            game_board[i] = Vector<T>(col);
        }
        remaining_moves = row * col;
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

    //get and set remaining moves
    int get_remaining_moves(){
        return remaining_moves;
    }
    void set_remaining_moves(){
        remaining_moves--;
    }
};
