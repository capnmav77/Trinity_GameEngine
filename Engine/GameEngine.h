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
template <typename GAME>
class GameEngine{
    public:

    virtual void game_loop(){};

    virtual void end_game(int condition){};

};

template <typename GAME, typename... Players>
class GameEnginePVP : public GameEngine<GAME>
{
private:
    GAME game;
    Vector<HumanPlayer> players;
    int num_players;
    int turn;

public:
    GameEnginePVP(GAME game,Players... players) : game(game) ,num_players(sizeof...(players)), turn(0) {
        (this->players.push_back(players),...);
       
    }

    void game_loop()
    {
        game.start_game();
       
        while (true)
        {
            for (int i = 0; i < num_players; i++)
            {
                while(true){
                    std::string move = players[i].get_move();
                    if(game.play_next(move)){
                        break;
                    }
                }
                int terminal_status = game.game_over();
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
            std::cout<<"Player "<<players[condition].get_name()<<" wins"<<std::endl;
        }
        else{
            std::cout<<"It's a draw"<<std::endl;
        }
    }

};

template <typename GAME, typename Player , typename AIPlayer>
class GameEngineAVP : public GameEngine<GAME>
{
    private: 
        GAME game;
        HumanPlayer Human_Player;
        AiPlayer AI;
        int turn ; 

    public : 
        GameEngineAVP(GAME game,Player player1 , AIPlayer player2) : game(game) , turn(0) {
            this->Human_Player = player1;
            this->AI = player2;
            cout<<Human_Player.get_name()<<" vs "<<AI.get_name()<<endl;
        }

        void game_loop(){
            cout<<"Chill bro all cool , gotta implement this ez pz"<<endl;

        }

        void end_game(int condition)
        {
            // if(condition != -2){
            //     std::cout<<"Player "<<players[condition].get_name()<<" wins"<<std::endl;
            // }
            // else{
            //     std::cout<<"It's a draw"<<std::endl;
            // }
        }

};


