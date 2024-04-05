#include <iostream>
#include <iomanip>
#define SWAP(x,y,t) (t=x,x=y,y=t)//交換
using namespace std;
int square[15][15];

void magicsquare_LU(int n);//奇數方陣 起點位置：第一列中間  移動方向：左上  撞到：往下
void magicsquare_RU(int n);//奇數方陣 起點位置：第一列中間  移動方向：右上  撞到：往下
void magicsquare_LD(int n);//奇數方陣 起點位置：最後一列中間  移動方向：左下  撞到：往上
void magicsquare_RD(int n);//奇數方陣 起點位置：最後一列中間  移動方向：右下  撞到：往上
void magicsquare_even(int n);//偶數方陣：可除四的(4M)
void magicsquare_even2(int n);//偶數方陣：不可除四的(4M+2)
void check(int n);//查每行、線相加值是否相同
void print(int n);//輸出幻方

int main ()
{
    int n,method;
    char ans;
    do{
        cout<<"Please enter a number between 3 amd 15!"<<endl;
        do{
            cout<<"You:";
            cin>>n;
            if(n>15||n<3)
                cout<<"The number is out of the range! Please try another!"<<endl;
        }while(n>15||n<3);//輸入值太大或太小
        if(n%2==1)
        {
            cout<<endl;
            cout<<"Please choose the method that you want to use to find the magic square."<<endl<<"Please enter the numebr!!!"<<endl;
            cout<<"1.Starting Point : TOP      Moving Direction: LEFT-TOP"<<endl;
            cout<<"2.Starting Point : TOP      Moving Direction: RIGHT-TOP"<<endl;
            cout<<"3.Starting Point : BOTTOM   Moving Direction: LEFT-BOTTOM"<<endl;
            cout<<"4.Starting Point : BOTTOM   Moving Direction: RIGHT-BOTTOM"<<endl;
            cout<<"You:";
            cin>>method;
            switch(method)
            {
                case 1:
                    magicsquare_LU(n);
                    break;
                case 2:
                    magicsquare_RU(n);
                    break;
                case 3:
                    magicsquare_LD(n);
                    break;
                case 4:
                   magicsquare_RD(n);
                    break;
            }
                
        }
        else if(n%4==0)
            magicsquare_even(n);
        else
            magicsquare_even2(n);
            
            cout<<endl<<endl;
        print(n);
        cout<<endl;
        check(n);
        
        cout<<endl<<"Do you want to find another magic square? "<<endl<<"If YES, please enter 'Y'. Otherwise, please ente 'N'."<<endl<<"You:";
        cin>>ans;
        cout<<endl;
    }while(ans=='Y'||ans=='y');
    
    return 0;
}

void magicsquare_LU(int n)
{
    int i,j,k,l,data;
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            square[i][j]=0;
    }
    i=0;
    j=(n-1)/2;//中間那行
    square[i][j]=1;//第一列中間
    data=2;
    
    while(data<=n*n)
    {
        k=(i-1<0)?n-1:i-1;//if(i-1<0) n-1; else i-1; //第一列的下一格會到最後一列
        l=(j-1<0)?n-1 :j-1;//if(j-1<0) n-1; else j-1; //第一行的下一格會到最後一行
        if(square[k][l]>0)//撞到
            i=(i+1)%n;//%是為了移上去（若撞到最後一列）
        else
        {
            i=k;
            j=l;//k l 表下一格
        }
        square[i][j]=data++;
    }
}

void magicsquare_RU(int n)
{
    int i,j,k,l,data;
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            square[i][j]=0;
    }
    i=0;
    j=(n-1)/2;//中間那行
    square[i][j]=1;//第一列中間
    data=2;
    
    while(data<=n*n)
    {
        k=(i-1<0)?n-1:i-1;// if(i-1<0) n-1; else i-1; //第一列的下一格會到最後一列
        l=(j+1>n-1)?0:j+1;//if(j+1>n-1) 0; else j+1; //最後一行的下一格會到第一行
        if(square[k][l]>0)//撞到
            i=(i+1)%n;//%是為了移上去（若撞到最後一列）
        else
        {
            i=k;
            j=l;//k l 表下一格
        }
        square[i][j]=data++;
    }
}

void magicsquare_LD(int n)
{
    int i,j,k,l,data;
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            square[i][j]=0;
    }
    i=n-1;
    j=(n-1)/2;//中間那行
    square[i][j]=1;//最後一列中間
    data=2;
    
    while(data<=n*n)
    {
        k=(i+1>n-1)?0:i+1;//if(i+1>n+1) 0; else i-1; //最後一列的下一格會到第一列
        l=(j-1<0)?n-1:j-1;//if(j-1<0) n-1; else j-1; //第一行的下一格會到最後一行
        if(square[k][l]>0)//撞到
            i=(i-1)%n;//%是為了移下去（若撞到第一列）
        else
        {
            i=k;
            j=l;//k l 表下一格
        }
        square[i][j]=data++;
    }
}

void magicsquare_RD(int n)
{
    int i,j,k,l,data;
    for (i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            square[i][j]=0;
    }
    i=n-1;
    j=(n-1)/2;//中間那行
    square[i][j]=1;//最後一列中間
    data=2;
    
    while(data<=n*n)
    {
        k=(i+1>n-1)?0:i+1;// if(i+1>n+1) 0; else i-1; //最後一列的下一格會到第一列
        l=(j+1>n-1)?0:j+1;//if(j+1>n-1) 0; else j+1; //最後一行的下一格會到第一行
        if(square[k][l]>0)//撞到
            i=(i-1)%n;//%是為了移下去（若撞到第一列）
        else
        {
            i=k;
            j=l;//k l 表下一格
        }
        square[i][j]=data++;
    }
}

void magicsquare_even(int n)
{
    int m,i,j,count=1,k,l,tmp;
    m=n/4;//將它分割成M*M個4*4的區塊
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            square[i][j]=count;//將1到n*n依序填入
            count++;
        }
    }
    for(k=0;k<m;k++)//一個一個區塊去看
    {
        for(l=0;l<m;l++)
        {
            for(i=k*4;i<4*(k+1);i++)
            {
                for(j=l*4;j<4*(l+1);j++)
                {
                    if((i%4==0)&&(j%4==1||j%4==2))
                        SWAP(square[i][j],square[n-1-i][n-1-j],tmp);//將不在主副對角線上的數對於中心對調
                    if((i%4==1)&&(j%4==0||j%4==3))
                        SWAP(square[i][j],square[n-1-i][n-1-j],tmp);//將不在主副對角線上的數對於中心對調
                }
            }
        }
    }
}

void magicsquare_even2(int n)
{
    int m,i,j,t,tmp;
    m=n/2;//將方陣 分成4區塊奇數方陣 分別為A(左上)、B(右下)、C(右上)、D(左下)
    //先依序將 A、B、C、D 四個位置，依奇數魔方陣規則填入數字，填完後方陣中各行和相同
    magicsquare_RU(m);//A區塊
    for(i=m;i<n;i++)//B區塊
    {
        for(j=m;j<n;j++)
            square[i][j]=square[i-m][j-m]+m*m;
    }
    for(i=0;i<m;i++)//C區塊
    {
        for(j=m;j<n;j++)
            square[i][j]=square[i][j-m]+2*m*m;
    }
    for(i=m;i<n;i++)//D區塊
    {
        for(j=0;j<m;j++)
            square[i][j]=square[i-m][j]+3*m*m;
    }
    t=(n-2)/4;
    for(i=0;i<m;i++)
    {
        if(i!=m/2)//將 A 中每列（中間列除外）頭 t 個元素，與 D 中對應位置元素調換
        {
            for(j=0;j<t;j++)
                SWAP(square[i][j],square[i+m][j],tmp);
        }
        else//將 A 的中央列、中央那一格向左取 t 格，並與 D 中對應位置對調。
        {
            for(j=m/2;j>(m/2-t);j--)
                SWAP(square[i][j],square[i+m][j],tmp);
        }
        for(j=n-1;j>n-1-(t-1);j--)//將 C 中每列的倒數 t - 1 個元素，與 B 中對應元素對調
            SWAP(square[i][n-1],square[i+m][n-1],tmp);
    }
    
}

void check(int n)
{
    int i,j,r[30],c[30],d[2],sum=0,count=0;
    if(n%2==1)
        sum=((n*n+1)/2)*n;//奇數和不可被四整除的偶數加起來每列、行、對角線應為此值
    else
        sum=(((n*n+1)/2)*n)+n/2;//可被4整除的偶數加起來每列、行、對角線應為此值
    
    for(i=0;i<n;i++)
        r[i]=0;
    for(i=0;i<n;i++)
        c[i]=0;
    d[0]=0;
    d[1]=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            r[i]+=square[i][j];//計算該列總和
    }
    for(j=0;j<n;j++)
    {
        for(i=0;i<n;i++)
            c[j]+=square[i][j];//計算該行總和
    }
    for(i=0;i<n;i++)
    {
        d[0]+=square[i][i];//計算左上往右下的對角線總和
    }
    for(i=0;i<n;i++)
    {
        d[1]+=square[i][n-1-i];//計算右上往左下的對角線總和
    }
    for(i=0;i<n;i++)
    {
        if(r[i]==sum)
            count++;
        else cout<<"r["<<i<<"]="<<r[i]<<endl;
    }
    for(i=0;i<n;i++)
    {
        if(c[i]==sum)
            count++;
        else cout<<"c["<<i<<"]="<<c[i]<<endl;
    }
    for(i=0;i<2;i++)
    {
        if(d[i]==sum)
            count++;
        else cout<<"d["<<i<<"]="<<d[i]<<endl;
    }
    cout<<"The sum of each row, column and diagonal should be: "<<sum<<endl;
    if(count==2*n+2)
    {
        cout<<"The sum of each row = "<<sum<<endl;
        cout<<"The sum of each column = "<<sum<<endl;
        cout<<"The sum of each diagonal = "<<sum<<endl;
        cout<<"The Magic Square is CORRECT !!"<<endl;
    }
    else
        cout<<"The Magic Square is INCORRECT !!"<<endl;
}

void print (int n)
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
            cout<<setw(3)<<square[i][j]<<" | ";//畫格線
        cout<<endl<<"-";//畫格線
        for(j=0;j<n;j++)
            cout<<"------";//畫格線
        cout<<endl;
    }
}
