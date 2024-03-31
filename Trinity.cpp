#include <iostream>
#include <vector>
#include <tuple>

// #include "Engine/Ai.h"
#include "Engine/GamePack.h"
#include "Engine/GameEngine.h"

// Forward declaration of classes

// class GamePack;
// class GameEngine;
// class AI;



int main() {
    GameEngine engine;
    GamePack<int>* game = new TicTacToe();
    engine.init(game);
    
    return 0;
}