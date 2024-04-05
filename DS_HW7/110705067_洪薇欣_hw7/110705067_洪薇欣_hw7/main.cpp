#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int **w;
int n,range,max_range,largeint;

void generate_w_1();//單向
void generate_w_2();//雙向
int mindistance(int d[], bool found[]);
void shortestpath(int u,int t);
void allpairs();
void allpairs_ssad(int t);
void transitiveclosure();
void printssad(int d[]);
void printallp();



int main()
{
    int i,j,s,g,t;
    cout<<"Choose the kind of graph you wanted to generate (Enter the number): 1.directed graph 2.undirected graph."<<endl<<"Graph:";
    cin>>g;
    cout<<"Randomly generated:"<<endl;
    cout<<"n=";
    cin>>n;
    cout<<"range(w(e))=";
    cin>>range;
    cout<<"if w(e) >";
    cin>>max_range;
    cout<<"w(e) =";
    cin>>largeint;
    if(g==1)
        generate_w_1();
    else
        generate_w_2();
    for(j=0;j<n+1;j++)
        cout<<"------";
    cout<<endl;
    cout<<"|  "<<setw(3)<<" | ";
    for(j=0;j<n;j++)
        cout<<setw(3)<<j<<" | ";
    cout<<endl;
    for(j=0;j<n+1;j++)
        cout<<"------";
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"| ";
        cout<<i<<" | ";
        for (j=0;j<n;j++)
            cout<<setw(3)<<w[i][j]<<" | ";
        cout<<endl;
        for(j=0;j<n+1;j++)
            cout<<"------";
        cout<<endl;
    }
    cout<<"Trace the process of solving this problem ? If yes,enter 1. Else, enter 0."<<endl;
    cin>>t;
    cout<<"Please enter the source for single source all destination:"<<endl<<"source:";
    cin>>s;
    cout<<"SSAD:"<<endl;
    shortestpath(s,t);
    cout<<"ALL PAIRS:"<<endl;
    allpairs();
    allpairs_ssad(t);
    cout<<endl<<"TRANSITIVE CLOSURE:"<<endl;
    transitiveclosure();
    return 0;
    
}

void generate_w_1()
{
    int i,j;
    if(w!=NULL)
    {
        for(i=0;i<n;i++)
        {
            delete w[i];
        }
        delete w;
    }
    w=new int*[n];
    for(i=0;i<n;i++)
    {
        w[i]=new int [n];
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            w[i][j]=rand()%range+1;
            if(w[i][j]>max_range)
                w[i][j]=largeint;
        }
        w[i][i]=0;
    }
}

void generate_w_2()
{
    int i,j;
    if(w!=NULL)
    {
        for(i=0;i<n;i++)
        {
            delete w[i];
        }
        delete w;
    }
    w=new int*[n];
    for(i=0;i<n;i++)
    {
        w[i]=new int [n];
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            w[i][j]=rand()%range+1;
            if(w[i][j]>max_range)
                w[i][j]=largeint;
        }
        w[i][i]=0;
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            w[j][i]=w[i][j];
        }
        
    }
}

int mindistance(int d[], bool found[])
{
    int min = largeint, min_index=0;
    for (int i = 0; i < n; i++)
        if (found[i] == false && d[i] < min)
        {
            min = d[i];
            min_index = i;
        }
    return min_index;
}

void  shortestpath(int u,int t)
{
    int j,count,k,v,a,b,i;
    int max=n*n;
    int d[max],e[max];
    int c[max][max];
    bool found[max];
    string r;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            c[i][j]=w[u][i];
        }
    }
    for(j=0;j<n;j++)
    {
        d[j]=w[u][j];
        e[j]=u;
        found[j]=false;
    }
    found[u]=true;
    d[u]=0;
    for(count=0;count<n-2;count++)
    {
        k = mindistance(d,found);
        found[k]=true;
        for(v=0;v<n;v++)
        {
            if(!found[v]&&(d[k]+w[k][v]<d[v]))
            {
                d[v]=d[k]+w[k][v];
                e[v]=k;
                for(i=k;i<n;i++)
                {
                    c[v][i]=d[v];
                }
            }
        }
        if(t==1)
        {
            cout<<"min-->"<<k<<endl;
            for(v=0;v<n;v++)
            {
                cout<<"From "<<u<<" to "<<v<<" is "<<d[v]<<endl;
            }
            cout<<endl;
        }
    }
    for(v=0;v<n;v++)
    {
        if(v!=u&&d[v]!=largeint)
        {
            r="-->"+to_string(v);
            for(b=v,a=e[b];a!=u;b=a,a=e[b])
            {
                r="-->"+to_string(a)+"--["+to_string(w[a][b])+"]"+r;
            }
            cout<<"The shortest distance from "<<u<<" to "<<v<<" is "<<d[v]<<" with path ";
            cout<<to_string(u)+"--["+to_string(w[u][b])+"]"+r<<endl;
        }
        else if(d[v]==largeint)
            cout<<"No path from "<<u<<" to "<<v<<endl;
    }
    cout<<endl<<"SSAD table:"<<endl;
    int m=n;
    int square[m][m];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            square[i][j]=c[i][j];
        }
    }
    for(j=0;j<m+2;j++)
        cout<<"------";
    cout<<endl;
    cout<<"|  "<<setw(3)<<" | ";
    for(j=0;j<m;j++)
        cout<<setw(3)<<j<<" | ";
    cout<<setw(3)<<"from | ";
    cout<<endl;
    for(j=0;j<m+2;j++)
        cout<<"------";
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"| ";
        cout<<i<<" | ";
        for (j=0;j<n;j++)
            cout<<setw(3)<<square[i][j]<<" | ";
        cout<<setw(3)<<e[i]<<" | "<<endl;
        for(j=0;j<m+2;j++)
            cout<<"------";
        cout<<endl;
    }
    cout<<endl;
}

void allpairs()
{
    int i,j,k;
    int max=n;
    int a[max][max];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=w[i][j];
        }
    }
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
            }
        }
    }
    int m=n;
    int square[m][m];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            square[i][j]=a[i][j];
        }
    }
    for(j=0;j<m+1;j++)
        cout<<"------";
    cout<<endl;
    cout<<"|  "<<setw(3)<<" | ";
    for(j=0;j<m;j++)
        cout<<setw(3)<<j<<" | ";
    cout<<endl;
    for(j=0;j<n+1;j++)
        cout<<"------";
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"| ";
        cout<<i<<" | ";
        for (j=0;j<n;j++)
            cout<<setw(3)<<square[i][j]<<" | ";
        cout<<endl;
        for(j=0;j<m+1;j++)
            cout<<"------";
        cout<<endl;
    }
    cout<<endl;
}

void allpairs_ssad(int t)
{
    int max=n*n;
    int p[max][max];
    int j,count,k,v,a,b,i;
    int d[max],e[max];
    int c[max][max];
    bool found[max];
    string r;
    for(int u=0;u<n;u++)
    {
        cout<<"Source:"<<u<<endl;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                c[i][j]=w[i][j];
            }
        }
        for(j=0;j<n;j++)
        {
            d[j]=c[u][j];
            e[j]=u;
            found[j]=false;
        }
        found[u]=true;
        d[u]=0;
        for(count=0;count<n-2;count++)
        {
            k = mindistance(d,found);
            found[k]=true;
            for(v=0;v<n;v++)
            {
                if(!found[v]&&(d[k]+w[k][v]<d[v]))
                {
                    d[v]=d[k]+w[k][v];
                    e[v]=k;
                }
            }
            if(t==1)
            {
                cout<<"min-->"<<k<<endl;
                for(v=0;v<n;v++)
                {
                    cout<<"From "<<u<<" to "<<v<<" is "<<d[v]<<endl;
                }
                cout<<endl;
            }
        }
        for(v=0;v<n;v++)
        {
            if(v!=u&&d[v]!=largeint)
            {
                r="-->"+to_string(v);
                for(b=v,a=e[b];a!=u;b=a,a=e[b])
                {
                    r="-->"+to_string(a)+"--["+to_string(w[a][b])+"]"+r;
                }
                cout<<"The shortest distance from "<<u<<" to "<<v<<" is "<<d[v]<<" with path ";
                cout<<to_string(u)+"--["+to_string(w[u][b])+"]"+r<<endl;
                
            }
            else if(d[v]==largeint)
                cout<<"No path from "<<u<<" to "<<v<<endl;
        }
        cout<<endl;
        for(i=0;i<n;i++)
        {
            if(u==i)
                p[u][i]=u;
            else
                p[u][i]=e[i];
        }
    }
    cout<<"ALL PAIRS table:"<<endl;
    int m=n;
    int square[m][m];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            square[i][j]=p[i][j];
        }
    }
    for(j=0;j<m+1;j++)
        cout<<"------";
    cout<<endl;
    cout<<"|  "<<setw(3)<<" | ";
    for(j=0;j<m;j++)
        cout<<setw(3)<<j<<" | ";
    cout<<endl;
    for(j=0;j<n+1;j++)
        cout<<"------";
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"| ";
        cout<<i<<" | ";
        for (j=0;j<n;j++)
            cout<<setw(3)<<square[i][j]<<" | ";
        cout<<endl;
        for(j=0;j<m+1;j++)
            cout<<"------";
        cout<<endl;
    }
   
}

void transitiveclosure()
{
    int i,j,k;
    int max=n;
    bool a[max][max];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(w[i][j]<largeint)
                a[i][j]=true;
            else
                a[i][j]=false;
        }
    }
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                a[i][j]=(a[i][j]||(a[i][k]&&a[k][j]));
            }
        }
    }
    int m=n;
    int square[m][m];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            square[i][j]=a[i][j];
        }
    }
    for(j=0;j<m+1;j++)
        cout<<"------";
    cout<<endl;
    cout<<"|  "<<setw(3)<<" | ";
    for(j=0;j<m;j++)
        cout<<setw(3)<<j<<" | ";
    cout<<endl;
    for(j=0;j<n+1;j++)
        cout<<"------";
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"| ";
        cout<<i<<" | ";
        for (j=0;j<n;j++)
            cout<<setw(3)<<square[i][j]<<" | ";
        cout<<endl;
        for(j=0;j<m+1;j++)
            cout<<"------";
        cout<<endl;
    }
}
