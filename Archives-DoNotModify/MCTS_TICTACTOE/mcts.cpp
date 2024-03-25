#include "mcts.h"


double get_uct(node_t *node){
    if (node->n == 0){
        return 1000.0;
    }
    int n, ni;
    double wi;
    n = node->parent->n;
    ni = node->n;
    wi = node->v;
    return (double) wi / ni + 0.4 * sqrt(log(ni)/n); 
}


node_t *selection(node_t *root){
    double uct, max = -1.0;
    node_t *best = root;
    if (root->n == 0 && root->expand){
        return root;
    }
    nvec_t::iterator i = root->childs.begin();
    for (;i != root->childs.end(); ++i){
        uct = get_uct(&(*i));
        if (uct > max){
            best = &(*i);
            max = uct;
        }
    }
    if (best->nbc != 0)
        return selection(best);
    return best;
}



void make_moves(node_t *node){

    node_t n;
    board_t b;
    ivec_t nexts = get_next_moves(node->state.state);
    ivec_t::iterator i=nexts.begin();
    for(; i < nexts.end(); ++i){
        b = get_next_board(node->state, (*i));
        n.state = b;
        n.parent = node;
        n.nbc = 0;
        n.n = 0;
        n.v = 0.0;
        if (n.state.full == true || n.state.winner != 0){
            n.expand = false;
        }
        else n.expand = true;
        node->childs.push_back(n);
    }
    node->nbc = (int)nexts.size();
    
}


node_t *expansion(node_t *node){
    node_t *best = node;
    if (best->n == 0 && best->expand && best->parent != NULL){
        return best;
    }
    make_moves(best);
    return &(best->childs[0]);
}

void print_board(board_t board){
    
    cout << "---------------------------" << endl;
    cout << "next_player: " << board.next_player << endl;
    cout << "winner: " << board.winner << endl;
    cout << "full: " << ((board.full == true)?"true":"false") << endl;
    int v;
    for(int i = 0; i < NBL; ++i)
    {
        for (int j = 0; j < NBC; ++j){
            v = board.state[i * NBC + j];
            printf("%c",((v) == 0) ? '.' : ((v) == 1)?'X':'O');
        }
        printf("\n");
    }
    cout << endl;
}


double playout(board_t board){
    board_t tmp = board;
    ivec_t nexts;
    int size, rnd;
    double result = 0;
    if (tmp.winner != 0 || tmp.full)
        return tmp.winner;
    for (int i = 0; i < 100; ++i){
        tmp = board;     
        while(true){
            nexts = get_next_moves(tmp.state);
            size = (int)nexts.size();
            rnd = rand()%size;
            tmp = get_next_board(tmp, nexts[rnd]);
            if (tmp.winner != 0 || tmp.full == true){
                result += tmp.winner;
                break;
            }
        }
    }
    return (double)result / 100;
}

void backpropagation(node_t *node, double score){
    node->v += score;
    node->n++;
    if (node->parent == NULL){
        return;
    } 
    backpropagation(node->parent, score);
}

int best_next(node_t *node){
    double uct, max = -1.0;
    node_t *best=NULL;
    nvec_t::iterator i = node->childs.begin();
    for (; i != node->childs.end(); ++i){
        if (node->state.next_player == PLAYER_TWO)
            uct = get_uct(&(*i))*(-1);
        else uct = get_uct(&(*i));
        if(uct > max){
            max = uct;
            best = &(*i);
        }
    }
    return best->state.move;
}



int mcts(board_t board){
    node_t node;
    double tmp;
    node.state = board;
    node.n = 0;
    node.v = 0;
    node.nbc = 0;
    node.parent = NULL;
    node_t *s1 = &node, *s2 = NULL;
    for (;;){
        s1 = selection(&node);
        s2 = expansion(s1);
        if (!s2->expand) break;
        tmp = playout(s2->state);
        backpropagation(s2, tmp); 
        
    }
    return best_next(&node);
}
