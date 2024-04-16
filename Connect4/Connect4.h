#pragma once // meaning include this file only once
#include "../MySTL/vector.h"
#include "../Engine/GamePack.h"
#include "../Engine/GameBoard.h"
#include <iostream>
#include <string>
#include "./Connect4Board.h"
#include "../Engine/State.h"

// rant = reminder to beat up avanish for writing the below code , what the f is this , why do you fucking need player notation ,

class Connect4 : public GamePack<2>
{
private:
    Connect4Board board;
    Vector<int> player_notation;
    int turn = 0;
    int process_move(string input);
    inline void clear_screen();

public:
    typedef int MOVE;
    typedef int PLAYER_NOTATION;
    typedef int STATE;

    void render_board();

    void start_game() override;

    int get_game_state() override;

    void init() override;

    int play_next(string move) override;

    int get_turn() override;

    int get_num_players() override;

    template <typename T>
    Vector<T> get_player_notations();

    template <typename U>
    U get_winner();

    void simulate(SIMULATE_STATE state);
    
    void simulate(Connect4::MOVE loc, Connect4::PLAYER_NOTATION turn);

    Connect4()
    {
        for (int i = 0; i < num_players; ++i)
        {
            player_notation.push_back(i);
        }
        board.init();
    }

    Connect4::PLAYER_NOTATION get_next_player(Connect4::PLAYER_NOTATION player)
    {
        return (player+1)%2;
    }
    Connect4::PLAYER_NOTATION get_current_player(int turn)
    {
        return player_notation[turn];
    }

   
    Vector<int> get_valid_moves()
    {
        return board.get_valid_moves();
    }
    
    void display_player_notations(){
        for(auto i:player_notation){
            cout<<i<<"_";
        }
    }
    std::string get_board_key(){
        return board.get_board_key<std::string>();
    }
};


//clear the screen
inline void Connect4::clear_screen()
{
    std::cout << "\033[2J\033[1;1H";
}

//simulate the game by saving the board state or loading the board state can be overloaded
void Connect4::simulate(SIMULATE_STATE state)
{
    static Connect4Board tempBoard = board;
    if (state == 0)
        tempBoard = board;
    else if (state == 1)
        board = tempBoard;
}


//run a simulation of the game by making a move and then unmaking it can be overloaded
void Connect4::simulate(Connect4::MOVE loc, Connect4::PLAYER_NOTATION turn)
{

    if (turn != -1)
    {
        board.move(loc, turn);
        board.set_remaining_moves();
    }
    else{
        board.unmove(loc);
        board.unmove_set_remaining_moves();
    }
       
}

// change the type from string to int
int Connect4::process_move(string input)
{
    return std::stoi(input);
}


// beautify the board display
void Connect4::render_board()
{
    //clear_screen();
    board.display();
}

// This function is called at the start of the game
void Connect4::start_game()
{
    render_board();
}

// This function is called to initialize the game
void Connect4::init()
{
    board.init();
}

// This function is called to get the game state
int Connect4::get_game_state()
{
    return board.check_terminal<Connect4::STATE>();
}

// This function is called to play the next move while also checking for validity
int Connect4::play_next(string input)
{
    int move = process_move(input);
    if (!board.playable<Connect4::MOVE>(move))
    {
        std::cout<<move<<std::endl;
        cout << "Invalid Move" << endl;

        return 0;
    }

    board.move(move, player_notation[turn]);
    turn = (turn + 1) % num_players;
    board.set_remaining_moves();
    render_board();
    return 1;
}

// returns the turn
int Connect4::get_turn()
{
    return turn;
}


// returns the number of players
int Connect4::get_num_players()
{
    return num_players;
}

// returns the player notations of the winner
template <typename U>
U Connect4::get_winner()
{
    int check = board.check_terminal<int>();
    if (check == -1)
        return -1;
    for (int i = 0; i < player_notation.size(); i++)
    {
        if (player_notation[i] == check)
        {
            return i;
        }
    }
}

// returns the player notations of the game
template <>
Vector<Connect4::PLAYER_NOTATION> Connect4::get_player_notations<Connect4::PLAYER_NOTATION>()
{
    return player_notation;
}