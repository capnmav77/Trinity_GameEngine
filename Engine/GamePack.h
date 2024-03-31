#include<iostream>
#include<bits/stdc++.h>
using namespace std;



// Class representing the game pack
template<typename... Ts>
class GamePack {
    // Define members representing the game pack
    // e.g., game board, game state, move checker, terminal conditions
    
public:
    // Constructor to initialize the game pack
    GamePack(/* parameters */);
    
    // Function to check possible moves
    std::vector<Move> getPossibleMoves(/* parameters */);
    
    // Function to check terminal conditions
    bool isTerminal(/* parameters */);
    
    // Other necessary functions
};


// class for tic tac toe game
class TicTacToe {
    // e.g., game board, game state, move checker, terminal conditions

    private: 
        vector<vector<int>> game_board;
        int n; // size of the board
        int turn; // turn of the player


        //terminal condition checker
        int checkrow(vector<vector<int>> board , int i , int j){
            int val = board[i][j];
            for(int k=0 ; k<3 ; k++){
                if(board[i][k] != val){
                    return -1;
                }
            }
            return val;
        }

        int checkcol(vector<vector<int>> board , int i , int j){
            int val = board[i][j];
            for(int k=0 ; k<3 ; k++){
                if(board[k][j] != val){
                    return -1;
                }
            }
            return val;
        }
        
        int checkdiag(vector<vector<int>> board , int i , int j){
            int val = board[i][j];
            if(board[0][0] == val && board[1][1] == val && board[2][2] == val){
                return val;
            }
            if(board[0][2] == val && board[1][1] == val && board[2][0] == val){
                return val;
            }
            return -1;
        }


    public:

        void init(int n){
            this->n = n;
            this->game_board = vector<vector<int>>(n , vector<int>(n , -1));
            this->turn = 0;
        }

        vector<vector<int>> get_game_board(){
            return game_board;
        }

        int get_turn(){
            return turn;
        }

        void set_turn(int turn){
            this->turn = turn;
        }

        void set_game_board(vector<vector<int>> game_board){
            this->game_board = game_board;
        }

};

