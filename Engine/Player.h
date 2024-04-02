#pragma once
#include <iostream>

class Player
{

protected:
    std::string name;
    int sequence;
public:
    virtual void get_player_details(){}
    virtual std::string get_name(){}
    virtual int get_sequence(){}
    virtual std::string get_move(){}
};

class HumanPlayer : public Player
{
    public:
    void get_player_details() override;
    std::string get_name() override;
    int get_sequence() override;
    std::string get_move() override;
};

void HumanPlayer::get_player_details()
{
    std::cout << "Enter the name of the player : ";
    std::cin >> name;
    std::cout << "Enter the sequence of the player : ";
    std::cin >> sequence;
}

std::string HumanPlayer::get_name()
{
    return name;
}

int HumanPlayer::get_sequence()
{
    return sequence;
}

std::string HumanPlayer::get_move()
{
    std::cout << get_name() << "'s turn : ";
    std::string move;
    std::cin >> move;
    std::cout << std::endl;
    return move;
}