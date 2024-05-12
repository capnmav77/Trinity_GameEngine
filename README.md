# Trinity 🎮

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

 The Game directory contains the games that can be run with the game engine , you can add in your own game , just look into Getting started.

 Games Created 🎮 : 
  - **Tic Tac Toe**
  - **Connect 4**

## Overview 🙄

The Generic AI Game Engine enables developers to create games where an AI agent can seamlessly participate as a player. The engine operates under specific constraints:

- Games must feature finite states in every game step.
- Games should be deterministic, devoid of randomness.

At present, the engine includes two pre-implemented games: TicTacToe and Connect4. Each game supports four modes:

1. Human vs Human
2. Human vs AI
3. AI vs Human
4. AI vs AI

While the current implementations revolve around two-player dynamics, games are not inherently restricted to this setup.

# Getting Started 🚀

To develop a new game compatible with the engine, follow these steps:

1. Inherit from `GamePack.h`.
2. Override all necessary functions tailored to your game.
3. Register the new game in `GameList.h`.

Refer to the `TTT.h` and `Connect4.h` files, which provide insights into the existing game implementations.

Once these steps are executed, the engine will effortlessly integrate your game, facilitating AI players' engagement as per the designated modes.


# How to Install 💻
``` bash
  git clone https://github.com/capnmav77/TIX_TAX_TOX.git
  cd TIX_TAX_TOX/
```

### For Linux and Mac
``` bash
  chmod +x ./run.sh
  ./run.sh
```

### For Windows  
``` bash
  g++ Trinity.cpp
  ./a.exe
```

# Contribute 🤗
  we are open to anyone who likes to improvise and contribute to this project , you can create a pr or get in touch with us using the email : rameshwar77411@gmail.com , AShenoy64@gmail.com

# License 📇
This project is licensed under the [MIT License](LICENSE), permitting unrestricted use, modification, and distribution in accordance with the stipulated terms.

