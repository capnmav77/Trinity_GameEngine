#include "mcts.h"



int check_lig(ivec_t state){
    for (int i = 0; i < NBC*NBL; i+=3)
    {
        if (state[i] == PLAYER_ONE &&
            state[i+1] == PLAYER_ONE &&
            state[i+2] == PLAYER_ONE)
        {
            return PLAYER_ONE;
        }
        else if (state[i] == PLAYER_TWO &&
                state[i+1] == PLAYER_TWO &&
                state[i+2] == PLAYER_TWO)
        {
            return PLAYER_TWO;
        }
    }
    return NO_PLAYER;
}

int check_col(ivec_t state){ 
    for (int i = 0; i < NBL; i++)
    {
        if (state[i] == PLAYER_ONE &&
            state[i+3] == PLAYER_ONE &&
            state[i+6] == PLAYER_ONE)
        {
            return PLAYER_ONE;
        }
        else if (state[i] == PLAYER_TWO &&
                state[i+3] == PLAYER_TWO &&
                state[i+6] == PLAYER_TWO)
        {
            return PLAYER_TWO;
        }
    }
    return NO_PLAYER;
}



int check_diag(ivec_t state){
    int const pos[]={0,8,2,6};
    for (int i = 0; i < 4; i+=2)
    {
        if (state[4] == PLAYER_ONE &&
            state[pos[i]] == PLAYER_ONE &&
            state[pos[i+1]] == PLAYER_ONE)
        {
            return PLAYER_ONE;
        }
        else if (state[4] == PLAYER_TWO &&
            state[pos[i]] == PLAYER_TWO &&
            state[pos[i+1]] == PLAYER_TWO)
        {
            return PLAYER_TWO;
        }
    }
    return NO_PLAYER;
}

bool check_full(ivec_t state){
    for (int i = 0; i < NBL*NBC; i++)
    {
        if (state[i] == 0){
            return false;
        }    
    }
    return true;
}



int is_terminal(ivec_t state){
    int c = 0;
    if ((c = check_col(state)) != 0){
        return c;
    }
    if ((c = check_lig(state)) != 0){
        return c;
    }
    if ((c = check_diag(state)) != 0){
        return c;
    }
    return c;
}



int get_winner(ivec_t state){
    return is_terminal(state);
}
void print_vec(ivec_t v){
    
}

ivec_t get_state(ivec_t s, int m, int p){
    ivec_t sp = s;
    ivec_t::iterator i = sp.begin()+m;
    if (sp[m] == 0){
        (*i) = p;
    }
    return sp;
}

int get_next_player(int current_player){
    if (current_player == PLAYER_ONE)
        return PLAYER_TWO;
    return PLAYER_ONE;
}



board_t get_next_board(board_t b, int m){
    board_t t;
    t.state = get_state(b.state, m, b.next_player);
    t.next_player = get_next_player(b.next_player);
    t.move = m;
    t.winner = get_winner(t.state);
    t.full = check_full(t.state);
    return t;
}


ivec_t get_next_moves(ivec_t state){
    ivec_t nexts;
    int n = 0;
    ivec_t::iterator i = state.begin();
    for(; i != state.end(); ++i, ++n){
        if ((*i) == 0){
            nexts.push_back(n);
        }
    }
    return nexts;
}
