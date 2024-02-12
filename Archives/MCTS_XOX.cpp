#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
private:
    int checkrow(vector<vector<int>> board , int i , int j){
        int val = board[i][j];
        for(int k=0 ; k<3 ; k++){
            if(board[i][k] != val){
                return -1;
            }
        }
        return val;
    }
    int checkcol(vector<vector<int>> board , int i , int j){
        int val = board[i][j];
        for(int k=0 ; k<3 ; k++){
            if(board[k][j] != val){
                return -1;
            }
        }
        return val;
    }
    int checkdiag(vector<vector<int>> board , int i , int j){
        int val = board[i][j];
        if(board[0][0] == val && board[1][1] == val && board[2][2] == val){
            return val;
        }
        if(board[0][2] == val && board[1][1] == val && board[2][0] == val){
            return val;
        }
        return -1;
    }

    //simulation of moves :
    int recur(vector<vector<int>> &board , int turn){
        int val = solve(board);
        if(val != -1){
            if(val == 1){
                return 4;
            }
            else if(val == 0){
                return -2;
            }
            else{
                return 4;
            }
        }
        int ans = 0;
        for(int i=0 ; i<3 ; i++){
            for(int j=0 ; j<3 ; j++){
                if(board[i][j] == -1){
                    board[i][j] = turn;
                    ans +=  recur(board , turn^1) ;
                    board[i][j] = -1;
                }
            }
        }
        return ans;
    }

    

public:
    void display(vector<vector<int>> board) {
        for (auto row : board) {
            cout<<"| ";
            for (auto col : row) {
                if(col == -1)
                    cout << "  | ";
                else if(col == 0)
                    cout << "O | ";
                else if(col == 1)
                    cout << "X | ";
            }
            cout<< endl;
        }
    }

    vector<vector<int>> board(){
        vector<vector<int>> XOX(3 , vector<int>(3, -1));
        return XOX;
    }

    void backpropagation(vector<vector<int>> &board , vector<vector<int>> &dp){
        cout<<"Monte Carlo: "<<endl;
        int maxi = INT_MIN , x = 0 , y = 0;
        //backpropagation of moves :
        for(int i=0 ; i<3 ; i++){
            for(int j=0 ; j<3 ; j++){
                cout<<dp[i][j]<<" ";
                if(dp[i][j] > maxi){
                    maxi = dp[i][j];
                    x = i;
                    y = j;
                }
            }
            cout<<endl;
        }
        cout<<endl;
        board[x][y] = 1;
    }

    void monteCarlo(vector<vector<int>> &board) {
        vector<vector<int>> dp(3 , vector<int>(3, INT_MIN)) ;
        //selection of moves :
        for(int i=0 ; i<3 ; i++){
            for(int j=0 ; j<3 ; j++){
                if(board[i][j] == -1){
                    board[i][j] = 1;
                    //expansion of moves :
                    dp[i][j] = recur(board , 0);
                    board[i][j] = -1;
                }
            }
        }
        backpropagation(board , dp);
        //remove dp 
        dp.clear();
    }


    int solve(vector<vector<int>> board){
        int count = 0; 
        for(int i=0 ; i<3 ; i++){
            for(int j= 0 ; j<3 ; j++){
                if(board[i][j] == -1){
                    continue;
                }
                ++count;
                int val = checkrow(board , i , j);
                if(val != -1){
                    return val;
                }
                val = checkcol(board , i, j);
                if(val != -1){
                    return val;
                }
                if(i==j || i+j==2){
                    val = checkdiag(board ,i , j);
                    if(val != -1){
                        return val;
                    }
                }
            }
        }
        if(count == 9){
            return 2;
        }
        return -1;
    }

    void input(vector<vector<int>> &board){
        int i, j , num; 
        cout<<"Enter the number to input from 1 to 9: ";
        cin>>num;
        i = (num-1)/3;
        j = (num-1)%3;
        if(board[i][j] != -1){
            cout<<"Invalid Input"<<endl;
            input(board);
        }
        else{
            board[i][j] = 0;
        }
    }
    bool displayOption(){
        int x;
        cout<<"select : "<<endl;
        cout<<"1 : you start first ."<<endl;
        cout<<"2 : Machine Starts first ."<<endl;
        cin>>x;
        if(x == 2) return true;
        return false;
    }

};


int main()
{
    Solution s;
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
        s.monteCarlo(board);
        s.display(board);
        Win = s.solve(board);
    }
    if(Win == 0)
        cout << "You Win" << endl;
    else if(Win == 1)
        cout << "You Lose" << endl;
    else
        cout << "Draw" << endl;
    return 0;
}