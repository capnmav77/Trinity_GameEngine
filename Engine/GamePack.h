#pragma once
#include <iostream>
#include "../MySTL/vector.h"
using namespace std;

template <int players>
class GamePack
{

protected:
    // to be used in the derived class only
    int num_players = players;
    int turn;

public:
    
    // overload this function if you need to simulate the game
    // simulate the game state or simulate the move . choice is yours
    template <typename T>
    void simulate(T loc){}

    //getting the player notations
    template <typename T>
    Vector<T> get_player_notations(){}

    //getting the winner
    template <typename U>
    U get_winner(){}

    //getting all the valid moves as a vector
    template <typename T>
    Vector<T> get_valid_moves(){}

    //getting the next player
    template<typename T>
    T get_next_player(T player){}


    //initialize the game
    virtual void init() {}

    //render the board
    virtual void start_game() {}

    //play the next move and return the game state
    virtual int play_next(string move) = 0;

    //get the game state
    virtual int get_game_state() = 0;

    //get the number of players as the number of players is protected
    virtual int get_num_players() = 0;

    //get the turn of the player
    virtual int get_turn() = 0;

    //Additional Function

    //add two functions if you need to simulate the game
    // template <typename T>
    // void simulate(T state){}

    // template<typename T,typename U>
    // void simulate(T move,U turn){}

};
