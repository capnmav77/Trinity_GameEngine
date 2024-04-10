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


template <typename GAME>
class AIPlayer : public Player{
    AI<GAME> *ai;
public:
    AIPlayer(GAME* game) :Player() {
        ai =  new AI<GAME>(game);
    }   
        

    void initialize_player() override {
        this->name = "AI";
    }

    std::string get_name() override {
        return name;
    }

    std::string get_move() override {
        std::string move = ai->decide_move();
        return move;
    }
};