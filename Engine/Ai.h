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

    std::string get_best_move() {
        std::cout << "GetBestMove " << std::endl;

        Vector<int> valid_moves = game.get_valid_moves();

        // Debugging: Display valid moves
        std::cout << "Valid moves: ";
        for (auto move : valid_moves) {
            std::cout << move << " ";
        }
        std::cout << std::endl;

        // char c;
        // std::cin >> c;

        Vector<double> UBC_Rates;
        for (auto move : valid_moves) {
            // Simulate the move
            Vector<int> result = game.simulate(move, 1);
            
            int total_games = result[0] + result[1] + result[2];

            cout<<"result[0] : "<<result[0]<<" result[1] : "<<result[1]<<" result[2] : "<<result[2]<<" Total Games: "<<total_games<<endl;
            
            // Calculate UCB1 (Upper Confidence Bound)
            // double UCB = (result[0] * 2.0 / total_games) +
            //              sqrt(2 * log(total_games) / total_games);
            // double UCB = (result[0]*2.0 + result[1]*1.5 - result[2]*1.0)/total_games;
            
            //cout << "Move: " << move << " Win rate: " << result[0] * 1.0 / total_games << " UCB: " << UCB << endl;
            double exploration_factor = 0.5;
            double UCB = ((result[0]*2.0 + result[1]*1.0 - result[2]*1.0) / total_games) + sqrt(2 * log(total_games) / (total_games * exploration_factor));
            cout<<"Move : "<<move<<" UCB : "<<UCB<<endl;


            //cin>>c;
            UBC_Rates.push_back(UCB);
        }

        for(auto wins : UBC_Rates){
            cout<<wins<<" ";
        }
        // cin>>c;

        // Find the move with the highest UCB
        int max_index = 0 ;
        for(int i = 0 ; i < UBC_Rates.size() ; i++){
            if(UBC_Rates[i] > UBC_Rates[max_index]){
                max_index = i;
            }
        }

        // Convert the move to string and return
        std::string move = std::to_string(valid_moves[max_index]);
        cout<<"Move : "<<move<<endl;
        return move;
    }
};
