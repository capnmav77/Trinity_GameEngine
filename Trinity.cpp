#include <iostream>
#include <vector>
#include <tuple>

#include "Engine/Ai.h"
#include "Engine/GamePack.h"
#include "Engine/GameEngine.h"

// Forward declaration of classes

class GamePack;
class GameEngine;
class AI;



int main() {
    // Example usage
    GamePack<?> gamePack(/* parameters */);
    GameEngine gameEngine(gamePack);
    gameEngine.startGame();
    
    return 0;
}