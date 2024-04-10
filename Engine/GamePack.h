#pragma once
#include <iostream>
#include "../MySTL/vector.h"
using namespace std;

template <int players>
class GamePack
{

public:
    int num_players = players;
    int turn;

    template <typename T>
    void simulate(T loc){}

    template <typename T>
    Vector<T> get_player_notations(){}

    template <typename U>
    U get_winner(){}

    template <typename T>
    Vector<T> get_valid_moves(){}

    virtual void init() {}
    virtual void start_game() {}
    virtual int play_next(string move) = 0;
    virtual int get_game_state() = 0;

    //add two functions if you need to simulate the game
    // template <typename T>
    // void simulate(T state){}

    // template<typename T,typename U>
    // void simulate(T move,U turn){}

    template<typename T>
    T get_next_player(T player){}

    virtual int get_num_players() = 0;

    virtual int get_turn() = 0;

};
