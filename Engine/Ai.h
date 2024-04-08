#pragma once
#include <iostream>
#include <cmath>
#include "../MySTL/vector.h"
#include "gameboard.h"


template <typename GAME>
class Ai {
private:
    GAME game;

public:
    // Function to initialize AI
    Ai(GAME game){
        this->game = game;
        // Implement the initialization logic here
        cout << "AI initialized" << endl;
    }
    void initialize_player(){
        cout << "AI initialized" << endl;
    }

    // Function to get the best move
    int get_best_move() {
        
        Vector<int> best_move;
        best_move = game.get_valid_moves();
        vector<int> win_rate;
        for(auto i : best_move){
            vector<int> res = game.simulate(i,game.get_board() , 1);
            //vector[0] = num_of_wins, vector[1] = num_of_Losses, vector[2] = num_of_draws
            int UBC  = res[0]*1.0/(res[0]+res[1]+res[2]) + sqrt(2*log(res[0]+res[1]+res[2])/res[0]+res[1]+res[2]);
            win_rate.push_back(UBC);
        }
        int max = 0;
        for(int i=0;i<win_rate.size();++i){
            if(win_rate[i] > win_rate[max]){
                max = i;
            }
        }
        return best_move[max];
    }
};