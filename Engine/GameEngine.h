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
    GAME game;
    Vector<Player*> players;
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
                std::string move = players[i]->get_move();

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
        cout << players[0]->get_name() << " wins" << endl;
        std::cout << "Game Over" << std::endl;
    }
};
