#include <iostream>
#include <vector>
#include <tuple>
#include "Engine/Player.h"

// #include "Engine/Ai.h"
#include "Engine/GameEngine.h"
#include "TicTacToe/TTT.h"




int main() {
    // GameEngine engine;
    // // UI
    // cout<<"Welcome to the Trinity Game Engine"<<endl;
    // cout<<"Choose the game you want to play : "<<endl;
    // cout<<"1. Tic Tac Toe"<<endl;
    // cout<<"2. Connect 4"<<endl;
    // cout<<"3. Sudoku"<<endl;

    // int choice;
    // cin>>choice;

    // if(choice == 1){
    //     GamePack<int>* game = new TicTacToe();
    //     engine.init(game);
    // }
    // // else if(choice == 2){
    // //     GamePack<int>* game = new Connect4();
    // //     engine.init(game);
    // // }
    // // else if(choice == 3){
    // //     GamePack<int>* game = new Sudoku();
    // //     engine.init(game);
    // // } 
    // else{
    //     cout<<"Invalid choice"<<endl;
    // }

  TTT gamePack;
  HumanPlayer h1,h2;
  AiPlayer a1;

  h1.initialize_player();
  h2.initialize_player();
  a1.initialize_player();

  int choice;
  cout<<"Choose the game mode : "<<endl;
  cout<<"1. Human vs Human or"<<"2. Human vs AI"<<endl;
  cin>>choice;

  if(choice == 1){
    GameEngine<TTT,HumanPlayer*,HumanPlayer*> engine1(gamePack,&h1,&h2);
    engine1.game_loop();
  }
  else if(choice == 2){
    GameEngine<TTT,HumanPlayer*,AiPlayer*> engine2(gamePack,&h1,&a1);
    engine2.game_loop();
  }
  else{
    cout<<"Invalid choice"<<endl;
  }
  return 0;
}