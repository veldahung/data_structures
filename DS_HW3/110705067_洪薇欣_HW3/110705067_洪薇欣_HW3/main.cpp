#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
using namespace std;
#define posssible_direction 8
struct offset
{
    int dx,dy;//兩個整數視為一體
};
struct offset moves[posssible_direction];//offset當一變數型態
enum directions {N, NE, E, SE, S, SW, W, NW};
struct position
{
    int x,y;
    directions dir;
};
int maze[100][100]={0};
int mark[100][100]={0},End[100][100]={0};
int m,p,top;//m,p為迷宮大小
struct position *Stack;
void move_table();//八個方位初始化
void push(struct position data);//push進堆疊
struct position pop();//pop出堆疊
void readFile(int name);//讀檔
void path();//走迷宮
void print();//印出最初迷宮的樣子
void print0();//印出迷宮走完的樣子
void maze_generate(int m,int p);//確保迷宮至少有一條路可以走
void maze_generate2();//增加迷宮難度
void print1(char A, char B, char C, char D); //選擇用自訂字元、數字輸出
void print2(int a,int b,int c, int d);//選擇用顏色輸出
void print3(int ani);//選擇用動物輸出
void print_select2(int a);//印出顏色輸出的選項 用來查表
void print_select3(int ani, int val);//印出動物輸出的選項 用來查表
 
int main()
{
    int name,num,x,y,a,b,c,d,ani;
    char A,B,C,D;
    int ans;
    double cputime;
    
    cout<<"Do you want to use the maze that is already existed or generate a new maze ?"<<endl;
    cout<<"Use the existed maze, enter 1!"<<"Genarate a new maze, enter 2!" <<endl;
    cout<<"You:";
    cin>>ans;
    if(ans==1)
    {
        cout<<endl<<"Please choose the maze you want to use."<<endl;
        cout<<"Please enter the number between 1~3."<<endl;
        cout<<"You:";
        cin>>name;
        readFile(name);
        print();
    }
    else
    {
        cout<<"Please enter the size of the maze m*p (doesn't enclude the wall)"<<endl;
        cout<<"You:";
        cin>>m>>p;
        m=m+2;
        p=p+2;
        srand(time(NULL));
        for (x=0; x<m; x++)
        {   for (y=0; y<p; y++)
            {
                if (x==0 || y==0 || x==m-1 || y==p-1 )
                    maze[x][y] = 2; // 設定外牆
                else
                    maze[x][y] = 1;  // 初始迷宮內部
            }
        }
        int Start_i=1, Start_j=1, End_i=m-2, End_j=p-2;
        maze_generate(Start_i,Start_j); // 產生迷宮
        maze_generate2();
        maze[End_i][End_j]=0;
        print();
    }
    top=(-1);//初始top
    clock_t t_begin,t_end;//t_begin,t_end變數名 clock_t為變數型態
    t_begin=clock();//clock()在time.h的函數
    path();
    t_end=clock();
    cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
    cout<<endl<<"The result:"<<endl;
    print0();
    cout<<"It tooks the mouse"<<cputime<<"s to finish the maze"<<endl;
    cout<<"Please choose the method you want to print out how the maze was solved:"<<endl;
    cout<<"1. print the maze with the numbers and symbols. (ex.1,2,3,@,#,&) "<<endl<<"2. print the maze with the colors(ex.🟥,🟩,🟦,⬛️) "<<endl<<"3. print the maze with the animals (ex.🐀,🐕,🐘) "<<endl;
    cout<<"You:";
    cin>>num;
    if(num==1)
    {
        cout<<"Please enter the numbers and symbols you want to use. (Four④ in total.In the following order, the walls, the obstacles, the path that the mouse has not been to, and the path that that the mouse has been to.)"<<endl;
        cout<<"You:"<<endl;
        cout<<"Wall:";
        cin>>A;
        cout<<"Obstacle:";
        cin>>B;
        cout<<"Path:";
        cin>>C;
        cout<<"Mouse:";
        cin>>D;
        print1(A,B,C,D);
    }
    else if(num==2)
    {
        cout<<"Please enter the numbers that represent the colors you want to use. (Four④ in total.In the following order, the walls, the obstacles, the path that the mouse has not been to, and the path that that the mouse has been to.)"<<endl;
        cout<<"1.❤️ 2.🧡 3.💛 4.💚 5.💙 6.💜 7.🖤 8.🤍 9.🤎 10.🔴 11.🟠 12.🟡 13.🟢 14.🔵 15.🟣 16.⚫️ 17.⚪️ 18.🟤 19.🟥 20.🟧 21.🟨 22.🟩 23.🟦 24.🟪 25.⬛️ 26.⬜️ 27.🟫"<<endl;
        cout<<"You:"<<endl;
        cout<<"Wall:";
        cin>>a;
        cout<<"Obstacle:";
        cin>>b;
        cout<<"Path:";
        cin>>c;
        cout<<"Mouse:";
        cin>>d;
        print2(a,b,c,d);
    }
    else
    {
        cout<<"Please enter the numbers that represent the colors you want to use."<<endl;
        cout<<"1.Mouse🐭 2.Dog🐶 3.Cat🐱 4.Pig🐷 5.Cow🐮 6.Rabbit🐰 7.Chicken🐔 8.Dolphin🐬 9.Elephant🐘 10.Gorilla🦍 11.Giraffe🦒 12.Sheep🐏 13.Ant🐜 14.Crab🦀 15.Panda🐼"<<endl;
        cout<<"You:";
        cin>>ani;
        print3(ani);
    }
    return 0;
}
 
void move_table()
{
    moves[0].dx=-1;
    moves[0].dy=0;
    moves[1].dx=-1;
    moves[1].dy=1;
    moves[2].dx=0;
    moves[2].dy=1;
    moves[3].dx=1;
    moves[3].dy=1;
    moves[4].dx=1;
    moves[4].dy=0;
    moves[5].dx=1;
    moves[5].dy=-1;
    moves[6].dx=0;
    moves[6].dy=-1;
    moves[7].dx=-1;
    moves[7].dy=-1;
}
 
void push(struct position data)
{
    if (top==9999)//滿了
        cout<<"The stack is full"<<endl;
    else
        Stack[++top]=data;//先++再將資料放入
}
 
struct position pop()
{
    if(top==-1)//防呆
    {
        cout<<"The stack is empty"<<endl;
        return Stack[0];
    }
    else
        return Stack[top--];//資料先回傳才--
}
 
void readFile(int name)
{
    int i, j,c,r;
    if(name==1)
    {
        ifstream f1;
        f1.open("maze1.txt");
        f1>>r>>c;
        m=r+2;
        p=c+2;
        for(i=0;i<m;i++)
        {
            for(j=0;j<p;j++)
            {
                f1>>maze[i][j];
            }
        }
        f1.close();//關檔
    }
    else if(name==2)
    {
        ifstream f1;
        f1.open("maze2.txt");
        f1>>r>>c;
        m=r+2;
        p=c+2;
        for(i=0;i<m;i++)
        {
            for(j=0;j<p;j++)
            {
                f1>>maze[i][j];
            }
        }
        f1.close();//關檔
    }
    else
    {
        ifstream f1;
        f1.open("maze3.txt");
        f1>>r>>c;
        m=r+2;
        p=c+2;
        for(i=0;i<m+2;i++)
        {
            for(j=0;j<p;j++)
            {
                f1>>maze[i][j];
            }
        }
        f1.close();//關檔
    }
}
 
void path()
{
    Stack= new struct position [m*p];
    struct position step;
    int i,j,u,v;
    directions d;
    move_table();
    step.x=1;
    step.y=1;
    step.dir=E;//第一步 北、東北為牆
    push(step);//第一不放stack 免費進入迴圈
    while(top!=-1)//只要stack is not empty
    {
        step=pop();//走不下去 回上一步
        i=step.x;
        j=step.y;
        d=step.dir;
        while (d<=NW)//還有方向可試 走不下去離開
        {
            u=i+moves[d].dx;//八個方向先決定一個 u,v為欲移動的位置 下一步的位置
            v=j+moves[d].dy;
            if((!maze[u][v]) && (!mark[u][v]))//沒走過
            {
                mark [u][v]=1;//標示已走過
                step.x = i;
                step.y = j;
                step.dir =(directions)(d+1);//下一個可能試的方向
                push(step);//放堆疊
                if((u==(m-2))&&(v==(p-2)))//到最後一格
                {
                    int place=top;
                    int tmp;
                    for(tmp=place;tmp>=0;tmp--)
                    {
                        step=pop();//把走過的路印出
                        i=step.x;
                        j=step.y;
                        End[i][j]=3;
                    }
                    for(i=0;i<m;i++)
                    {
                        for(j=0;j<p;j++)
                        {
                            if(End[i][j]!=3)
                                End[i][j]=maze[i][j];
                        }
                    }
                    End[1][0]=3;
                    End[m-2][p-2]=3;
                    End[m-2][p-1]=3;
                    return;
                }
                i=u;//往下一步
                j=v;
                d=N;
 
            }
            else
                d =(directions)(d+1);//是下一方向
        }
    }
    delete [] Stack;
}
 
void print()
{
    int i,j;
    cout<<"-";//畫格線
    for(j=0;j<p;j++)
        cout<<"------";//畫格線
    cout<<endl;
    for(i=0;i<m;i++)
    {
        cout<<"| ";//畫格線
        for (j=0;j<p;j++)
            cout<<setw(3)<<maze[i][j]<<" | ";//畫格線
        cout<<endl<<"-";//畫格線
        for(j=0;j<p;j++)
            cout<<"------";//畫格線
        cout<<endl;
    }
}
 
void print0()
{
    int i,j;
    cout<<"-";//畫格線
    for(j=0;j<p;j++)
        cout<<"------";//畫格線
    cout<<endl;
    for(i=0;i<m;i++)
    {
        cout<<"| ";//畫格線
        for (j=0;j<p;j++)
            cout<<setw(3)<<End[i][j]<<" | ";//畫格線
        cout<<endl<<"-";//畫格線
        for(j=0;j<p;j++)
            cout<<"------";//畫格線
        cout<<endl;
    }
}
 
void maze_generate(int x,int y)
{
    int direction;
    maze[x][y]=0;
    if((x!=m-2)&&(y!=p-2))
    {
        direction = rand()%4+1;  // 決定下一個位置
        if (direction==1)// 向右走
        {
            if(y==1)
            {
                maze[x][y+1] =0;// 向左走
                maze_generate(x,y+1);
            }
            else
            {
                maze[x][y-1] =0; // 拆掉右牆
                maze_generate(x,y-1);
            }
        }
        else if (direction==2) // 向上走
        {
            if(x==1)
            {
                maze[x+1][y] =0;// 向下走
                maze_generate(x+1,y);
            }
            else
            {
                maze[x-1][y] =0; // 拆掉上牆
                maze_generate (x-1,y);
            }
        }
        else if (direction==3) // 向左走
        {
            if(y==(p-2))// 向下走
            {
                maze[x+1][y] =0;
                maze_generate(x+1,y);
            }
            else
            {
                maze[x][y+1] =0; // 拆掉左牆
                maze_generate(x,y+1);
            }
        }
        else if (direction==4) // 向下走
        {
            if(x==(m-2))
            {
                maze[x][y+1] =0; //向左走
                maze_generate(x,y+1);
            }
            else
            {
                maze[x+1][y] =0;// 拆掉下牆
                maze_generate(x+1,y);
            }
        }
        
    }
        
}
    
 
void maze_generate2()
{
    int i,j;
    for(i=1;i<m-1;i++)
    {
        for (j=1;j<p-1;j++)
        {
            if(maze[i][j]!=0)//非已設好的路
                maze[i][j]=rand()%2;
        }
    }
}
 
void print1(char A, char B, char C, char D)
{
    int i,j;
    cout<<"-";//畫格線
    for(j=0;j<p;j++)
        cout<<"------";//畫格線
    cout<<endl;
    for(i=0;i<m;i++)
    {
        cout<<"| ";//畫格線
        for (j=0;j<p;j++)
        {
            if(End[i][j]==2)
                cout<<setw(3)<<A<<" | ";//畫格線
            else if(End[i][j]==1)
                cout<<setw(3)<<B<<" | ";
            else if(End[i][j]==0)
                cout<<setw(3)<<C<<" | ";
            else
                cout<<setw(3)<<D<<" | ";
        }
        cout<<endl<<"-";//畫格線
        for(j=0;j<p;j++)
            cout<<"------";//畫格線
        cout<<endl;
    }
}
 
void print2(int a,int b,int c,int d)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for (j=0;j<p;j++)
        {
            if(End[i][j]==2)
                print_select2(a);
            else if(End[i][j]==1)
                print_select2(b);
            else if(End[i][j]==0)
                print_select2(c);
            else
                print_select2(d);
        }
        cout<<endl;
    }
}
 
void print3(int ani)
{
    int i,j,val;
    for(i=0;i<m;i++)
    {
        for(j=0;j<p;j++)
        {
            int u,v,count=0;
            directions d;
            move_table();
            d=N;
            while (d<=NW)//還有方向可試
            {
                u=i+moves[d].dx;
                v=j+moves[d].dy;
                if(End[u][v]==1)
                    count++;
                d =(directions)(d+1);//是下一方向
            }
            if((count==7)&&(End[i][j]==0))
                End[i][j]=4;
        }
    }
    for(i=0;i<m;i++)
    {
        for (j=0;j<p;j++)
        {
            if((i==1)&&(j==0))
            {
                if(ani==1)
                    cout<<"🐭";
                else if(ani==2)
                    cout<<"🐶";
                else if(ani==3)
                    cout<<"🐱";
                else if(ani==4)
                    cout<<"🐷";
                else if(ani==5)
                    cout<<"🐮";
                else if(ani==6)
                    cout<<"🐰";
                else if(ani==7)
                    cout<<"🐔";
                else
                    cout<<"⛳️";
            }
            else if((i==m-2)&&(j==p-1))
            {
                val=5;
                print_select3(ani,val);
            }
            else if(End[i][j]==2)
            {
                val=2;
                print_select3(ani,val);
            }
            else if(End[i][j]==1)
            {
                val=1;
                print_select3(ani,val);
            }
            else if(End[i][j]==0)
            {
                val=0;
                print_select3(ani,val);
            }
            else if(End[i][j]==3)
            {
                val=3;
                print_select3(ani,val);
            }
            else
            {
                val=4;
                print_select3(ani,val);
            }
                
        }
        cout<<endl;
    }
}
 
void print_select2(int a)
{
    switch(a)
    {
        case 1:
            cout<<"❤️";
            break;
        case 2:
            cout<<"🧡";
            break;
        case 3:
            cout<<"💛";
            break;
        case 4:
            cout<<"💚";
            break;
        case 5:
            cout<<"💙";
            break;
        case 6:
            cout<<"💜";
            break;
        case 7:
            cout<<"🖤";
            break;
        case 8:
            cout<<"🤍";
            break;
        case 9:
            cout<<"🤎";
            break;
        case 10:
            cout<<"🔴";
            break;
        case 11:
            cout<<"🟠";
            break;
        case 12:
            cout<<"🟡";
            break;
        case 13:
            cout<<"🟢";
            break;
        case 14:
            cout<<"🔵";
            break;
        case 15:
            cout<<"🟣";
            break;
        case 16:
            cout<<"⚫️";
            break;
        case 17:
            cout<<"⚪️";
            break;
        case 18:
            cout<<"🟤";
            break;
        case 19:
            cout<<"🟥";
            break;
        case 20:
            cout<<"🟧";
            break;
        case 21:
            cout<<"🟨";
            break;
        case 22:
            cout<<"🟩";
            break;
        case 23:
            cout<<"🟦";
            break;
        case 24:
            cout<<"🟪";
            break;
        case 25:
            cout<<"⬛️";
            break;
        case 26:
            cout<<"⬜️";
            break;
        case 27:
            cout<<"🟫";
            break;
    }
}
 
void print_select3(int ani, int val)
{
    if(val==0)//可以走的路
    {
        switch(ani)
        {
            case 1:
                cout<<"🪴";
                break;
            case 2:
                cout<<"🪴";
                break;
            case 3:
                cout<<"🪴";
                break;
            case 4:
                cout<<"🌱";
                break;
            case 5:
                cout<<"🌱";
                break;
            case 6:
                cout<<"🌱";
                break;
            case 7:
                cout<<"🌱";
                break;
            case 8:
                cout<<"🌊";
                break;
            case 9:
                cout<<"🌿";
                break;
            case 10:
                cout<<"🌲";
                break;
            case 11:
                cout<<"🌳";
                break;
            case 12:
                cout<<"🌱";
                break;
            case 13:
                cout<<"🪴";
                break;
            case 14:
                cout<<"🌊";
                break;
            case 15:
                cout<<"🌲";
                break;
        }
    }
    else if(val==1)//障礙
    {
        switch(ani)
        {
            case 1:
                cout<<"🧱";
                break;
            case 2:
                cout<<"🧱";
                break;
            case 3:
                cout<<"🧱";
                break;
            case 4:
                cout<<"🪵";
                break;
            case 5:
                cout<<"🪵";
                break;
            case 6:
                cout<<"🪵";
                break;
            case 7:
                cout<<"🪵";
                break;
            case 8:
                cout<<"🪨";
                break;
            case 9:
                cout<<"🪨";
                break;
            case 10:
                cout<<"🪨";
                break;
            case 11:
                cout<<"🪨";
                break;
            case 12:
                cout<<"🪵";
                break;
            case 13:
                cout<<"🧱";
                break;
            case 14:
                cout<<"🪨";
                break;
            case 15:
                cout<<"🪵";
                break;
        }
    }
    else if(val==2)//牆
    {
        switch(ani)
        {
            case 1:
                cout<<"🪨";
                break;
            case 2:
                cout<<"🪨";
                break;
            case 3:
                cout<<"🪨";
                break;
            case 4:
                cout<<"🧱";
                break;
            case 5:
                cout<<"🧱";
                break;
            case 6:
                cout<<"🧱";
                break;
            case 7:
                cout<<"🧱";
                break;
            case 8:
                cout<<"🏝";
                break;
            case 9:
                cout<<"⛰";
                break;
            case 10:
                cout<<"⛰";
                break;
            case 11:
                cout<<"⛰";
                break;
            case 12:
                cout<<"🧱";
                break;
            case 13:
                cout<<"🪨";
                break;
            case 14:
                cout<<"🌋";
                break;
            case 15:
                cout<<"⛰";
                break;
        }
    }
    else if(val==3)//走過的路
    {
        switch(ani)
        {
            case 1:
                cout<<"🐀";
                break;
            case 2:
                cout<<"🐾";
                break;
            case 3:
                cout<<"🐈";
                break;
            case 4:
                cout<<"🐖";
                break;
            case 5:
                cout<<"🐄";
                break;
            case 6:
                cout<<"🐇";
                break;
            case 7:
                cout<<"🐓";
                break;
            case 8:
                cout<<"🐬";
                break;
            case 9:
                cout<<"🐘";
                break;
            case 10:
                cout<<"🦍";
                break;
            case 11:
                cout<<"🦒";
                break;
            case 12:
                cout<<"🐏";
                break;
            case 13:
                cout<<"🐜";
                break;
            case 14:
                cout<<"🦀";
                break;
            case 15:
                cout<<"🐼";
                break;
        }
    }
    else if(val==4)//此路不通
    {
        switch(ani)
        {
            case 1:
                cout<<"🐈‍⬛";
                break;
            case 2:
                cout<<"🦁";
                break;
            case 3:
                cout<<"🦊";
                break;
            case 4:
                cout<<"🐯";
                break;
            case 5:
                cout<<"🐻";
                break;
            case 6:
                cout<<"🐍";
                break;
            case 7:
                cout<<"🐺";
                break;
            case 8:
                cout<<"🦈";
                break;
            case 9:
                cout<<"🐁";
                break;
            case 10:
                cout<<"🐆";
                break;
            case 11:
                cout<<"🦁";
                break;
            case 12:
                cout<<"🐅";
                break;
            case 13:
                cout<<"🦜";
                break;
            case 14:
                cout<<"🐙";
                break;
            case 15:
                cout<<"🐯";
                break;
        }
    }
    else//終點
    {
        switch(ani)
        {
            case 1:
                cout<<"🧀";
                break;
            case 2:
                cout<<"🦴";
                break;
            case 3:
                cout<<"🐟";
                break;
            case 4:
                cout<<"🌾";
                break;
            case 5:
                cout<<"🌾";
                break;
            case 6:
                cout<<"🥕";
                break;
            case 7:
                cout<<"🍞";
                break;
            case 8:
                cout<<"🦑";
                break;
            case 9:
                cout<<"🥜";
                break;
            case 10:
                cout<<"🍌";
                break;
            case 11:
                cout<<"🌿";
                break;
            case 12:
                cout<<"🌾";
                break;
            case 13:
                cout<<"🍬";
                break;
            case 14:
                cout<<"🦐";
                break;
            case 15:
                cout<<"🎋";
                break;
        }
    }
        
}

