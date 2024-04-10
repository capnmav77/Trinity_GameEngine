#pragma once //meaning include this file only once
#include "../MySTL/vector.h"
#include "../Engine/GamePack.h"
#include "../Engine/GameBoard.h"
#include <iostream>
#include <string>
#include "./TTT.h"

class TTTBoard : public Board<3, 3, int>
{
private:


public:
    void init();
    void display();

    template <typename U>
    bool playable(U loc);

    template <typename U>
    U check_terminal();

    template <typename U, typename V>
    void move(U loc, V turn);

    template <typename U>
    void unmove(U loc);
    

    Vector<int> get_valid_moves() {
        Vector<int> valid_moves;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (game_board[i][j] == -1) {
                    valid_moves.push_back(i * 3 + j + 1);
                }
            }
        }
        return valid_moves;
    }

    template<typename T>
    Vector<int> simulate(int loc, int turn, TTTBoard& simboard) {
        // Make the move on the current board
        simboard.move(loc, turn); 

        Vector<int> result(3, 0);
        int terminal_state = simboard.check_terminal<int>();

        if(terminal_state != -1){
            if(terminal_state == 1){
                result[0] = 1;
            }
            else if(terminal_state == -2){
                result[1] = 1;
            }
            else{
                result[2] = 1;
            }
            // Undo the move before returning
            simboard.unmove(loc);
            return result;
        }

        // Get valid moves
        Vector<int> valid_moves = simboard.get_valid_moves();
        if(valid_moves.size() == 0){
            result[1] = 1;
            // Undo the move before returning
            simboard.unmove(loc);
            return result;
        }

        // Simulate each possible move
        for (auto move : valid_moves) {
            // Recursively simulate the move without copying the board
            Vector<int> recursive_result = this->simulate<int>(move, (turn + 1) % 2, simboard);
            result[0] += recursive_result[0]; // Wins from recursive simulation
            result[1] += recursive_result[1]; // Draws from recursive simulation
            result[2] += recursive_result[2]; // Losses from recursive simulation
        }

        // Undo the move before returning
        simboard.unmove(loc);
        return result;
    }



};


void TTTBoard::init()
{
    Board::init();
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            game_board[i][j] = -1;
        }
    }
}

void TTTBoard::display()
{
    for (auto row : TTTBoard::game_board)
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
void TTTBoard::move<int, int>(int loc, int turn)
{
    int row = (loc - 1) / 3;
    int col = (loc - 1) % 3;

    if (game_board[row][col] != -1)
    {
        cout << "Invalid Move" << endl;
    }
    else
    {
        game_board[row][col] = turn;
    }
}


template <>
void TTTBoard::unmove<int>(int loc)
{
    int row = (loc - 1) / 3;
    int col = (loc - 1) % 3;
    game_board[row][col] = -1;
}


// i swear to god i'll .... , whyyyyyy
// check the typeee you fooollll

template <>
int TTTBoard::check_terminal<int>()
{
    //cout<<"Checking for terminal"<<endl;
    //return 0 -> player 1 , 1->player2 , -2-> draw , -1 -> game not over

    //check for a draw
    if(get_remaining_moves() == 0){
        return -2;
    }

    // Check for rows
    for (int i = 0; i < 3; i++)
    {
        if (game_board[i][0] != -1 && game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2])
        {
            return game_board[i][0];
        }
    }

    // Check for columns
    for (int i = 0; i < 3; i++)
    {
        if (game_board[i][0] != -1 && game_board[0][i] == game_board[1][i] && game_board[1][i] == game_board[2][i])
        {
            return game_board[0][i];
        }
    }

    // Check for diagonals
    if ((game_board[1][1] != -1) && ((game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) || (game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0])))
    {
        return game_board[1][1];
    }

    return -1;
}

template <>
bool TTTBoard::playable<int>(int loc)
{
    if(loc < 1 || loc > 9){
        return false;
    }
    int row = (loc - 1) / 3;
    int col = (loc - 1) % 3;
    return game_board[row][col] == -1;
}

/*
template <>
Vector<int> TTTBoard::get_valid_moves<int>()
{
    Vector<int> valid_moves;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game_board[i][j] == -1)
            {
                valid_moves.push_back(i * 3 + j + 1);
            }
        }
    }
    return valid_moves;
}
*/

// template <typename T>
// Vector<int> TTTBoard::simulate(T loc, int turn) {
//     cout<<"Simulating"<<endl;
//     TTTBoard simboard(*this); // Create a copy of the current board
//     simboard.move(loc, turn); // Make the move on the copy
//     Vector<int> result(3, 0);

//     if (simboard.check_terminal<int>() != -1) {
//         if (simboard.check_terminal<int>() == turn) {
//             result[0] += 1;
//         } else if (simboard.check_terminal<int>() == -2) {
//             result[2] += 1;
//         } else {
//             result[1] = 1;
//         }
//     } else {
//         cout<<"Getting valid moves"<<endl;
//         Vector<int> valid_moves = simboard.get_valid_moves();
//         //get the number of players: 
//         int num_players = 2;
//         for (auto move : valid_moves) {
//             Vector<int> new_result = simulate(move, (turn + 1) % num_players);
//             for (int i = 0; i < 3; ++i) {
//                 result[i] += new_result[i];
//             }
//         }
//     }

//     return result;
// }
