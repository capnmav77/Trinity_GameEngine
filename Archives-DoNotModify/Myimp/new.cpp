#include <iostream>
using namespace std;
#include <malloc.h>
#include <math.h>
#include <set>
#include <stack>
#include <time.h>
#include <vector>
#include <deque>
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef pair<int,int> PR;

const int int_MAX = 999999;
const int int_MIN = -999999;
const double max_HEUR = 1.0;
const double min_HEUR = -1.0;

int ans_x, ans_y;
int temp_x, temp_y;
int DEPTH;
int INCRE;
int MAX_DEPTH;
clock_t start;

double Hf = 0.005;
int THRESHOLD=10;
double C = sqrt(2.0);
double PBf = 5.0;
int PBe =  3;


class Board
{
public:
    int grid[3][3];
    bool done;
    int result;

public:
    Board()
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                grid[i][j]=0;
            }
        }
        done=false;
        result=0;
    }

    Board(Board *obj)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                grid[i][j]= (obj->grid[i][j]);
            }
        }
        done= obj->done;
        result= obj->result;
    }

    void modify()
    {
        int i,j;
        if(grid[0][0]==grid[0][1] && grid[0][1]==grid[0][2])
        {
            if(grid[0][0]!=0)
            {
                done = true;
                result = grid[0][0];
                return;
            }
        }
        if(grid[1][0]==grid[1][1] && grid[1][1]==grid[1][2])
        {
            if(grid[1][0]!=0)
            {
                done = true;
                result = grid[1][0];
                return;
            }
        }
        if(grid[2][0]==grid[2][1] && grid[2][1]==grid[2][2])
        {
            if(grid[2][0]!=0)
            {
                done = true;
                result = grid[2][0];
                return;
            }
        }
        if(grid[0][0]==grid[1][0] && grid[1][0]==grid[2][0])
        {
            if(grid[0][0]!=0)
            {
                done = true;
                result = grid[0][0];
                return;
            }
        }
        if(grid[0][1]==grid[1][1] && grid[1][1]==grid[2][1])
        {
            if(grid[0][1]!=0)
            {
                done = true;
                result = grid[0][1];
                return;
            }
        }
        if(grid[0][2]==grid[1][2] && grid[1][2]==grid[2][2])
        {
            if(grid[0][2]!=0)
            {
                done = true;
                result = grid[0][2];
                return;
            }
        }
        if(grid[0][0]==grid[1][1] && grid[1][1]==grid[2][2])
        {
            if(grid[0][0]!=0)
            {
                done = true;
                result = grid[0][0];
                return;
            }
        }
        if(grid[2][0]==grid[1][1] && grid[1][1]==grid[0][2])
        {
            if(grid[1][1]!=0)
            {
                done = true;
                result = grid[1][1];
                return;
            }
        }
        bool flag=true;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(grid[i][j]==0)
                {
                    flag=false;
                    i=4;
                    break;
                }
            }
        }
        if(flag)
        {
            done=true;
            result=0;
        }
    }

    void move(int i, int j, int cl)
    {
        grid[i][j]=cl;
        modify();
    }

    int find_board_heuristic()
    {
        if(done)
        {
            return (result*5);
        }

        int ans=0;

        ans += (3*grid[1][1]);

        for(int i=0;i<3;i++)
        {
            int summ=0;
            for(int j=0;j<3;j++)
            {
                summ += grid[i][j];
            }
            if(summ==2 || summ==-2)ans+=summ;
        }

        for(int i=0;i<3;i++)
        {
            int summ=0;
            for(int j=0;j<3;j++)
            {
                summ += grid[j][i];
            }
            if(summ==2 || summ==-2)ans+=summ;
        }
        
        int summ=0;
        summ += grid[0][0]; summ += grid[1][1]; summ += grid[2][2];
        if(summ==2 || summ==-2)ans+=summ;
        summ=0;
        summ += grid[2][0]; summ += grid[1][1]; summ += grid[0][2];
        if(summ==2 || summ==-2)ans+=summ;

        return ans;

    }

};

class Node
{

public:
    Board arr[3][3];
    //double heuristic;
    bool done;
    int grid[3][3];
    int result;
    int prevx, prevy;
    int next_turn;

public:
    
    Node()
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j] = Board();
                grid[i][j]=0;
            }
        }
        done = false;
        //heuristic=0;    
        result = 0; 
        prevx = -1;
        prevy = -1;
        next_turn=1;
    }

    Node(Node *obj)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j] = Board(&(obj->arr[i][j]));
                grid[i][j] = obj->grid[i][j];
            }
        }
        done = obj->done;
        //heuristic= obj->heuristic;  
        result = obj->result;   
        prevx = obj->prevx;
        prevy = obj->prevy;
        next_turn = obj->next_turn;
        //heuristic = find_heuristic();        
    }


    Node(int px, int py)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j] = Board();
                grid[i][j]=0;
            }
        }
        done = false;
        //heuristic=0;    
        result = 0; 
        prevx = px;
        prevy = py;
        next_turn=1;
    }

    Node(Node *obj, int px, int py, int cl)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j] = Board(&(obj->arr[i][j]));
                grid[i][j] = obj->grid[i][j];
            }
        }
        done = obj->done;
        //heuristic= obj->heuristic;  
        result = obj->result;   
        prevx = px%3;
        prevy = py%3;
        move(px,py,cl);
        next_turn = cl*(-1);
        //heuristic = find_heuristic();        
    }

    
    void modify()
    {
        if(grid[0][0]==grid[0][1] && grid[0][1]==grid[0][2])
        {
            if(grid[0][0]!=0)
            {
                done = true;
                result = grid[0][0];
                return;
            }
        }
        if(grid[1][0]==grid[1][1] && grid[1][1]==grid[1][2])
        {
            if(grid[1][0]!=0)
            {
                done = true;
                result = grid[1][0];
                return;
            }
        }
        if(grid[2][0]==grid[2][1] && grid[2][1]==grid[2][2])
        {
            if(grid[2][0]!=0)
            {
                done = true;
                result = grid[2][0];
                return;
            }
        }
        if(grid[0][0]==grid[1][0] && grid[1][0]==grid[2][0])
        {
            if(grid[0][0]!=0)
            {
                done = true;
                result = grid[0][0];
                return;
            }
        }
        if(grid[0][1]==grid[1][1] && grid[1][1]==grid[2][1])
        {
            if(grid[0][1]!=0)
            {
                done = true;
                result = grid[0][1];
                return;
            }
        }
        if(grid[0][2]==grid[1][2] && grid[1][2]==grid[2][2])
        {
            if(grid[0][2]!=0)
            {
                done = true;
                result = grid[0][2];
                return;
            }
        }
        if(grid[0][0]==grid[1][1] && grid[1][1]==grid[2][2])
        {
            if(grid[0][0]!=0)
            {
                done = true;
                result = grid[0][0];
                return;
            }
        }
        if(grid[2][0]==grid[1][1] && grid[1][1]==grid[0][2])
        {
            if(grid[1][1]!=0)
            {
                done = true;
                result = grid[1][1];
                return;
            }
        }
        bool flag=true;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(arr[i][j].done==false)
                {
                    flag=false;
                    i=4;
                    break;
                }
            }
        }
        if(flag)
        {
            done=true;
            result=0;
        }
    }

    void move(int i, int j, int cl)
    {
        arr[(i/3)][(j/3)].move((i%3),(j%3),cl);
        if(arr[(i/3)][(j/3)].done==true)
        {
            grid[(i/3)][(j/3)] = arr[(i/3)][(j/3)].result;
            modify();
        }

    }

    int find_moves(PR moves[])
    {
        int count=0;
        int x,y;
        x=prevx;
        y=prevy;
        if( x>=0 && (arr[x][y].done==false) )
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    if(arr[x][y].grid[i][j]==0)
                    {
                        moves[count].first = 3*x +i;
                        moves[count].second = 3*y +j;
                        count++;
                    }
                }
            }
            return count;
        }
        else
        {   
            for(x=0;x<3;x++)
            {
                for(y=0;y<3;y++)
                {
                    if(arr[x][y].done)continue;
                    for(int i=0;i<3;i++)
                    {
                        for(int j=0;j<3;j++)
                        {
                            if(arr[x][y].grid[i][j]==0)
                            {
                                moves[count].first = 3*x +i;
                                moves[count].second = 3*y +j;
                                count++;
                            }
                        }
                    }
                }
            }
            return count;
        }

    }

    void find_moves2(vector<PR> V)
    {
        V.clear();
        int x,y;
        x=prevx;
        y=prevy;
        if( x>=0 && (arr[x][y].done==false) )
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    if(arr[x][y].grid[i][j]==0)
                    {
                        int a = 3*x +i;
                        int b = 3*y +j;
                        V.push_back( PR(a,b) );
                    }
                }
            }
            return;
        }
        else
        {   
            for(x=0;x<3;x++)
            {
                for(y=0;y<3;y++)
                {
                    if(arr[x][y].done)continue;
                    for(int i=0;i<3;i++)
                    {
                        for(int j=0;j<3;j++)
                        {
                            if(arr[x][y].grid[i][j]==0)
                            {
                                int a = 3*x +i;
                                int b = 3*y +j;
                                V.push_back( PR(a,b) );
                            }
                        }
                    }
                }
            }
        }

    }

    void find_moves3(vector<PR> *V)
    {
        (*V).clear();
        int x,y;
        x=prevx;
        y=prevy;
        if( x>=0 && (arr[x][y].done==false) )
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    if(arr[x][y].grid[i][j]==0)
                    {
                        int a = 3*x +i;
                        int b = 3*y +j;
                        (*V).push_back( PR(a,b) );
                    }
                }
            }
            return;
        }
        else
        {   
            for(x=0;x<3;x++)
            {
                for(y=0;y<3;y++)
                {
                    if(arr[x][y].done)continue;
                    for(int i=0;i<3;i++)
                    {
                        for(int j=0;j<3;j++)
                        {
                            if(arr[x][y].grid[i][j]==0)
                            {
                                int a = 3*x +i;
                                int b = 3*y +j;
                                (*V).push_back( PR(a,b) );
                            }
                        }
                    }
                }
            }
        }

    }

    double find_heuristic()
    {
        if(done)
        {
            if(result==1)
            {
                return max_HEUR;
            }
            if(result==0)
            {
                return 0;
            }
            else
            {
                return min_HEUR;
            }
        }

        int ans=0;
        ans += grid[1][1]*10;

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(arr[i][j].done)
                {
                    ans += grid[i][j]*5;
                    if( (i==0 && j==0) || (i==0 && j==2) || (i==2 && j==0) || (i==2 && j==2) )
                    {
                        ans += grid[i][j]*3;
                    }
                }
                else
                {
                    int temp = arr[i][j].find_board_heuristic();
                    if(i==1 && j==1)
                    {
                        for(int tx=0;tx<3;tx++)
                        {
                            for(int ty=0;ty<3;ty++)
                            {
                                temp += (arr[1][1].grid[tx][ty]*3);
                            }
                        }
                    }
                    ans += temp;
                }
            }
        }

        for(int i=0;i<3;i++)
        {
            int summ=0;
            for(int j=0;j<3;j++)
            {
                summ += grid[i][j];
            }
            if(summ==2 || summ==-2)ans+= summ*2;
        }

        for(int i=0;i<3;i++)
        {
            int summ=0;
            for(int j=0;j<3;j++)
            {
                summ += grid[j][i];
            }
            if(summ==2 || summ==-2)ans+= summ*2;
        }
        
        int summ=0;
        summ += grid[0][0]; summ += grid[1][1]; summ += grid[2][2];
        if(summ==2 || summ==-2)ans+= summ*2;
        summ=0;
        summ += grid[2][0]; summ += grid[1][1]; summ += grid[0][2];
        if(summ==2 || summ==-2)ans+= summ*2;

        if( ! ( prevx>=0 && (arr[prevx][prevy].done==false) ) )
        {
            if(next_turn==1)ans+=2;
            else ans-=2;
        }

        double temppp = ans;
        return temppp*Hf;

    }

};

typedef class Node Treenode;

// simulation is (almost) completely random :|
int simulate(Treenode *node1)          
{
    Treenode node = Treenode(node1);
    while(!node.done)
    {
        if(node.prevx>=0 && (!node.arr[node.prevx][node.prevy].done) )
        {
            int rndx=rand()%3, rndy=rand()%3;
            while(node.arr[node.prevx][node.prevy].grid[rndx][rndy]!=0)
            {
                rndx=rand()%3; rndy=rand()%3;
            }
            node.move(node.prevx*3+rndx,node.prevy*3+rndy,node.next_turn);
            node.prevx=rndx;node.prevy=rndy;
            node.next_turn *= -1;
        }
        else
        {
            int brdx=rand()%3,brdy=rand()%3,rndx=rand()%3,rndy=rand()%3;
            while(node.arr[brdx][brdy].done)
            {
                brdx=rand()%3; brdy=rand()%3;
            }
            while(node.arr[brdx][brdy].grid[rndx][rndy]!=0)
            {
                rndx=rand()%3; rndy=rand()%3;
            }
            node.move(brdx*3+rndx,brdy*3+rndy,node.next_turn);
            node.prevx=rndx;node.prevy=rndy;
            node.next_turn *= -1;
        }
    }
    return node.result;
} 

class MCTS_node
{
public:
    Treenode node;
    int ni;
    double bi;
    double vi; 
    double fni;
    int wi;
    int li;
    double uct_val;
    class MCTS_node* child[81];
    int child_count;
    class MCTS_node* parent;

public:
    MCTS_node(Treenode *obj, int px, int py, int cl, class MCTS_node *pnode)
    {
        node = Treenode(obj, px, py, cl);
        ni=wi=li=0;
        vi=0;
        bi=node.find_heuristic();
        fni=((pow(bi,PBe)*PBf)/(ni+1));
        uct_val = fni;
        child_count=0;
        for(int i=0;i<81;i++)child[i]=NULL;
        //uct_val = vi + fni + (C*sqrt( (pnode->ni) / ni ));
        parent = pnode;
        //child.clear();
    }

    MCTS_node(Treenode *obj, int px, int py, int cl)
    {
        node = Treenode(obj, px, py, cl);
        ni=wi=li=0;
        vi=0;
        bi=node.find_heuristic();
        fni=((pow(bi,PBe)*PBf)/(ni+1));
        uct_val = fni;
        child_count=0;
        for(int i=0;i<81;i++)child[i]=NULL;
        //uct_val = vi + fni + (C*sqrt( (pnode->ni) / ni ));
        parent=NULL;
        //child.clear();
    }

    MCTS_node(Treenode *obj)
    {
        node = Treenode(obj);
        ni=wi=li=0;
        vi=0;
        bi=0;
        uct_val=fni=0;
        child_count=0;
        for(int i=0;i<81;i++)child[i]=NULL;
        //bi=node.find_heuristic();
        //fni=((pow(bi,PBe)*PBf)/(ni+1));
        //uct_val = fni;
        //uct_val = vi + fni + (C*sqrt( (pnode->ni) / ni ));
        //parent=NULL;
        //child.clear();
    }

    void update_uct_val_pl()
    {
        vi = (wi-li)/(double)ni ;
        fni=((pow(bi,PBe)*PBf)/((double)(ni+1)));
        uct_val = vi + fni + (C*sqrt( (parent->ni) / (double)ni ));
    }

    void update_uct_val_opp()
    {
        vi = (wi-li)/(double)ni ;
        fni=((pow(bi,PBe)*PBf)/((double)(ni+1)));
        uct_val = vi + fni + (C*sqrt( (parent->ni) / (double)ni ));
        uct_val *= - 1.0;
    }

    void do_simulation(int k, int *ww, int *ll, int *nn)
    {
        int i;
        for(i=0;i<k;i++)
        {
            int temp = simulate(&node);
            ni++;
            (*nn)++;
            if(temp==1){wi++;(*ww)++;}
            else if(temp==-1){li++;(*ll)++;}
        }
    }

};

typedef class MCTS_node mcts_node;


mcts_node* new_MCTS_node(Treenode *obj, int px, int py, int cl, class MCTS_node *pnode)
{
    mcts_node* temp = NULL;
    temp = (mcts_node*)malloc(sizeof(mcts_node));
    *temp = mcts_node(obj,px,py,cl,pnode);
    return temp;
}
mcts_node* new_MCTS_node(Treenode *obj)
{
    mcts_node* temp = NULL;
    temp = (mcts_node*)malloc(sizeof(mcts_node));
    *temp = mcts_node(obj);
    return temp;
}

void find_missing_move(mcts_node* a, mcts_node* b, int *x, int *y)
{
    int i,j,k,l;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                for(l=0;l<3;l++)
                {
                    if(a->node.arr[i][j].grid[k][l]!=b->node.arr[i][j].grid[k][l])
                    {
                        (*x) = 3*i + k;
                        (*y) = 3*j +l;
                    }
                }
            }
        }
    }
    return;
}

void MCTS(Treenode *head, double max_time_per_move, clock_t move_start)
{
    mcts_node* Root = new_MCTS_node(head);
    int doubt = 100;
    //Root->child.clear();
    PR candidates[81];
    int ghgh = head->find_moves(candidates);
    Root->child_count= ghgh;
    int it_index=0;
    int aa=0, bb=0, cc=0;
    for(;it_index< Root->child_count;it_index++)
    {
        Root->child[it_index] = new_MCTS_node(&(Root->node),candidates[it_index].first,candidates[it_index].second,1,Root);
        if((Root->child[it_index])->node.done)
            {
                if(Root->child[it_index]->node.result==1)
                    {aa += doubt; (Root->child[it_index])->wi = doubt;}
                else if(Root->child[it_index]->node.result==-1)
                    {bb += doubt; (Root->child[it_index])->li = doubt;}
                {cc += doubt; (Root->child[it_index])->ni = doubt;}
            }
        else
            {
                Root->child[it_index]->do_simulation(THRESHOLD, &aa, &bb, &cc);
            }
            // int x,y;
            // find_missing_move(Root,Root->child[it_index],&x,&y);
            //cout<<x<<" "<<y<<endl;
        //cout<<Root->child[it_index]->wi<<" "<<Root->child[it_index]->li<<endl;
        //cout<<Root->child[it_index]->child_count;
        //cout<<aa<<" "<<bb<<" "<<cc<<endl;
        //cout<<mv_it->first<<" "<<mv_it->second<<endl;
    }
    Root->wi+= aa;
    Root->li+= bb;
    Root->ni+= cc;
    //cout<<aa<<" "<<bb<<" "<<cc<<endl;

    int node_count=1;
    // while(1)
    // {
    //     //time constraint
    //     clock_t curr = clock();
    //     double d = (double)(curr-move_start)/(double)CLOCKS_PER_SEC;
    //     if(d>max_time_per_move+0.05)
    //     {
    //         //do action
    //         break;
    //     }
    //     //very good and enough criteria

    while(1)
    {
        // selection
        clock_t curr_time = clock();
        double time_taken_so_far = (double)(curr_time - move_start)/(double)CLOCKS_PER_SEC;
        if(time_taken_so_far>max_time_per_move)
        {
            break;
        }
        mcts_node* temp_select;
        temp_select = Root;
        bool type=true;
        bool flag = false;
        while(temp_select->child_count>=1)
        {
            if(type)
            {   
                mcts_node* ans=NULL;
                double max_uct = -9999998;
                for(int kl=0 ; kl<temp_select->child_count;kl++)
                {
                    //if( (*child_it)==NULL ){cout<<"adqr qq";}
                    (temp_select->child[kl])->update_uct_val_pl();
                    if( (temp_select->child[kl])->uct_val > max_uct && !(temp_select->child[kl])->node.done)
                    {
                        ans = (temp_select->child[kl]);
                        max_uct = (temp_select->child[kl])->uct_val;
                    }

                }
                if(ans!=NULL)
                    {temp_select = ans; }
                else
                {
                    temp_select->node.done=true;
                    flag= true;
                    break;
                }
            }
            else
            {
                mcts_node* ans=NULL;
                double min_uct = 9999998;
                vector<mcts_node*>::iterator child_it;
                for(int kl=0 ; kl<temp_select->child_count;kl++)
                {
                    //if( (*child_it)==NULL ){cout<<"adqr qq";}
                    (temp_select->child[kl])->update_uct_val_opp();
                    if( (temp_select->child[kl])->uct_val < min_uct && !(temp_select->child[kl])->node.done)
                    {
                        ans = (temp_select->child[kl]);
                        min_uct = (temp_select->child[kl])->uct_val;
                    }

                }
                if(ans!=NULL)
                temp_select = ans;
                else
                {
                    temp_select->node.done=true;
                    flag= true;
                    break;
                }
            }
            type = !type;
        }
        if(temp_select==Root){break;}
        
        if(flag)
        {
            
            if(temp_select==Root){break;}
            //back propogation for determined selected node
            while(temp_select->parent!=Root)
            {
                temp_select->wi += doubt;
                temp_select->li += doubt;
                temp_select->ni += doubt;
                temp_select = temp_select->parent;
            }
            temp_select->wi += doubt;
            temp_select->li += doubt;
            temp_select->ni += doubt;
            //cout<<temp_select->ni<<endl;
            Root->wi += doubt;
            Root->li += doubt;
            Root->ni += doubt;
            //cout<<"used"<<endl;
            continue;
        }
        //expansion
        PR moves[81];
        //moves.clear();
        //if(temp_select==Root){cout<<"1"<<endl;}
        int dist_count=temp_select->node.find_moves(moves);
        //cout<<dist_count<<endl;
        //vector<PR>::iterator move_it;
        temp_select->child_count=0;
        int win_select=0, losses_select=0, total_new_games_select=0;
        int xxx=0;
        for(int da=0;da<dist_count;da++)
        {   
            //node_count++;
            //cout<<node_count<<endl;
            int cl = (type)? 1 : -1;
            temp_select->child[xxx]=new_MCTS_node( &(temp_select->node),moves[da].first,moves[da].second,cl, temp_select);
            //cout<<temp_select->child[xxx]->node.arr[1][1].grid[0][1]<<" gr"<<endl;
            temp_select->child_count++;
            //int x,y;
            //find_missing_move(temp_select,temp_select->child[xxx],&x,&y);
            //cout<<x<<" : "<<y<<endl;
            if((temp_select->child[xxx])->node.done)
            {
                //cout<<"1";
                if( (temp_select->child[xxx])->node.result==1 )
                    {win_select += doubt; (temp_select->child[xxx])->wi += doubt;}
                else if( (temp_select->child[xxx])->node.result==-1)
                    {losses_select += doubt; (temp_select->child[xxx])->li += doubt;}
                else
                {total_new_games_select += doubt; (temp_select->child[xxx])->ni += doubt;}
                //cout<<"used"<<endl;
                //cout<<"2";
            }
            else
            {
                (temp_select->child[xxx])->do_simulation(THRESHOLD, &win_select, &losses_select, &total_new_games_select);
            }
            xxx++;
            //cout<<xxx<<" d da"<<endl;
        }
        //cout<<"efwf wf";
        //back propogation
        //cout<<temp_select->parent!=NULL;
        while(temp_select->parent!=Root)
        {
            //cout<<"f";
            
            temp_select->wi += win_select;
            temp_select->li += losses_select;
            temp_select->ni += total_new_games_select;
            //cout<<temp_select->ni<<endl;
            temp_select = temp_select->parent;
        }
        temp_select->wi += win_select;
        temp_select->li += losses_select;
        temp_select->ni += total_new_games_select;
        //cout<<temp_select->ni<<endl;
        //cout<<endl;
        //cout<<"end";
        Root->wi += win_select;
        Root->li += losses_select;
        Root->ni += total_new_games_select;
   
    
        

    }

    //cout<<node_count<<endl;

    //final best move selection
    mcts_node* final_move_node=NULL;
    double max_selection = -9999999.0;
    int no_of_candidates = Root->child_count;
    //cout<<Root->ni<<endl;
    for(int abc=0; abc<no_of_candidates;abc++)
    {
        Root->child[abc]->update_uct_val_pl();
        //cout<<Root->child[abc]->ni;
        double val_i = (Root->child[abc])->vi + ((Root->child[abc]->ni))/(double)Root->ni;
        if(val_i>max_selection || (Root->child[abc])->vi>0.999)
        {
            max_selection = val_i;
            final_move_node = (Root->child[abc]);
        }
        int move_x=0, move_y=0;
        find_missing_move(Root->child[abc], Root, &move_x, &move_y);
        //cout<<move_x<<" "<<move_y<<"  "<<val_i<<" "<<Root->child[abc]->ni<<endl;
    }


    int final_move_x=0, final_move_y=0;
    find_missing_move(final_move_node, Root, &final_move_x, &final_move_y);
    //cout<<final_move_x<<" "<<final_move_y<<endl;
    ans_x = final_move_x;
    ans_y = final_move_y;


}





int main() {

    srand(time(NULL)) ;
    THRESHOLD=15;
    start=clock();
    char cl;
    cin>>cl;
    char opp;
    opp = (cl=='X')?'O':'X';
    //cout<<opp<<endl;
    int board_x, board_y;
    cin>>board_x>>board_y;
    //cout<<board_x<<board_y<<endl;
    char main_grid[11][11];
    int main_int_grid[9][9];
    Treenode head = Treenode(board_x, board_y);
    Board main_board_arr[3][3];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            main_board_arr[i][j] = Board();
        }
    }
    for(int i=0;i<9;i++)
    {
        //scanf("%c", &main_grid[i][j]);
            //printf("%c", main_grid[i][j]);
            char temp[15];
            scanf("%s", temp);
            //printf("%s", temp);
            for(int j=0;j<9;j++)
            {
                int res_boardx, res_boardy, cordx, cordy;
                res_boardx = i/3;
                res_boardy = j/3;
                cordx=i%3;
                cordy=j%3;
                if(temp[j]==cl)
                {
                    main_int_grid[i][j] = 1;
                    head.move(i,j,1);
                    main_board_arr[res_boardx][res_boardy].grid[cordx][cordy]=1;
                }
                else if(temp[j]== opp)
                {
                    main_int_grid[i][j] = -1;
                    head.move(i,j,-1);
                    main_board_arr[res_boardx][res_boardy].grid[cordx][cordy]=-1;
                }
                else
                {
                    main_int_grid[i][j] = 0;
                    main_board_arr[res_boardx][res_boardy].grid[cordx][cordy]=0;
                }
            }
        
        
    }
    
    
    // for(int i=0;i<9;i++)
    // {
    //  for(int j=0;j<9;j++)
    //  {
    //      ;//cout<<(head.arr[i/3][j/3].grid[i%3][j%3]);
    //  }
    //  //cout<<endl;
    // }
    

    // MAX_DEPTH=30;
    // INCRE=1;
    head.next_turn=1;
    //cout<<board_x<<" "<<board_y<<endl;
    //head.prevx=board_x;
    //head.prevy=board_y;
    PR movess[90];
    int cnnt = head.find_moves(movess);
    if(cnnt==0)
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(main_int_grid[i][j]==0)
                {
                    ans_x=i;
                    ans_y=j;
                    cout<<(ans_x/3)<<" "<<(ans_y/3)<<" "<<(ans_x%3)<<" "<<(ans_y%3)<<endl;
                    return 0;
                }
            }
            //cout<<endl;
        }
    }
    //alphabeta_control(&head);
    //cout<<ans_x<<" "<<ans_y<<endl;
    MCTS(&head,0.980,start);
    cout<<(ans_x/3)<<" "<<(ans_y/3)<<" "<<(ans_x%3)<<" "<<(ans_y%3)<<endl;
    //cout<<DEPTH<<endl;
    return 0;
}