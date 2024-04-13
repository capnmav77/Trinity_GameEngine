#include <iostream>
#include "Engine/GameEngine.h"
#include "MySTL/unordered_map.h"
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
    int count = game_collection.size();

    cout << "1. Tic Tac Toe" << endl;
    cout << "2. Connect 4" << endl;

    cin >> wish;

    if (wish > game_collection.size() || wish <= 0)
      continue;
    break;
  }

  if(wish == 1)
  {
    game_collection["Tic Tac Toe"]();
  }
  else if(wish == 2)
  {
    game_collection["Connect 4"]();
  }
}

int main()
{

  //Ascii art for "Prototype"
  cout<<"  _____           _        _                     "<<endl;             
  cout<<" |  __ \\         | |      | |                    "<<endl;         
  cout<<" | |__) | __ ___ | |_ ___ | |_ _   _ _ __   ___  "<<endl;
  cout<<" |  ___/ '__/ _ \\| __/ _ \\| __| | | | '_ \\ / _ \\ "<<endl;
  cout<<" | |   | | | (_) | || (_) | |_| |_| | |_) |  __/ "<<endl;
  cout<<" |_|   |_|  \\___/ \\__\\___/ \\__|\\__, | .__/ \\___| "<<endl;
  cout<<"                               __/ | |                   "<<endl;
  cout<<"                              |___/|_|                   "<<endl;

  //Unordered_map<std::string, void (*)()> game_collection;

  game_collection["Tic Tac Toe"] = TTT_Plugin;
  game_collection["Connect 4"] = Connect4_Plugin;
  play();
  


  /*
  2. Add comments  done 
  3. Private and protected member of the class done 
  4. Concepts and constraints not used
  1. Beutify The Menues and play events, use system cls or clear to remove old boards to be done 
  5. unordered_map implemntation to be done 
  */

  return 0;
}
