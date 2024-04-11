#pragma once //meaning include this file only once
#include "../MySTL/vector.h"
#include "../Engine/GamePack.h"
#include "../Engine/GameBoard.h"
#include <iostream>
#include <string>
#include "./Connect4.h"

class Connect4Board : public Board<7, 7, int>
{
private:


public:

    //function to initialize the board
    void init();

    //function to display the board
    void display();

    //function to get the valid moves
    Vector<int> get_valid_moves();

    //function to check if a move is valid
    template <typename U>
    bool playable(U loc);

    // function to check for terminal state
    template <typename U>
    U check_terminal();

    //function to move the player
    template <typename U, typename V>
    void move(U loc, V turn);

    //function to unmove the player i.e setting the move to -1
    template <typename U>
    void unmove(U loc);

};
    

void Connect4Board::init()
{
    Board::init();
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            game_board[i][j] = -1;
        }
    }
}

void Connect4Board::display()
{
    for (auto row : Connect4Board::game_board)
    {
        cout << "| ";
        for (auto col : row)
        {
            if (col == -1)
                cout << "  | ";
            else if (col == 0)
                cout << "O | ";
            else if (col == 1)
                cout << "X | ";
        }
        cout << endl;
    }
}

template <>
void Connect4Board::move<int, int>(int loc, int turn)
{
    int col = loc - 1;

    for (int i = 6; i >= 0; i--)
    {
        if (game_board[i][col] == -1)
        {
            game_board[i][col] = turn;
            break;
        }
        if(i == 0){
            cout << "Invalid Move" << endl;
        }
    }
}


template <>
void Connect4Board::unmove<int>(int loc)
{
    int col = loc - 1;

    for (int i = 0; i < 6; i++)
    {
        if (game_board[i][col] != -1)
        {
            game_board[i][col] = -1;
            break;
        }
    }
}


// i swear to god i'll .... , whyyyyyy
// check the typeee you fooollll

template <>
int Connect4Board::check_terminal<int>()
{

    //return 0 -> player 1 , 1->player2 , -2-> draw , -1 -> game not over

    //check for a draw
    if(get_remaining_moves() == 0){
        return -2;
    }

    // Check for rows
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 4; j++){
            if(game_board[i][j] != -1 && game_board[i][j] == game_board[i][j+1] && game_board[i][j+1] == game_board[i][j+2] && game_board[i][j+2] == game_board[i][j+3]){
                return game_board[i][j];
            }
        }
    }

    //check for columns for board size 7x7
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 7; j++){
            if(game_board[i][j] != -1 && game_board[i][j] == game_board[i+1][j] && game_board[i+1][j] == game_board[i+2][j] && game_board[i+2][j] == game_board[i+3][j]){
                return game_board[i][j];
            }
        }
    }

    //check for diagonals
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(game_board[i][j] != -1 && game_board[i][j] == game_board[i+1][j+1] && game_board[i+1][j+1] == game_board[i+2][j+2] && game_board[i+2][j+2] == game_board[i+3][j+3]){
                return game_board[i][j];
            }
        }
    }

    return -1;
}



template <>
bool Connect4Board::playable<int>(int loc)
{
    if(loc < 1 || loc > 7){
        return false;
    }
    int col = loc - 1;
    return game_board[0][col] == -1; //if the topmost cell of the column is empty then the move is valid
}


 Vector<int> Connect4Board::get_valid_moves() {
    Vector<int> valid_moves;
    for (int i = 0; i < 7; i++) {
        if (game_board[0][i] == -1) {
            valid_moves.push_back(i + 1);
        }
    }
    return valid_moves;
}