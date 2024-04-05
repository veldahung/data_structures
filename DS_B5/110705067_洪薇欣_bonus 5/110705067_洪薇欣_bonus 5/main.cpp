#include <iostream>
#include <string>
#include <iomanip>
#define SWAP(x,y,t) (t=x,x=y,y=t)
using namespace std;

int **w, **m, *heap, *mine, *mask,*mst_k,*d,*ed,*tm;
int n,range,max_range,largeint,g;


void generate_w();//雙向
void print_w();
int count_edge();
void copy_w();
void restore(int s,int t,int heap[][2]);
void heapsort();
void kruskal();
void prim(int X);
void merge(int c[], int k, int a[], int i, int h, int b[], int j, int n);
void merge_sort(int a[],int left, int right);


int main()
{
    char ans;
    int i,X;
    clock_t t_begin,t_end;
    double cputime;
    cout<<"Graph:"<<endl;
    cout<<"Randomly generated:"<<endl;
    cout<<"n=";
    cin>>n;
    cout<<"range(w(e))=";
    cin>>range;
    cout<<"if w(e) >";
    cin>>max_range;
    cout<<"w(e) =";
    cin>>largeint;
    generate_w();
    cout<<"Print the graph? If yes, enter Y. Else, enter N"<<endl;
    cin>>ans;
    if(ans=='Y'||ans=='y')
        print_w();
    cout<<"Please enter the starting point for Prim's algorithm"<<endl;
    cin>>X;
    cout<<"Kruskal:"<<endl;
    t_begin=clock();
    kruskal();
    t_end=clock();
    cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
    cout<<"Kruskal : "<<cputime<<"s"<<endl;
    cout<<"Print the MST for Kruskal's algorithm? If yes, enter Y. Else, enter N"<<endl;
    cin>>ans;
    if(ans=='Y'||ans=='y')
    {
        for(i=0;i<n-1;i++)
        {
            cout<<m[mst_k[i]][0]<<" - "<<m[mst_k[i]][1]<<" : "<<m[mst_k[i]][2]<<endl;
        }
    }
    cout<<endl<<"Prim:"<<endl;
    t_begin=clock();
    prim(X);
    t_end=clock();
    cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
    cout<<"Prim : "<<cputime<<"s"<<endl;
    cout<<"Print the MST for Prim's algorithm? If yes, enter Y. Else, enter N"<<endl;
    cin>>ans;
    if(ans=='Y'||ans=='y')
    {
        cout<<"Starts from : "<<X<<endl;
        for(i=0;i<n;i++)
        {
            if(i!=X)
                cout<<i<<" - "<<ed[i]<<" : "<<d[i]<<endl;
        }
    }
    return 0;
}

void generate_w()
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

void print_w()
{
    int i,j;
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
}

int count_edge()
{
    int i,j,count=0;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(w[i][j]>0&&w[i][j]<largeint)
                count++;
        }
    }
    return count;
}

void copy_w()
{
    int e,i,j,t=0;
    e=count_edge();
    m=new int*[e];
    for(i=0;i<e;i++)
    {
        m[i]=new int [3];
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(w[i][j]>0&&w[i][j]<largeint)
            {
                m[t][0]=i;
                m[t][1]=j;
                m[t][2]=w[i][j];
                t++;
            }
        }
    }
}

/*void restore(int s, int t)
{
    int tmp;
    int i=s,j;
    while(i<=t/2)
    {
        if(m[heap[2*i]][3]>m[heap[2*i+1]][3])
            j=2*i;
        else
            j=2*i+1;
        if(m[heap[i]][3]>m[heap[j]][3])
            break;
        SWAP(heap[i],heap[j],tmp);
        i=j;
    }
}

void heapsort()
{
    int e,i;
    e=count_edge();
    heap=new int [e+2];
    mine=new int [e];
    for(i=1;i<=e;i++)
    {
        heap[i]=i-1;
    }
    for(i=e/2;i>=1;i--)
        restore(i,e);
    for(i=e;i>1;i--)
    {
        mine[i-1]=heap[1];
        heap[1]=heap[i];
        restore(1,i-1);
        
    }
}*/

void merge(int c[], int k, int a[], int i, int h, int b[], int j, int n)
{
    int p;
    for(p=i;p<=h;p++)
        tm[p]=a[p];
    for(p=j;p<=n;p++)
        tm[p]=b[p];
    while((i<=h)&&(j<=n))
    {
        if(m[tm[i]][2]<=m[tm[j]][2])
            c[k++]=tm[i++];
        else
            c[k++]=tm[j++];
    }
    while(i<=h) c[k++]=tm[i++];
    while(j<=n) c[k++]=tm[j++];
}

void merge_sort(int a[],int left, int right)
{
    int h;
    if(left<right)
    {
        h=(left+right)/2;
        merge_sort(a,left,h);
        merge_sort(a,h+1,right);
        merge(a,left,a,left,h,a,h+1,right);
    }
}

void kruskal()
{
    int u,v,min,small,large,e,i,t=0,h,k=0,a=n*n;
    e=count_edge();
    copy_w();
    tm=new int [a];
   mine=new int [e];
    for(i=0;i<e;i++)
        mine[i]=i;
    merge_sort(mine,0,e-1);
    //heapsort();
    h=e;
    mask=new int[n];
    mst_k=new int[n];
    for(i=0;i<n;i++)
        mask[i]=i;
    while((t<n-1)&&(h!=0))
    {
        min=mine[k];
        u=m[min][0];
        v=m[min][1];
        h--;
        if(mask[u]!=mask[v])
        {
            mst_k[t++]=min;
            small=(mask[u]<mask[v]) ? mask[u]:mask[v];
            large=(mask[u]<mask[v]) ? mask[v]:mask[u];
            for(i=0;i<n;i++)
            {
                if(mask[i]==large) mask[i]=small;
            }
        }
        k++;
        
    }
    if(t<n-1)
        cout<<"No spanning tree in G"<<endl;
    else
        cout<<"Minimum spanning tree is found"<<endl;
}

void prim(int X)
{
    int *x,*visited;
    int i,j,v,u,min,s,t=0,k=0;
    x=new int [n];
    visited=new int [n];
    ed=new int[n];
    d=new int [n];
    for(i=0;i<n;i++)
    {
        visited[i]=0;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==j)
                w[i][j]=largeint;
        }
    }
    x[t]=X;
    visited[X]=1;
    t++;
    for(i=0;i<n;i++)
    {
        ed[i]=X;
        d[i]=largeint;
    }
    while(t<n)
    {
        for(i=0;i<n;i++)
        {
            if((w[X][i]<d[i])&&(visited[i]==0))
            {
                ed[i]=X;
                d[i]=w[X][i];
            }
        }
        min=largeint;
        for(i=0;i<n;i++)
        {
            if(d[i]<min&&(visited[i]==0))
            {
                s=i;
                min=d[i];
            }
        }
        v=s;
        if(d[v]==largeint)
            break;
        u=ed[v];
        x[t++]=v;
        visited[v]=1;
        X=v;

    }
    if(t<n)
        cout<<"No spanning tree in G"<<endl;
    else
        cout<<"Minimum spanning tree is found"<<endl;
    
}
