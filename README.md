# Trinity 

 ### A Prototype Game Engine that can run and simulate multiple Sequentially Played games like Tic Tac Toe , Connect4 , etc.
 ### Trinity utilizes a modified version of Monte Carlo Tree Search for The Artificial Intelligence Baked in 
 ### The Game Engine is Designed to be completely Modular and Highly Generic for extensive Modifications and CROSS IMPORTS 
 ### The AI is capable of playing any game that the game engine can Run 

# Documentation 📃
 The Project contains A main **ENGINE** directory as well as a Game Directory , inside the Engine directory are files that contain the logic for the framework to run
 Here's the list of important Parts for the Engine : 
 - Ai.h -> contains the Logic for the AI [ MCTS ]
 - Player.h -> contains the main class Object Player as well as it's subclasses Humanplayer and AIplayer
 - GameEngine.h -> contains the logic for running the game
 - GameTraits.h -> Used as a extension for GameEngine to check the types of the parameters being passed
 - GamePack.h -> is a SuperClass that implements a Game template
 - GameBoard.h -> is a superclass that implements a Game Board
 - State.h -> is a necessary file for the AI and GameEngine to simulate the states of the board

 The Game directory contains the games that can be run with the game engine , you can create your own game or add in a new game by simply modifying the template of the Game pack 

 Games Created 🎮 : 
  - **Tic Tac Toe**
  - **Connect 4**


# How to Install 💻
``` bash
  git clone https://github.com/capnmav77/TIX_TAX_TOX.git
  cd TIX_TAX_TOX/
```

# For Linux Users 
``` bash
  chmod +x ./run.sh
  ./run.sh
```

# For Windows Users 
``` bash
  g++ Trinity.cpp
  ./a.exe
```

# Contribute 🤗
  we are open to anyone who likes to improvise and contribute to this project , you can create a pr or get in touch with us using the email : rameshwar77411@gmail.com , AShenoy64@gmail.com
