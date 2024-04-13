#include <iostream>
#include "MySTL/vector.h"
#include <tuple>
#include "Engine/Player.h"
#include "Engine/Ai.h"
#include "Engine/GameEngine.h"
#include "TicTacToe/TTT.h"
#include "TicTacToe/TTTBoard.h"
#include <unordered_map>



void TTT_Plugin()
{
  //clear the screen
  std::cout << "\033[2J\033[1;1H";

  //display ascii art 
  std::cout << "  _______ _        _______           _______         " << endl;
  std::cout << " |__   __(_)      |__   __|         |__   __|        " << endl;
  std::cout << "    | |   _  ___     | | __ _  ___     | | ___   ___ " << endl;
  std::cout << "    | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\" << endl;
  std::cout << "    | |  | | (__     | | (_| | (__     | | (_) |  __/" << endl;
  std::cout << "    |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___|" << endl;
  

  std::cout<<"Which Mode you will like "<<std::endl;

  std::cout<<"1.  Human v/s Human "<<std::endl;
  std::cout<<"2.  AI v/s Human "<<std::endl;
  std::cout<<"3.  Human v/s AI "<<std::endl;
  std::cout<<"4.  AI v/s AI "<<std::endl;

  int wish ;
  std::cout<<"Wish : "<<std::endl;
  cin>>wish;

  TTT gamePack;
  // HumanPlayer h1, h2;
  // AIPlayer<TTT> ai_1(&gamePack),ai_2(&gamePack);
  
  if(wish == 1)
  {
    HumanPlayer h1, h2;
    h1.initialize_player(1);
    h2.initialize_player(2);
    GameEngine<TTT,HumanPlayer*,HumanPlayer*> gameEngine(&gamePack,&h1,&h2); 
    gameEngine.game_loop();
  }
  else if(wish ==2){
    HumanPlayer h2;
    AIPlayer<TTT> ai_1(&gamePack);
    ai_1.initialize_player(1);
    h2.initialize_player(2);
    GameEngine<TTT,AIPlayer<TTT>*,HumanPlayer*> gameEngine(&gamePack,&ai_1,&h2);
    gameEngine.game_loop(); 
  }
  else if(wish ==3){
    HumanPlayer h1;
    AIPlayer<TTT> ai_2(&gamePack);
    h1.initialize_player(1);
    ai_2.initialize_player(2);
    GameEngine<TTT,HumanPlayer*,AIPlayer<TTT>*> gameEngine(&gamePack,&h1,&ai_2); 
    gameEngine.game_loop();
  }
  else{
    AIPlayer<TTT> ai_1(&gamePack),ai_2(&gamePack);
    ai_1.initialize_player(1);
    ai_2.initialize_player(2);
    GameEngine<TTT,AIPlayer<TTT>*,AIPlayer<TTT>*> gameEngine(&gamePack,&ai_1,&ai_2); 
    gameEngine.game_loop();
  }

}

unordered_map<std::string,void(*)()> game_collection;
