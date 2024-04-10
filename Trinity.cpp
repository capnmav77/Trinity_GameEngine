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


  /*
  
  1. Beutify The Menues and play events, use system cls or clear to remove old boards
  2. Add comments 
  3. Private and protected member of the class
  4. Concepts and constraints
  5. unordered_map implemntation
  
  */

  return 0;
}
