#pragma once
#include <iostream>
#include "../MySTL/vector.h"
#include "Player.h"
#include "GameTraits.h"

using namespace std;



template <typename GAME, typename... Players>
class GameEngine
{
    static_assert((IsPointerToPlayerDerived<Players>::value && ...), "All Players must be pointers to classes derived from Player");
private:
    GAME* game;
    Vector<Player*> players;
    int num_players;
    int turn;

public:
    GameEngine(GAME* game,Players... players) : game(game) ,num_players(sizeof...(players)), turn(0) {
        (this->players.push_back(players),...);
       
    }


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
                if (terminal_status != -1)
                {
                    end_game(terminal_status);
                    return; // Exit the loop when game is over
                }
            }
        }
    }

    void end_game(int condition)
    {
        if(condition != -2){
            std::cout<<"Player "<<players[condition]->get_name()<<" wins"<<std::endl;
        }
        else{
            std::cout<<"It's a draw"<<std::endl;
        }
    }
};