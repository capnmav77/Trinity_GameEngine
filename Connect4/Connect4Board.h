#pragma once //meaning include this file only once
#include "../MySTL/vector.h"
#include "../Engine/GamePack.h"
#include "../Engine/GameBoard.h"
#include <iostream>
#include <string>
#include "./Connect4.h"
#include <sstream>


class Connect4Board : public Board<5, 5, int>
{
private:
int row;
int col;

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

    template <typename U>
    U get_board_key();
};



template<>
std::string Connect4Board::get_board_key<std::string>(){
    std::stringstream ss;
    for (int i = 0; i <row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (game_board[i][j] == -1) {
                ss << "-";
            } else if (game_board[i][j] == 0) {
                ss << "O";
            } else if (game_board[i][j] == 1) {
                ss << "X";
            }
        }
    }
    return ss.str();
}   

void Connect4Board::init()
{
    Board::init();
    this->row = Board::game_board.size();
    this->col = Board::game_board[0].size();
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
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

    for (int i = row-1; i >= 0; i--)
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

    for (int i = 0; i < row; i++)
    {
        if (game_board[i][col] != -1)
        {
            game_board[i][col] = -1;
            break;
        }
    }
}


template <>
int Connect4Board::check_terminal<int>()
{

    //return 0 -> player 1 , 1->player2 , -2-> draw , -1 -> game not over

    //check for a draw
    //cout<<"Remaining moves :"<<get_remaining_moves()<<endl;
    

    // Check for rows
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col-3; j++){
            if(game_board[i][j] != -1 && game_board[i][j] == game_board[i][j+1] && game_board[i][j+1] == game_board[i][j+2] && game_board[i][j+2] == game_board[i][j+3]){
                return game_board[i][j];
            }
        }
    }

    //check for columns for board size 5x5
    for(int i = 0; i < row-3; i++){
        for(int j = 0; j < col; j++){
            if(game_board[i][j] != -1 && game_board[i][j] == game_board[i+1][j] && game_board[i+1][j] == game_board[i+2][j] && game_board[i+2][j] == game_board[i+3][j]){
                return game_board[i][j];
            }
        }
    }

    //check for diagonals
    for(int i = 0; i < row-3; i++){
        for(int j = 0; j < col-3; j++){
            if(game_board[i][j] != -1 && game_board[i][j] == game_board[i+1][j+1] && game_board[i+1][j+1] == game_board[i+2][j+2] && game_board[i+2][j+2] == game_board[i+3][j+3]){
                return game_board[i][j];
            }
        }
    }

    //check for diagonals from bottom to top
    for(int i = 4; i >=3; --i){
        for(int j = 0; j <=1; j++){
            if(game_board[i][j] != -1 && game_board[i][j] == game_board[i-1][j+1] && game_board[i-1][j+1] == game_board[i-2][j+2] && game_board[i-2][j+2] == game_board[i-3][j+3]){
                return game_board[i][j];
            }
        }
    }
    
    if(get_remaining_moves() == 0){
        return -2;
    }

    return -1;
}



template <>
bool Connect4Board::playable<int>(int loc)
{
    if(loc < 1 || loc > row){
        return false;
    }
    int col = loc - 1;
    return game_board[0][col] == -1; //if the topmost cell of the column is empty then the move is valid
}


 Vector<int> Connect4Board::get_valid_moves() {
    Vector<int> valid_moves;
    for (int i = 0; i < col; i++) {
        if (game_board[0][i] == -1) {
            valid_moves.push_back(i + 1);
        }
    }
    return valid_moves;
}
