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
  HumanPlayer h1,h2;
  //initializing the Aiplayer with the ai object 
  AI<TTT> ai(gamePack);
  ai.initialize_player();
  h1.initialize_player();
  //AiPlayer<Ai<TTT>> a1(ai); // call in the AiPlayer constructor and pass the reference of the ai object
  //GameEngine<TTT,HumanPlayer*,AiPlayer<Ai<TTT>>*> engine1(gamePack,&h1,&a1);

  gamePack.start_game();

  while(gamePack.game_over() == -1){
    string move = h1.get_move();
    gamePack.play_next(move);
    if(gamePack.game_over() != -1){
      break;
    }
    move = ai.get_move();
    gamePack.play_next(move);
  }

  //AiPlayer<Ai<TTTBoard>,TTTBoard> a1(ai);

/*
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
*/
  return 0;
}