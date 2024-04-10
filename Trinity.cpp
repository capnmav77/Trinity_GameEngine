#include <iostream>
#include "Engine/GameEngine.h"
#include "GameList.h"

// #include "Engine/Player.h"
// #include "Engine/Ai.h"
// #include "TicTacToe/TTT.h"
// #include "TicTacToe/TTTBoard.h"





void play()
{
  std::cout << "Welcome to Generic AI Engine" << std::endl;
  std::cout << "Please select the game you want to play" << std::endl;

  int wish;
  while (true)
  {
    int count = 1;
    for (auto game : game_collection)
    {
      std::cout << count << "  " << game.first << std::endl;
      ++count;
    }

    cin >> wish;

    if (wish > game_collection.size() || wish <= 0)
      continue;
    break;
  }

  game_collection["Tic Tac Toe"]();
}

int main()
{

  game_collection["Tic Tac Toe"] = TTT_Plugin;
  play();


  // TTT gamePack ;
  // HumanPlayer h1,h2;
  // //initializing the Aiplayer with the ai object 
  // AIPlayer<TTT> ai_1(&gamePack);
  // AIPlayer<TTT> ai_2(&gamePack);
  // ai_1.initialize_player();
  // ai_2.initialize_player();
  // // h1.initialize_player();
  // //AiPlayer<Ai<TTT>> a1(ai); // call in the AiPlayer constructor and pass the reference of the ai object
  // //GameEngine<TTT,HumanPlayer*,AiPlayer<Ai<TTT>>*> engine1(gamePack,&h1,&a1);

  // int a;
  // while(gamePack.get_game_state() == -1){
  //   string move = ai_1.get_move();
  //   gamePack.play_next(move);
  //   cin>>a;
  //   if(gamePack.get_game_state() != -1){
  //     break;
  //   }
  //   move = ai_2.get_move();
  //   gamePack.play_next(move);
  //   cin>>a;
  //   if(gamePack.get_game_state() != -1){
  //     break;
  //   }
  // }

  return 0;
}
