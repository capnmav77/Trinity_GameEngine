#pragma once // meaning include this file only once
#include "../MySTL/vector.h"
#include "../Engine/GamePack.h"
#include "TTTBoard.h"
#include <iostream>
#include <string>
#include <type_traits>

enum GameState
{
    DRAW = -2,
    ONGOING = -1,
    PLAYER_1 = 1,
    PLAYER_2 = 2,
};

class TTT : public GamePack<2>
{
private:
    TTTBoard board;
    Vector<int> player_notation;
    int turn = 0;
    int process_move(string input);
    void render_board();

protected:
    template <typename T>
    void simulate(T loc);
    template <typename T>
    Vector<T> get_valid_moves();

public:
    typedef int MOVE_TYPE;
    typedef int PLAYER_NOTATION_TYPE;
    typedef int STATE_TYPE;

    template <typename T>
    static auto state_resolver = []<T>(TTT::STATE_TYPE state)
    {
        if (state == -1)
            return GameState::ONGOING;
        else if (state == -2)
            return GameState::DRAW;
        else if (state == 0)
            return GameState::PLAYER_1;
        else if (state == 1)
            return GameState::PLAYER_2;
    };

    template <typename T>
    auto state_resolver = [](TTT::STATE_TYPE state)
    {
        if constexpr (std::is_same_v<T, int>)
        {
            if (state == -1)
                return GameState::ONGOING;
            else if (state == -2)
                return GameState::DRAW;
            else if (state == 1)
                return GameState::PLAYER_1;
            else if (state == 2)
                return GameState::PLAYER_2;
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            if (state == -1)
                return "ONGOING";
            else if (state == -2)
                return "DRAW";
            else if (state == 1)
                return "WIN:1";
            else if (state == 2)
                return "WIN:2";
        }
        else if constexpr (std::is_same_v<T, char>)
        {
            if (state == -1)
                return 'O';
            else if (state == -2)
                return 'D';
            else if (state == 1)
                return '1';
            else if (state == 2)
                return '2';
        }
        else
        {
            static_assert(std::is_same_v<T, int> || std::is_same_v<T, std::string> || std::is_same_v<T, char>, "Unsupported type");
        }
    };

    TTT()
    {
        for (int i = 0; i < num_players; ++i)
        {
            player_notation.push_back(i);
        }
        board.init();
    }

    void start_game() override;

    int game_over() override;

    void init() override;

    int play_next(string move) override;

    int get_turn() override;

    template <typename T>
    Vector<T> get_player_notations();

    template <typename U>
    U get_winner();
};

int TTT::process_move(string input)
{
    return std::stoi(input);
}

// beautify the board display
void TTT::render_board()
{
    board.display();
}

// Game Starting anything that needs to be done before the game starts
void TTT::start_game()
{
    render_board();
}

void TTT::init()
{
    board.init();
}

int TTT::game_over()
{
    return board.check_terminal<TTT::STATE_TYPE>();
}

int TTT::play_next(string input)
{
    int move = process_move(input);
    if (!board.playable<TTT::MOVE_TYPE>(move))
    {
        cout << "Invalid Move" << endl;

        return 0;
    }

    board.move(move, player_notation[turn]);
    turn = (turn + 1) % num_players;
    board.set_remaining_moves();
    render_board();
    return 1;
}

int TTT::get_turn()
{
    return turn;
}

// AI Learns the best move by simulating the game
template <>
void TTT::simulate<TTT::MOVE_TYPE>(TTT::MOVE_TYPE loc)
{
}

template <>
TTT::PLAYER_NOTATION_TYPE TTT::get_winner<TTT::PLAYER_NOTATION_TYPE>()
{
    int check = board.check_terminal<TTT::STATE_TYPE>();
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

template <>
Vector<TTT::PLAYER_NOTATION_TYPE> TTT::get_player_notations<TTT::PLAYER_NOTATION_TYPE>()
{
    return player_notation;
}

template <>
Vector<TTT::MOVE_TYPE> TTT::get_valid_moves<TTT::MOVE_TYPE>()
{
    return board.get_valid_moves<TTT::MOVE_TYPE>();
}
