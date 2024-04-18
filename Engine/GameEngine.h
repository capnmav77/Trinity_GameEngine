#pragma once
#include <iostream>
#include "../MySTL/vector.h"
#include "Player.h"
#include "GameTraits.h"

using namespace std;


template <typename GAME, typename... Players>
class GameEngine
{
private:
    // Check if all Players are pointers to classes derived from Player
    static_assert((IsPointerToPlayerDerived<Players>::value && ...), "All Players must be pointers to classes derived from Player");

    // GAME object that is a pointer to the Game class
    GAME* game;
    
    // Vector of pointers to Player objects
    Vector<Player*> players;

    // Number of players and the current turn variable
    int num_players;
    int turn;

    // Function to end the game
    void end_game()
    {   
        int condition = game->get_game_state();
        if(condition != -2){
            std::cout<<"Player "<<players[condition]->get_name()<<" wins"<<std::endl;
        }
        else{
            std::cout<<"It's a draw"<<std::endl;
        }
    }

public:
    // Constructor to initialize the game and players
    GameEngine(GAME* game,Players... players) : game(game) ,num_players(sizeof...(players)), turn(0) {
        (this->players.push_back(players),...);
       
    }

    // Function to start the game loop
    void game_loop()
    {
        int a;
        game->start_game();
        while (true)
        {
            for (int i = 0; i < num_players; i++)
            {
                while(true){
                    std::string move = players[i]->get_move();
                    if(game->play_next(move)){
                        break;
                    }
                }
                int terminal_status = game->get_game_state();
                //game->render_board();
                
                if (terminal_status != -1)
                {
                    end_game();
                    return; // Exit the loop when game is over
                }
            }
        }
    }
};