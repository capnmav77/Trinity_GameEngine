#pragma once
#include <iostream>

#include "Ai.h"


class Player
{
protected:
    std::string name;
    //int sequence; ? - what is this for? ans: to keep track of the sequence of the player i.e 1st, 2nd, 3rd etc
public:
    virtual void initialize_player() = 0;
    virtual std::string get_move() = 0;
    virtual std::string get_name() = 0;
};


class HumanPlayer : public Player 
{
    public:
    void initialize_player(){
        std::cout << "Enter the name of the player : ";
        std::cin >> name;
    }

    std::string get_move() 
    {
        cout<<"Player "<<name<<"Turn"<<": ";
        std::string move;
        std::cin >> move;
        return move;
    }

    std::string get_name() 
    {
        return name;
    }

};


template <typename game>
class AiPlayer : public Player {
private:
    AI<game>& ai; // Reference to the Ai object

public:
    AiPlayer(AI<game>& ai) : ai(ai) {} // Constructor takes Ai object by reference

    void initialize_player() override {
        // Nothing to initialize for AiPlayer
    }

    std::string get_name() override {
        return "AiPlayer";
    }

    std::string get_move() override {
        int move = ai.get_best_move();
        return std::to_string(move);
    }
};