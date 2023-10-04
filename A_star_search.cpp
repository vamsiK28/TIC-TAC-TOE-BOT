#include<bits/stdc++.h>
using namespace std;
char board[3][3];
void op_board();

char if_win()
{
    char k='-';
    //cout<<1<<endl;
    for(int i=0;i<3;i++)if(board[i][1]==board[i][0] && board[i][1]==board[i][2])if(board[i][0]!='-')return board[i][0];
    //cout<<1<<endl;
    for(int i=0;i<3;i++)if(board[1][i]==board[0][i] && board[1][i]==board[2][i])if(board[0][i]!='-')return board[0][i];
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2]) return board[0][0];
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0]) return board[1][1];
    return k;
}

struct xy{
    int x,y;
    xy(int i,int j){
        x=i;
        y=j;
    }
};

struct ai{
    int heuristic[3][3];
    char symbol='-';
    char t;
    ai(char c){
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)heuristic[i][j]=3;
        heuristic[1][1]=0;
        symbol=c;
    }
    void heur_gen(){
        //test for win case and danger zone
        //cout<<"hi"<<endl;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(board[i][j]=='-')heuristic[i][j]=3;
        //print_huer();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(heuristic[i][j]==INT_MAX) continue;
                //gaurantee x win
                board[i][j]='x';
                t=if_win();
                if(t=='x'){
                    board[i][j]='-';
                    heuristic[i][j]=0;
                    return;
                }
                //gaurantee o win
                board[i][j]='o';
                t=if_win();
                if(t=='o'){
                    board[i][j]='-';
                    heuristic[i][j]=1;
                }
                board[i][j]='-';
            }
        }

        //test for strategy zones
        //cout<<"hi"<<endl;
        bool tri=false;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                    tri=false;
                if(heuristic[i][j]==INT_MAX) continue;
                if(heuristic[i][j]!=3) continue;
                board[i][j]='x';
                heuristic[i][j]=INT_MAX;
                for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        if(heuristic[k][l]==INT_MAX) continue;
                        if(heuristic[k][l]!=3) continue;
                        //if(heuristic[k][l]!=3) continue;
                        board[k][l]='x';
                        if(if_win()=='x'){
                            //cout<<1<<endl;
                            heuristic[k][l]=2;
                            tri=true;
                        }
                        board[k][l]='-';
                    }
                }
                if(tri) heuristic[i][j]=2;
                else heuristic[i][j]=3;
                board[i][j]='-';
                //cout<<"hi "<<i<<j<<endl;
            }
        }

    }

    void placed(int x, int y){
        heuristic[x][y]=INT_MAX;
    }
    void place(){
        int mini;
        heur_gen();
        mini=heuristic[0][0];
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(mini>heuristic[i][j])mini=heuristic[i][j];
        vector<xy> oi;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(heuristic[i][j]==mini){
                    xy dumi(i,j);
                    oi.push_back(dumi);
                }
            }
        }
        int x=oi.size();
        int i=rand()%x;
        heuristic[oi[i].x][oi[i].y]=INT_MAX;
        board[oi[i].x][oi[i].y]='x';
    }
    void print_huer(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)cout<< heuristic[i][j]<<" ";
            cout<<endl;
        }

    }

};

void testseq(ai o){
    /*board[1][0]='x';
    board[1][1]='x';
    board[1][2]='x';
    op_board();
    cout<<if_win()<<endl;
    return;*/
    board[1][1]='x';
    o.heuristic[1][1]=INT_MAX;
    o.heur_gen();
    //cout<<"hi"<<endl;
    o.print_huer();
    board[1][2]='o';
    o.heuristic[1][2]=INT_MAX;
    o.heur_gen();
    o.print_huer();
}

void op_board()
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }
}



bool is_board_full()
{
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(board[i][j]=='-')return false;
    return true;
}

bool WLD()
{
    char k=if_win();
    //cout<<k<<endl;
    if(is_board_full()){
        if(k=='-'){
            cout<<"DRAW"<<endl;
            //op_board();
            return true;
        }

    }
    if(k=='-')
        return false;
    else if(k=='x'){
        cout<<"AI wins"<<endl;
        //op_board();
        return true;
    }
    else if(k=='o'){
        cout<<"Player wins"<<endl;
        //op_board();
        return true;
    }

}

int main(){
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)board[i][j]='-';
    ai o('x');
    //testseq(o);
    //cout<<INT_MAX<<endl;
    //return 0;
    board[1][1]='x';
    o.heuristic[1][1]=INT_MAX;
    int x,y;
    op_board();
    while(true){

        cout<<"Enter place cords: "<<endl;
        while(1){
            cin>>x>>y;
            x-=1;
            y-=1;
            if(board[x][y]=='-'){
                board[x][y]='o';
                o.placed(x,y);
                break;
            }
            else{
                cout<<"invalid option, try again"<<endl;
            }
        }
        op_board();
        //cout<<1<<endl;
        if(WLD())break;
        //cout<<2<<endl;
        cout<<"AI turn: "<<endl;
        o.place();
        op_board();
        //cout<<3<<endl;
        if(WLD())break;
        //cout<<4<<endl;

    }
}
