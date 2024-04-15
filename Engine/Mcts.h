#pragma once

#include <iostream>
#include <cmath>
#include "../MySTL/vector.h"
// #include <vector>
#include "GameBoard.h"
#include "State.h"
#include <unordered_map>

template <typename GAME>

class AI
{

private:
    // GAME* game is a pointer to the game object that the AI will play
    GAME *game;

    // AI Turn is the turn of the AI
    typename GAME::PLAYER_NOTATION AI_Turn;

    // exploration factor is the parameter that controls the exploration vs exploitation tradeoff in the UCB formula
    double exploration_factor = 0.5;

    unordered_map<string, unordered_map<typename GAME::PLAYER_NOTATION, Vector<int>> >game_states;

    // Function to simulate the game
    // template <typename T, typename U>
    // Vector<int> simulate_game(T move, U turn, int depth , typename GAME::PLAYER_NOTATION AI_Turn)
    // {
    //     string game_state = game->get_board_key();
    //     // if (game_states.find(game_state) != game_states.end() && game_states[game_state].find(depth) != game_states[game_state].end())
    //     // {
    //     //     return game_states[game_state][depth];
    //     // }

    //     game->simulate(move, turn);
    //     Vector<int> result(3, 0);
    //     Vector<typename GAME::MOVE> valid_moves = game->get_valid_moves();
    //     int terminal_state = game->get_game_state();

    //     // Checking for terminal state
    //     if (terminal_state != -1)
    //     {
    //         if (terminal_state == -2)
    //         {
    //             result[1] = 1; // Draw
    //         }
    //         else if (terminal_state == AI_Turn)
    //         {
    //             result[0] = 1; // AI wins
    //         }
    //         else
    //         {
    //             result[2] = 1; // Opponent wins
    //         }
    //         game->simulate(move, SIMULATE_STATE::UNMOVE);
    //         game_states[game_state][depth] = result;
    //         return result;
    //     }

    //     // Checking for draw
    //     if (valid_moves.size() == 0)
    //     {
    //         result[1] = 1; // Draw
    //         game->simulate(move, SIMULATE_STATE::UNMOVE);
    //         game_states[game_state][depth] = result;
    //         return result;
    //     }

    //     // Simulate the game for each valid move
    //     for (auto _move : valid_moves)
    //     {
    //         // Get the opponent's turn
    //         typename GAME::PLAYER_NOTATION opponent_turn = game->get_next_player(turn);

    //         // Recursive simulation for the opponent's move
    //         Vector<int> recursive_result = simulate_game(_move, opponent_turn, depth + 1,AI_Turn);
    //         result[0] += recursive_result[0]; // Losses for the AI are wins for the opponent
    //         result[1] += recursive_result[1]; // Draws for both
    //         result[2] += recursive_result[2]; // Wins for the AI are losses for the opponent
    //     }

    //     // Undo the move before returning
    //     game->simulate(move, SIMULATE_STATE::UNMOVE);
    //     game_states[game_state][depth] = result;
    //     int size = game_states[game_state][depth].size();
    
    //     return result;
    // }

    // overloaded function to keep the depth of the simulation at check
    // template <typename T, typename U>
    // Vector<int> simulate_game(T move, U turn, int depth, int max_depth)
    // {
    //     // Make a move in the game
    //     game->simulate(move, turn);
    //     Vector<int> result(3, 0);
    //     Vector<typename GAME::MOVE> valid_moves = game->get_valid_moves();
    //     int terminal_state = game->get_game_state();

    //     // Checking for terminal state or draw at lower depths
    //     if (terminal_state != -1 || valid_moves.size() == 0)
    //     {
    //          if (terminal_state == -2)
    //         {
    //             result[1] = 1; // Draw
    //         }
    //         else if (terminal_state == AI_Turn) //type id dependent have to fix this
    //         {
    //             result[0] = 1; // AI wins
    //         }
    //         else
    //         {
    //             result[2] = 1; // Opponent wins
    //         }
    //         return result;
    //     }

    //     // Checking for maximum depth
    //     if (depth == max_depth)
    //     {
    //         result[1] = 1; // Draw
    //         return result;
    //     }

    //     // Simulate the game for each valid move
    //     for (auto _move : valid_moves)
    //     {
    //         // Get the opponent's turn
    //         typename GAME::PLAYER_NOTATION opponent_turn = game->get_next_player(turn);

    //         // Recursive simulation for the opponent's move
    //         Vector<int> recursive_result = simulate_game(_move, opponent_turn, depth + 1, max_depth);
    //         result[0] += recursive_result[0]; // Wins for the AI are losses for the opponent
    //         result[1] += recursive_result[1]; // Draws for both
    //         result[2] += recursive_result[2]; // Losses for the AI are wins for the opponent
    //     }

    //     // Undo the move before returning
    //     game->simulate(move, SIMULATE_STATE::UNMOVE);
    //     return result;
    // }

    double calculate_UCB(int wins, int draws, int losses)
    {

        cout<< " WINS : " << wins << " DRAWS : " << draws << " LOSSES : " << losses << endl;

        int total_games = wins + draws + losses;

        double win_bias = wins * 0.5;
        double win_depth = wins / total_games;

        double draw_bias = draws * 0.25;
        double draw_depth = draws / total_games;

        double loss_bias = losses * 0.1;
        double loss_depth = losses / total_games;

        double refactored_wins = win_bias + win_depth;

        return (win_bias + draw_bias + loss_bias + win_depth + draw_depth + loss_depth) * sqrt(2 * log(total_games) / (total_games * exploration_factor));

        //;
    }

    template<typename T, typename U>
    Vector<int> simulate_game(T move, U turn )
    {
        // Make a move in the game
        game->simulate(move, turn);

        // string game_state = game->get_board_key();
        // if (game_states.find(game_state) != game_states.end() && game_states[game_state].find(turn) != game_states[game_state].end())
        // {
        //     return game_states[game_state][turn];
        // }


        Vector<int> result(3, 0);

        Vector<typename GAME::MOVE> valid_moves = game->get_valid_moves();

        int terminal_state = game->get_game_state();

        if(terminal_state!=-1 ){
            //Draw
            if(terminal_state == -2){
                result[1] = 1;
            }
            //AI wins
            else if(terminal_state == AI_Turn){
                result[0] = 1;
            }
            //Opponent wins
            else{
                result[2] = 1;
            }
            game->simulate(move, SIMULATE_STATE::UNMOVE);
            return result;
        }

        if(valid_moves.size() == 0){
            result[1] = 1;
            game->simulate(move, SIMULATE_STATE::UNMOVE);
            return result;
        }

        for(auto _move : valid_moves){
            turn = game->get_next_player(turn);
            Vector<int> recursive_result = simulate_game(_move,turn);
            result[0] += recursive_result[0];
            result[1] += recursive_result[1];
            result[2] += recursive_result[2];
        }

        game->simulate(move, SIMULATE_STATE::UNMOVE);
        return result;
    }
public:
    // Constructor for the AI class
    AI(GAME *game) : game(game) {}

    // Function to set the AI's turn
    void set_turn(typename GAME::PLAYER_NOTATION turn)
    {
        AI_Turn = turn;
    }

    // Function to set the exploration factor
    void set_exploration_factor(double factor)
    {
        exploration_factor = factor;
    }

    // function that decides the move for the AI
    std::string decide_move()
    {
        // Simulate the current state of the game
        game->simulate(SIMULATE_STATE::SAVE_BOARD); // overloaded function to save the current state of the game

        // Get the valid moves for the current state of the game
        Vector<typename GAME::MOVE> valid_moves = game->get_valid_moves();
        Vector<double> UBC_Rates;

        // Get the current player's notation
        typename GAME::PLAYER_NOTATION player = game->get_turn();
        set_turn(player);
        cout<<"AI TURN : "<<AI_Turn<<endl;
        int num_players = game->get_num_players();

        // If the game is over, return an empty string
        for (auto moves : valid_moves)
        {

            // Simulate the game for each valid move and calculate the UCB value for each move
            Vector<int> result = simulate_game<typename GAME::MOVE, typename GAME::PLAYER_NOTATION>(moves, player);
            player = game->get_next_player(player);


            // modified version of the UBC , change it according to prefs
            double UCB = calculate_UCB(result[0], result[1], result[2]); //((result[0]*3.0 + result[1]*2.0 - result[2]*3.0)/total_games)+ sqrt(2 * log(total_games) / (total_games * exploration_factor));

            cout << "FOR MOVE " << moves << " UCB IS " << UCB << endl;
            UBC_Rates.push_back(UCB);
        }

        // get the best move based on the UBC values
        int max_index = 0;
        for (int i = 0; i < UBC_Rates.size(); i++)
        {
            if (UBC_Rates[i] > UBC_Rates[max_index])
            {
                max_index = i;
            }
        }

        // return the best move
        std::string move = std::to_string(valid_moves[max_index]);
        game->simulate(SIMULATE_STATE::LOAD_BOARD);
        return move;
    }
};