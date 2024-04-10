// AI.h
#pragma once

#include <iostream>
#include <cmath>
#include "../MySTL/vector.h"
#include "GameBoard.h"

template <typename GAME>
class AI {
private:
    GAME& game;

public:
    
    AI(GAME& game) : game(game) {
        std::cout << "AI initialized" << std::endl;
    }

    void initialize_player() {
        std::cout << "AI initialized" << std::endl;
    }

    std::string get_move()
    {
        game.simulate(0,0,0);
        Vector<int> valid_moves = game.get_valid_moves();
        Vector<double> UBC_Rates;

        for(auto moves : valid_moves){
            Vector<int> result = simulate_game(moves,1);
            int total_games = result[0] + result[1] + result[2];
            double exploration_factor = 0.5;
            double UCB = ((result[0]*2.0 + result[1]*1.0 - result[2]*1.0) / total_games) + sqrt(2 * log(total_games) / (total_games * exploration_factor));
            UBC_Rates.push_back(UCB);
        }
        
        int max_index = 0 ;
        for(int i = 0 ; i < UBC_Rates.size() ; i++){
            if(UBC_Rates[i] > UBC_Rates[max_index]){
                max_index = i;
            }
        }

        std::string move = std::to_string(valid_moves[max_index]);
        game.simulate(0,0,1);
        return move;
    }

    Vector<int> simulate_game(int move,int turn) {
        game.simulate(move,turn,2);
        Vector<int> result(3, 0);
        Vector<int> valid_moves = game.get_valid_moves();
        int terminal_state = game.game_over();
        
        if(terminal_state != -1){
            if(terminal_state == 1){
                result[0] = 1;
            }
            else if(terminal_state == -2){
                result[1] = 1;
            }
            else{
                result[2] = 1;
            }
            game.simulate(move,0,3);
            return result;
        }


        if(valid_moves.size() == 0){
            result[1] = 1;
            game.simulate(move,0,3);
            return result;
        }


        for (auto _move : valid_moves) {
            Vector<int> recursive_result = simulate_game(_move, (turn + 1) % 2);
            result[0] += recursive_result[0]; // Wins from recursive simulation
            result[1] += recursive_result[1]; // Draws from recursive simulation
            result[2] += recursive_result[2]; // Losses from recursive simulation
        }

        // Undo the move before returning
        game.simulate(move,0,3);
        return result;
    }
};
