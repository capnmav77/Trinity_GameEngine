#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Class representing different AI algorithms
template<typename... Ts> 
class AI {
public:
    // Virtual function for predicting the next best move
    virtual Move predictNextMove(GamePack<?> gamePack) = 0;
    
    // Other necessary functions
};

// Class representing an AI using Monte Carlo Tree Search (MCTS)
class MCTSAI : public AI {
public:
    // Override function to predict next move using MCTS
    Move predictNextMove(GamePack<?> gamePack) override;
    
    // Other necessary functions
};

// Class representing an AI using a general graph-based algorithm
class GraphAI : public AI {
public:
    // Override function to predict next move using graph-based algorithm
    Move predictNextMove(GamePack<?> gamePack) override;
    
    // Other necessary functions
};
