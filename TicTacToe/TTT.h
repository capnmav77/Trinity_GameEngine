#pragma once //meaning include this file only once
#include "../MySTL/vector.h"
#include "../Engine/GamePack.h"
#include "../Engine/GameBoard.h"
#include <iostream>
#include <string>

class TTTBoard : public Board<3, 3, int>
{
private:


public:
    void init();
    void display();

    template <typename U>
    bool playable(U loc);

    template <typename U>
    U check_terminal();

    template <typename U, typename V>
    void move(U loc, V turn);

    template <typename U>
    Vector<U> get_valid_moves();
};


void TTTBoard::init()
{
    Board::init();
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            game_board[i][j] = -1;
        }
    }
}

void TTTBoard::display()
{
    for (auto row : TTTBoard::game_board)
    {
        cout << "| ";
        for (auto col : row)
        {
            if (col == -1)
                cout << "  | ";
            else if (col == 0)
                cout << "O | ";
            else if (col == 1)
                cout << "X | ";
        }
        cout << endl;
    }
}

template <>
void TTTBoard::move<int, int>(int loc, int turn)
{
    int row = (loc - 1) / 3;
    int col = (loc - 1) % 3;

    if (game_board[row][col] != -1)
    {
        cout << "Invalid Move" << endl;
        // Sometype of error handling
        // finished it cuntt....
    }
    else
    {
        game_board[row][col] = turn;
    }
}


// i swear to god i'll .... , whyyyyyy
// check the typeee you fooollll

template <>
int TTTBoard::check_terminal<int>()
{
    //cout<<"Checking for terminal"<<endl;
    //return 0 -> player 1 , 1->player2 , 2-> draw , -1 -> game not over

    //check for a draw
    if(get_remaining_moves() == 0){
        return -2;
    }

    // Check for rows
    for (int i = 0; i < 3; i++)
    {
        if (game_board[i][0] != -1 && game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2])
        {
            return game_board[i][0];
        }
    }

    // Check for columns
    for (int i = 0; i < 3; i++)
    {
        if (game_board[i][0] != -1 && game_board[0][i] == game_board[1][i] && game_board[1][i] == game_board[2][i])
        {
            return game_board[0][i];
        }
    }

    // Check for diagonals
    if ((game_board[1][1] != -1) && ((game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) || (game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0])))
    {
        return game_board[1][1];
    }

    return -1;
}

template <>
bool TTTBoard::playable<int>(int loc)
{
    if(loc < 1 || loc > 9){
        return false;
    }
    int row = (loc - 1) / 3;
    int col = (loc - 1) % 3;
    return game_board[row][col] == -1;
}

template <>
Vector<int> TTTBoard::get_valid_moves<int>()
{
    Vector<int> valid_moves;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game_board[i][j] == -1)
            {
                valid_moves.push_back(i * 3 + j + 1);
            }
        }
    }
    return valid_moves;
}


// rant = reminder to beat up avanish for writing the below code , what the f is this , why do you fucking need player notation , 
//who writes public , protected and then public , cunt..... , and then forget's to mention private ..........

class TTT : public GamePack<2>
{
private:
    TTTBoard board;
    Vector<int> player_notation;
    int turn = 0;

protected:
    template <typename T>
    void simulate(T loc);
    template <typename T>
    Vector<T> get_valid_moves();

public:
    typedef int MOVE;
    typedef int PLAYER_NOTATION;
    typedef int STATE;

    TTT()
    { 
        for (int i=0 ; i<num_players ; ++i){
            player_notation.push_back(i);
        }
        board.init();
    }

    int process_move(string input);

    void render_board() ;

    void start_game() override;

    int game_over() override;

    void init() override;

    int play_next(string move) override;

    int get_turn() ;

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

void TTT::init(){
    board.init();

}

int TTT::game_over()
{
    return board.check_terminal<TTT::STATE>();
}

int TTT::play_next(string input)
{
    int move = process_move(input);
    if (!board.playable<TTT::MOVE>(move))
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
void TTT::simulate<TTT::MOVE>(TTT::MOVE loc)
{
}

template <typename U>
U TTT::get_winner()
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

template <>
Vector<TTT::PLAYER_NOTATION> TTT::get_player_notations<TTT::PLAYER_NOTATION>()
{
    return player_notation;
}

template <>
Vector<TTT::MOVE> TTT::get_valid_moves<TTT::MOVE>() 
{
    return board.get_valid_moves<int>();
}