#include<iostream>
#include<bits/stdc++.h>

#include"./Engine Files/Game.h"

using namespace std;



int main()
{
    Game s;
    int Win = -1 , moves = 0;
    vector<vector<int>> board = s.board();

    if(s.displayOption()){
        board[1][1] = 1;
    }

    s.display(board);
    while(Win == -1 ) {
        cout<<endl<<"Your Turn: "<<endl;
        s.input(board);
        ++moves;
        s.display(board);
        Win = s.solve(board);
        if(Win != -1 )    
            break;
        cout<<endl<<"Computer's Turn: "<<endl;
        // s.monteCarlo(board);
        // s.display(board);
        // Win = s.solve(board);
        s.input(board);
        s.display(board);
        Win = s.solve(board);
        if(Win != -1 )    
            break;
    }
    if(Win == 0)
        cout << "You Win" << endl;
    else if(Win == 1)
        cout << "You Lose" << endl;
    else
        cout << "Draw" << endl;
    return 0;
}