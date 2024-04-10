#include <iostream>
#include <cmath>
#include <string>
#include "./MySTL/vector.h"

using namespace std;


// AI

template <typename GAME>
class AI {
private:
    GAME& game;

public:
    AI(GAME& game) : game(game) {
        std::cout << "AI initialized" << std::endl;
    }

    void initialize_player() {
        std::cout << "AI initialized" << std::endl;
    }

    std::string get_best_move() {
        std::cout << "GetBestMove " << std::endl;

        Vector<int> valid_moves = game.get_valid_moves();

        // Debugging: Display valid moves
        std::cout << "Valid moves: ";
        for (auto move : valid_moves) {
            std::cout << move << " ";
        }
        std::cout << std::endl;

        // char c;
        // std::cin >> c;

        Vector<double> win_rate;
        for (auto move : valid_moves) {
            // Simulate the move
            Vector<int> res = game.simulate(move, 1);
            cout<<"res[0] : "<<res[0]<<" res[1] : "<<res[1]<<" res[2] : "<<res[2]<<endl;
            int total_games = res[0] + res[1] + res[2];
            
            // Calculate UCB1 (Upper Confidence Bound)
            // double UCB = (res[0] * 2.0 / total_games) +
            //              sqrt(2 * log(total_games) / total_games);
            double UCB = res[0]*1.0/total_games + res[1]*0.8/total_games - res[2]*2.0/total_games;
            
            cout << "Move: " << move << " Win rate: " << res[0] * 1.0 / total_games << " UCB: " << UCB << endl;

            //cin>>c;
            win_rate.push_back(UCB);
        }

        for(auto wins : win_rate){
            cout<<wins<<" ";
        }
        // cin>>c;

        // Find the move with the highest UCB
        int max_index = 0 ;
        for(int i = 0 ; i < win_rate.size() ; i++){
            if(win_rate[i] > win_rate[max_index]){
                max_index = i;
            }
        }

        // Convert the move to string and return
        std::string move = std::to_string(valid_moves[max_index]);
        cout<<"Move : "<<move<<endl;
        return move;
    }
};


// GameEngine 


template <typename GAME, typename... Players>
class GameEngine
{
    static_assert((IsPointerToPlayerDerived<Players>::value && ...), "All Players must be pointers to classes derived from Player");
private:
    GAME game;
    Vector<Player*> players;
    int num_players;
    int turn;

public:
    GameEngine(GAME game,Players... players) : game(game) ,num_players(sizeof...(players)), turn(0) {
        (this->players.push_back(players),...);
       
    }


    void game_loop()
    {
        game.start_game();
        while (true)
        {
            for (int i = 0; i < num_players; i++)
            {
                while(true){
                    std::string move = players[i]->get_move();
                    if(game.play_next(move)){
                        break;
                    }
                }
                int terminal_status = game.game_over();
                if (terminal_status != -1)
                {
                    end_game(terminal_status);
                    return; // Exit the loop when game is over
                }
            }
        }
    }

    void end_game(int condition)
    {
        if(condition != -2){
            std::cout<<"Player "<<players[condition]->get_name()<<" wins"<<std::endl;
        }
        else{
            std::cout<<"It's a draw"<<std::endl;
        }
    }
};


//GameTraits


// Helper type trait to check if a type is a pointer to a class derived from Player
template<typename T>
struct IsPointerToPlayerDerived : std::false_type {};

template<typename T>
struct IsPointerToPlayerDerived<T*> : std::is_base_of<Player, typename std::remove_pointer<T>::type> {};


// Player


class Player
{
protected:
    std::string name;
    //int sequence; ? - what is this for? ans: to keep track of the sequence of the player i.e 1st, 2nd, 3rd etc
public:
    virtual void initialize_player() = 0;
    virtual std::string get_move() = 0;
    virtual std::string get_name() = 0;
};


class HumanPlayer : public Player 
{
    public:
    void initialize_player(){
        std::cout << "Enter the name of the player : ";
        std::cin >> name;
    }

    std::string get_move() 
    {
        cout<<"Player "<<name<<"Turn"<<": ";
        std::string move;
        std::cin >> move;
        return move;
    }

    std::string get_name() 
    {
        return name;
    }

};


template <typename game>
class AiPlayer : public Player {
private:
    AI<game>& ai; // Reference to the Ai object

public:
    AiPlayer(AI<game>& ai) : ai(ai) {} // Constructor takes Ai object by reference

    void initialize_player() override {
        // Nothing to initialize for AiPlayer
    }

    std::string get_name() override {
        return "AiPlayer";
    }

    std::string get_move() override {
        int move = ai.get_best_move();
        return std::to_string(move);
    }
};

// GamePack


template <int players>
class GamePack
{

public:
    int num_players = players;
    int turn;

    template <typename T>
    void simulate(T loc);

    template <typename T>
    Vector<T> get_player_notations();

    template <typename U>
    U get_winner();

    template<typename T>
    Vector<T> get_valid_moves();
    
    virtual void init(){}
    virtual void start_game(){}
    virtual int play_next(string move) = 0;
    virtual int game_over()=0;
    
};




// GameBoard


template <int row, int col, typename T>
class Board
{
protected:
    Vector<Vector<T>> game_board;
    int remaining_moves;
public:
    // Initializes the board
    virtual void init()
    {
        game_board.resize(row);
        for(int i=0;i<row;++i)
        {
            game_board[i] = Vector<T>(col);
        }
        remaining_moves = row * col;
    };

    // Displays the board
    virtual void display(){}

    // Checks if the game is over
    template <typename U>
    U check_terminal();

    // Checks if the move is valid
    template <typename U>
    bool playable(U loc);

    // Makes a move
    template <typename U, typename V>
    void move(U loc, V turn);

    template <typename U>
    Vector<U> get_valid_moves();

    //get and set remaining moves
    int get_remaining_moves(){
        return remaining_moves;
    }
    void set_remaining_moves(){
        remaining_moves--;
    }
};


// TTTBoard

// TTTBoard
class TTTBoard : public Board<3, 3, int>
{
private:


public:
    void init();
    void display();

    template <typename U>
    bool playable(U loc);

    template <typename U>
    U check_terminal();

    template <typename U, typename V>
    void move(U loc, V turn);
    

    Vector<int> get_valid_moves() {
        //display the board 
        // cout<<"Getting valid moves for the board : "<<endl;
        // display();
        Vector<int> valid_moves;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (game_board[i][j] == -1) {
                    valid_moves.push_back(i * 3 + j + 1);
                }
            }
        }
        return valid_moves;
    }

    template<typename T>
    Vector<int> simulate(T loc, int turn) {
        TTTBoard simboard(*this); // Create a copy of the current board
        simboard.move(loc, turn); // Make the move on the copy
        //check if the move is terminal 
        int terminal_state = simboard.check_terminal<int>();
        if(terminal_state != -1){
            Vector<int> result(3, 0);
            if(terminal_state == turn){
                result[0] = 1;
            }
            else if(terminal_state == -2){
                result[1] = 1;
            }
            else{
                result[2] = 1;
            }
            return result;
        }
        Vector<int> result(3, 0);

        // Get valid moves
        Vector<int> valid_moves = simboard.get_valid_moves();
        if(valid_moves.size() == 0){
            result[1] = 1;
            return result;
        }

        // Simulate each possible move
        for (auto move : valid_moves) {
            // Create a copy of the board for each move
            TTTBoard temp_board(simboard);
            temp_board.move(move, (turn + 1) % 2); // Alternate players

            // Check terminal state
            int terminal_state = temp_board.check_terminal<int>();
            if (terminal_state == 1) {
                result[0]++; // Win
            } else if (terminal_state == -1) {
                // Recursively simulate if the game is not over yet
                Vector<int> recursive_result = temp_board.simulate(move, (turn + 1) % 2);
                result[0] += recursive_result[0]; // Wins from recursive simulation
                result[1] += recursive_result[1]; // Draws from recursive simulation
                result[2] += recursive_result[2]; // Losses from recursive simulation
            } else if(terminal_state == -2){
                result[1]++; // Draw
            
            } else {
                result[2]++; // Loss
            }
        }

        return result;
    }


};


void TTTBoard::init()
{
    Board::init();
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            game_board[i][j] = -1;
        }
    }
}

void TTTBoard::display()
{
    for (auto row : TTTBoard::game_board)
    {
        cout << "| ";
        for (auto col : row)
        {
            if (col == -1)
                cout << "  | ";
            else if (col == 0)
                cout << "O | ";
            else if (col == 1)
                cout << "X | ";
        }
        cout << endl;
    }
}

template <>
void TTTBoard::move<int, int>(int loc, int turn)
{
    int row = (loc - 1) / 3;
    int col = (loc - 1) % 3;

    if (game_board[row][col] != -1)
    {
        cout << "Invalid Move" << endl;
    }
    else
    {
        game_board[row][col] = turn;
    }
}


// i swear to god i'll .... , whyyyyyy
// check the typeee you fooollll

template <>
int TTTBoard::check_terminal<int>()
{
    //cout<<"Checking for terminal"<<endl;
    //return 0 -> player 1 , 1->player2 , -2-> draw , -1 -> game not over

    //check for a draw
    if(get_remaining_moves() == 0){
        return -2;
    }

    // Check for rows
    for (int i = 0; i < 3; i++)
    {
        if (game_board[i][0] != -1 && game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2])
        {
            return game_board[i][0];
        }
    }

    // Check for columns
    for (int i = 0; i < 3; i++)
    {
        if (game_board[i][0] != -1 && game_board[0][i] == game_board[1][i] && game_board[1][i] == game_board[2][i])
        {
            return game_board[0][i];
        }
    }

    // Check for diagonals
    if ((game_board[1][1] != -1) && ((game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) || (game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0])))
    {
        return game_board[1][1];
    }

    return -1;
}

template <>
bool TTTBoard::playable<int>(int loc)
{
    if(loc < 1 || loc > 9){
        return false;
    }
    int row = (loc - 1) / 3;
    int col = (loc - 1) % 3;
    return game_board[row][col] == -1;
}



// TicTacToe

class TTT : public GamePack<2>
{
private:
    TTTBoard board;
    Vector<int> player_notation;
    int turn = 0;


public:
    typedef int MOVE;
    typedef int PLAYER_NOTATION;
    typedef int STATE;

    TTT()
    { 
        for (int i=0 ; i<num_players ; ++i){
            player_notation.push_back(i);
        }
        board.init();
    }

    int process_move(string input);

    void render_board() ;

    void start_game() override;

    int game_over() override;

    void init() override;

    int play_next(string move) override;

    int get_turn() ;

    TTTBoard get_board();

    template <typename T>
    Vector<T> get_player_notations();

    template <typename U>
    U get_winner();

    //getting the valid_moves from TTTBoard
    Vector<int> get_valid_moves(){
        return board.get_valid_moves();
    }

    Vector<int> simulate(int loc , int turn){
        return board.simulate(loc,turn);
    }

};

int TTT::process_move(string input)
{
    return std::stoi(input);
}

TTTBoard TTT::get_board(){
    return board;
}

// beautify the board display
void TTT::render_board() 
{
    board.display();
}

// Game Starting anything that needs to be done before the game starts
void TTT::start_game()
{
    render_board();
}

void TTT::init(){
    board.init();

}

int TTT::game_over()
{
    return board.check_terminal<TTT::STATE>();
}

int TTT::play_next(string input)
{
    int move = process_move(input);
    if (!board.playable<TTT::MOVE>(move))
    {
        cout << "Invalid Move" << endl;

        return 0;
    }

    board.move(move, player_notation[turn]);
    turn = (turn + 1) % num_players;
    board.set_remaining_moves();
    render_board();
    return 1;
}


int TTT::get_turn()
{
    return turn;
}



template <typename U>
U TTT::get_winner()
{
    int check = board.check_terminal<int>();
    if (check == -1)
        return -1;
    for (int i = 0; i < player_notation.size(); i++)
    {
        if (player_notation[i] == check)
        {
            return i;
        }
    }
}

template <>
Vector<TTT::PLAYER_NOTATION> TTT::get_player_notations<TTT::PLAYER_NOTATION>()
{
    return player_notation;
}



int main() {

  TTT gamePack ;
  HumanPlayer h1,h2;
  //initializing the Aiplayer with the ai object 
  AI<TTT> ai(gamePack);
  ai.initialize_player();
  h1.initialize_player();
  //AiPlayer<Ai<TTT>> a1(ai); // call in the AiPlayer constructor and pass the reference of the ai object
  //GameEngine<TTT,HumanPlayer*,AiPlayer<Ai<TTT>>*> engine1(gamePack,&h1,&a1);

  gamePack.start_game();

  while(gamePack.game_over() == -1){
    string move = h1.get_move();
    gamePack.play_next(move);
    if(gamePack.game_over() != -1){
      break;
    }
    move = ai.get_best_move();
    gamePack.play_next(move);
  }

  //AiPlayer<Ai<TTTBoard>,TTTBoard> a1(ai);

/*
  int choice;
  cout<<"Choose the game mode : "<<endl;
  cout<<"1. Human vs Human or"<<"2. Human vs AI"<<endl;
  cin>>choice;

  if(choice == 1){
    h1.initialize_player();
    h2.initialize_player();
    GameEngine<TTT,HumanPlayer*,HumanPlayer*> engine1(gamePack,&h1,&h2);
    engine1.game_loop();
  }
  else if(choice == 2){
    h1.initialize_player();
    AiPlayer<TTTBoard> a1(ai);
    GameEngine<TTT,HumanPlayer*,AiPlayer<TTTBoard>*> engine2(gamePack,&h1,&a1);
    engine2.game_loop();
  }
  else{
    cout<<"Invalid choice"<<endl;
  }
*/
  return 0;
}