#include<iostream>
#include<string>
#include "./Connect4.h"


int main(){
    Connect4 game;
    game.init();
    game.start_game();
    // game.render_board();
    cout<<game.get_game_state()<<endl;
    Vector<int> valid_moves = game.get_valid_moves();
    for(auto move: valid_moves){
        cout<<move<<" ";
    }
    cout<<endl;
    while(game.get_game_state() == -1){
        string move;
        std::cin >> move;
        game.play_next(move);
        // game.render_board();
        cout<<game.get_game_state()<<endl;
        Vector<int> valid_moves = game.get_valid_moves();
        for(auto move: valid_moves){
            cout<<move<<" ";
        }
    }
    cout<<game.get_game_state();

    return 0;
}