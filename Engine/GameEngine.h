#pragma once
#include <iostream>
#include "../MySTL/vector.h"
#include "Player.h"
// #include "GamePack.h"
using namespace std;

// class GameEngine {
//     private :
//         // the game to be played is stored here
//             GamePack<int>* game;

//         public:
//             // a initializer class that takes in the game pack and plays the game
//             void init(GamePack<int>* game) {
//                 //initialize the game
//                 this->game = game;
//                 Play();
//             }

//             void Play() {
//                 // creating a tic tac toe game

//                 // playing the game pvp
//                 //initialize the game board
//                 game->init(3);
//                 while(true){
//                     cout<<"Player "<<game->get_turn()<<"'s turn : ";
//                     game->move();
//                     game->display();
//                     if(game->check_terminal() != -1){
//                         break;
//                     }
//                 }
//             }
// };

template <typename GAME, typename... Players>
class GameEngine
{
private:
    GAME game;
    Vector<HumanPlayer> players;
    int num_players;
    int turn;

public:
    GameEngine(GAME game,Players... players) : game(game) ,num_players(sizeof...(players)), turn(0) {
        (this->players.push_back(players),...);
       
    }

    void game_loop()
    {
        game.start_game();
       
        while (true)
        {
            for (int i = 0; i < num_players; i++)
            {
                 std::cout<<"Player "<<players[i].get_name()<<std::endl;
                std::string move = players[i].get_move();

                game.play_next(move);
                if (game.game_over())
                {
                    end_game();
                    return; // Exit the loop when game is over
                }
            }
        }
    }

    void end_game()
    {
        // int winner = game.get_winner<int>();
        cout << players[0].get_name() << " wins" << endl;
        std::cout << "Game Over" << std::endl;
    }
};
