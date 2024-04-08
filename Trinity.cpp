#include <iostream>
#include <vector>
#include <tuple>
#include "Engine/Player.h"
#include "Engine/Ai.h"
#include "Engine/GameEngine.h"
#include "TicTacToe/TTT.h"
#include "TicTacToe/TTTBoard.h"


int main() {

  TTT gamePack ;
  TTTBoard board;
  HumanPlayer h1,h2;
  //initializing the Aiplayer with the ai object 

  Ai<TTTBoard> ai(board);

  int choice;
  cout<<"Choose the game mode : "<<endl;
  cout<<"1. Human vs Human or"<<"2. Human vs AI"<<endl;
  cin>>choice;

  if(choice == 1){
    h1.initialize_player();
    h2.initialize_player();
    GameEngine<TTT,HumanPlayer*,HumanPlayer*> engine1(gamePack,&h1,&h2);
    engine1.game_loop();
  }
  else if(choice == 2){
    h1.initialize_player();
    AiPlayer<TTTBoard> a1(ai);
    GameEngine<TTT,HumanPlayer*,AiPlayer<TTTBoard>*> engine2(gamePack,&h1,&a1);
    engine2.game_loop();
  }
  else{
    cout<<"Invalid choice"<<endl;
  }
  return 0;
}