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
    virtual std::string get_name()=0;
    //virtual int get_sequence() = 0;
    virtual std::string get_move() = 0;
};

class HumanPlayer : public Player
{
    public:
    void initialize_player() override;
    std::string get_name() override;
    //int get_sequence() override;
    std::string get_move() override;
};

void HumanPlayer::initialize_player()
{
    std::cout << "Enter the name of the player : ";
    std::cin >> name;
    //std::cout << "Enter the sequence of the player : ";
    //std::cin >> sequence;
}

std::string HumanPlayer::get_name()
{
    return name;
}

std::string HumanPlayer::get_move()
{
    cout<<"Player "<<name<<"Turn"<<": ";
    std::string move;
    std::cin >> move;
    return move;
}   

class AiPlayer : public Player
{
    public:
    void initialize_player() override;
    std::string get_name() override;
    //int get_sequence() override;
    std::string get_move() override;
};

void AiPlayer::initialize_player()
{
    name = "AI";
    //sequence = 2;
}

std::string AiPlayer::get_name()
{
    return name;
}

std::string AiPlayer::get_move()
{
    return "1";
}
