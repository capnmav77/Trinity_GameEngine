#pragma once
#include <iostream>
#include "../MySTL/vector.h"
using namespace std;

template <int players>
class GamePack
{

protected:
    int num_players = players;
    int turn;

    template <typename T>
    void simulate(T loc);

    template <typename T>
    Vector<T> get_valid_moves();

public:
    virtual void init(){}
    virtual void start_game(){}
    virtual void play_next(string move){}
    template <typename T>
    Vector<T> get_player_notations();

    template <typename U>
    U get_winner();
    
    virtual bool game_over(){}
    
};

// template <typename... Ts>
// class GamePack
// {
//     // a template class for the games to be implemented
//     // e.g., game board, game state, move checker, terminal conditions are all functions that are to be overriden by the game class
// public:
//     virtual void init(Ts... args) = 0;
//     virtual vector<vector<int>> get_game_board() = 0;
//     virtual int get_turn() = 0;
//     virtual void set_turn(int turn) = 0;
//     virtual void display() = 0;
//     virtual void move() = 0;
//     virtual void set_game_board(vector<vector<int>> game_board) = 0;
//     virtual int get_remaining_moves() = 0;
//     // virtual int recur(vector<vector<int>> &board , int turn) ;
//     // virtual int solve(vector<vector<int>> board) ;
//     virtual int check_terminal() = 0;
//     virtual void dtor()
//     {
//         cout << "Game Over" << endl;
//     }
// };

// // class for tic tac toe game
// class TicTacToe : public GamePack<int>
// {

// private:
//     vector<vector<int>> game_board;
//     int n;    // size of the board
//     int turn; // turn of the player
//     int remaining_moves;

//     // terminal condition checker
//     int checkrow(vector<vector<int>> board, int i, int j)
//     {
//         int val = board[i][j];
//         for (int k = 0; k < 3; k++)
//         {
//             if (board[i][k] != val)
//             {
//                 return -1;
//             }
//         }
//         return val;
//     }

//     int checkcol(vector<vector<int>> board, int i, int j)
//     {
//         int val = board[i][j];
//         for (int k = 0; k < 3; k++)
//         {
//             if (board[k][j] != val)
//             {
//                 return -1;
//             }
//         }
//         return val;
//     }

//     int checkdiag(vector<vector<int>> board, int i, int j)
//     {
//         int val = board[i][j];
//         if (board[0][0] == val && board[1][1] == val && board[2][2] == val)
//         {
//             return val;
//         }
//         if (board[0][2] == val && board[1][1] == val && board[2][0] == val)
//         {
//             return val;
//         }
//         return -1;
//     }

//     // checking all the above conditions
//     int Terminal_Check(vector<vector<int>> board)
//     {
//         for (int i = 0; i < 3; i++)
//         {
//             for (int j = 0; j < 3; j++)
//             {
//                 if (board[i][j] != -1)
//                 {
//                     int val = checkrow(board, i, j);
//                     if (val != -1)
//                     {
//                         return val;
//                     }
//                     val = checkcol(board, i, j);
//                     if (val != -1)
//                     {
//                         return val;
//                     }
//                     if (i == j)
//                     {
//                         val = checkdiag(board, i, j);
//                         if (val != -1)
//                         {
//                             return val;
//                         }
//                     }
//                     if (remaining_moves == 0)
//                     {
//                         return 2;
//                     }
//                 }
//             }
//         }
//         return -1;
//     }

// public:
//     void init(int n)
//     {
//         this->n = n;
//         this->game_board = vector<vector<int>>(n, vector<int>(n, -1));
//         this->turn = 0;
//         this->remaining_moves = n * n;
//         display();
//     }

//     vector<vector<int>> get_game_board()
//     {
//         return game_board;
//     }

//     int get_turn()
//     {
//         return turn;
//     }

//     void set_turn(int turn)
//     {
//         this->turn = turn;
//     }

//     void set_game_board(vector<vector<int>> game_board)
//     {
//         this->game_board = game_board;
//     }

//     int check_terminal()
//     {
//         int val = Terminal_Check(game_board);
//         if (val != -1)
//         {
//             if (val == 1)
//             {
//                 cout << "Player 1 wins" << endl;
//                 return 1;
//             }
//             else if (val == 0)
//             {
//                 cout << "Player 2 wins" << endl;
//                 return 0;
//             }
//             else
//             {
//                 cout << "Draw" << endl;
//                 return 2;
//             }
//         }
//         return -1;
//     }

//     void dtor()
//     {
//         cout << "Game Over" << endl;
//     }

//     int get_remaining_moves()
//     {
//         return remaining_moves;
//     }

//     void display()
//     {
//         for (auto row : game_board)
//         {
//             cout << "| ";
//             for (auto col : row)
//             {
//                 if (col == -1)
//                     cout << "  | ";
//                 else if (col == 0)
//                     cout << "O | ";
//                 else if (col == 1)
//                     cout << "X | ";
//             }
//             cout << endl;
//         }
//     }

//     void move()
//     {
//         int i, j, num;
//         cout << "Enter the number to input from 1 to 9: ";
//         cin >> num;
//         i = (num - 1) / 3;
//         j = (num - 1) % 3;
//         if (game_board[i][j] != -1)
//         {
//             cout << "Invalid Input" << endl;
//             move();
//         }
//         else
//         {
//             game_board[i][j] = turn;
//             set_turn(turn ^ 1);
//             remaining_moves--;
//             cout << remaining_moves << endl;
//         }
//     }
// };

// // class Connect4 : public GamePack<int>{

// //     private:
// //         vector<vector<int>> game_board;
// //         int n; // size of the board
// //         int turn; // turn of the player
// //     public :

// // };
