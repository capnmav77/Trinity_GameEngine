#include <iostream>
#include "MySTL/vector.h"
#include <tuple>
#include "Engine/Player.h"
#include "Engine/Ai.h"
#include "Engine/GameEngine.h"
#include "TicTacToe/TTT.h"
#include "TicTacToe/TTTBoard.h"
#include<unordered_map>



void TTT_Plugin()
{
  std::cout<<"Which Mode you will like "<<std::endl;

  std::cout<<"1.  Human v/s Human "<<std::endl;
  std::cout<<"2.  AI v/s Human "<<std::endl;
  std::cout<<"3.  Human v/s AI "<<std::endl;
  std::cout<<"4.  AI v/s AI "<<std::endl;

  int wish ;
  std::cout<<"Wish : "<<std::endl;
  cin>>wish;

  TTT gamePack;
  HumanPlayer h1, h2;
  AIPlayer<TTT> ai_1(&gamePack),ai_2(&gamePack);
  
  if(wish == 1)
  {
    h1.initialize_player();
    h2.initialize_player();
    GameEngine<TTT,HumanPlayer*,HumanPlayer*> gameEngine(&gamePack,&h1,&h2); 
    gameEngine.game_loop();
  }
  else if(wish ==2){
    ai_1.initialize_player();
    h2.initialize_player();
    GameEngine<TTT,AIPlayer<TTT>*,HumanPlayer*> gameEngine(&gamePack,&ai_1,&h2);
    gameEngine.game_loop(); 
  }
  else if(wish ==3){
    h1.initialize_player();
    ai_2.initialize_player();
    GameEngine<TTT,HumanPlayer*,AIPlayer<TTT>*> gameEngine(&gamePack,&h1,&ai_2); 
    gameEngine.game_loop();
  }
  else{
    ai_1.initialize_player();
    ai_2.initialize_player();
    GameEngine<TTT,AIPlayer<TTT>*,AIPlayer<TTT>*> gameEngine(&gamePack,&ai_1,&ai_2); 
    gameEngine.game_loop();
  }

}

unordered_map<std::string,void(*)()> game_collection;
