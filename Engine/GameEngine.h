#include<iostream>
#include<bits/stdc++.h>
// #include "GamePack.h"
using namespace std;


class GameEngine {
    private :
        // the game to be played is stored here 
            GamePack<int>* game;

        public: 
            // a initializer class that takes in the game pack and plays the game   
            void init(GamePack<int>* game) {
                //initialize the game 
                this->game = game;
                Play();
            }

            void Play() {
                // creating a tic tac toe game

                // playing the game pvp
                //initialize the game board
                game->init(3);
                while(true){
                    cout<<"Player "<<game->get_turn()<<"'s turn : ";
                    game->move();
                    game->display();
                    if(game->check_terminal() != -1){
                        break;
                    }
                }
            }
};
