# include <iostream>
# include <stdio.h>
#include <iomanip>
using namespace std;

struct coordinate
{
    int dx,dy;
};

struct step
{
    int x,y;
};

struct move
{
    struct step position;
    int moves;
};

struct coordinate offset[8];
struct move Next[8];
int k[50][50];
int n;

void initial();
struct step nextmove(struct step Step,int k);
void print();
void knighttour(struct step Step);

int main()
{
    struct step start;
    char ans;
    initial();
    do
    {
        cout<<"Please enter the size of the knight tour"<<endl<<"n = ";
        cin>>n;
        cout<<"Please enter the staring point of the knight tour"<<endl<<"x = ";
        cin>>start.x;
        cout<<"y = ";
        cin>>start.y;
        knighttour(start);
        cout<<"Try another one? If yes, enter y. Else, enter n."<<endl<<"You:";
        cin>>ans;
    }while(ans=='Y'||ans=='y');
    
}

void initial()
{
    offset[0].dx=-2;
    offset[0].dy=1;
    offset[1].dx=-1;
    offset[1].dy=2;
    offset[2].dx=1;
    offset[2].dy=2;
    offset[3].dx=2;
    offset[3].dy=1;
    offset[4].dx=2;
    offset[4].dy=-1;
    offset[5].dx=1;
    offset[5].dy=-2;
    offset[6].dx=-1;
    offset[6].dy=-2;
    offset[7].dx=-2;
    offset[7].dy=-1;
    
}

struct step nextmove(struct step Step,int t)
{
    struct step test;
    test.x = Step.x+offset[t].dx;
    test.y = Step.y+offset[t].dy;
    return test;
}

void print ()
{
    int i,j;
    cout<<"-";//畫格線
    for(j=0;j<n;j++)
        cout<<"------";//畫格線
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"| ";//畫格線
        for (j=0;j<n;j++)
            cout<<setw(3)<<k[i][j]<<" | ";//畫格線
        cout<<endl<<"-";//畫格線
        for(j=0;j<n;j++)
            cout<<"------";//畫格線
        cout<<endl;
    }
}

void knighttour(struct step Step)
{
    int i,j,count,data,t,p,min,datasquare;
    datasquare=n*n;
    struct step test;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            k[i][j]=0;
    }
    k[Step.x][Step.y]=1;
    for(data=2;data<=datasquare;data++)
    {
        for(count=0,t=0;t<8;t++)
        {
            test=nextmove(Step,t);
            if(((test.x >= 0) && (test.x < n)) && ((test.y >= 0 )&& (test.y < n))&&(k[test.x][test.y]==0))
            {
                Next[count].position=test;
                count++;
            }
        }
        
        if(count==0)
            break;
        
        for(p=0;p<count;p++)
        {
            Step=Next[p].position;
            Next[p].moves=0;
            for(t=0;t<8;t++)
            {
                test=nextmove(Step,t);
                if(((test.x >= 0) && (test.x < n)) && ((test.y >= 0 )&& (test.y < n))&&(k[test.x][test.y]==0))
                {
                    Next[p].moves++;
                }
            }
        }
        
        min=0;
        for(i=1;i<count;i++)
        {
            if(Next[i].moves<Next[min].moves)
                min=i;
        }
        Step=Next[min].position;
        k[Step.x][Step.y]=data;
    }
    if(data>datasquare)
    {
        print();
    }
    else
        cout<<"No knight tour"<<endl;
}

