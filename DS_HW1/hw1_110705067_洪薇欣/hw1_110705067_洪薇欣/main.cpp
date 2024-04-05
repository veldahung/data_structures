#include <iostream>
#include <stdio.h>
#include <stdlib.h> //亂數相關函數
#include <time.h>//計算cpu時間用 產生亂數用
#include <stdlib.h>//計算cpu時間用
#define SWAP(x,y,t) (t=x,x=y,y=t)//macro 交換數值用的
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1)
/*
 define COMPARE(x,y) 等同於下列程式
 int compare(int x,int y)
 {
    if(x<y) return -1;
    else if(x==8) return 0;
    else return 1;
 }
 */
using namespace std;

void input (int n,int r,int data[]);//輸入亂數資料
void print (int n,int list[]);//輸出資料
void sort(int n,int s,int list[],int method[],double cputime[],int i);//決定用何種排序方式 並進行排序
void selection_sort (int n,int list[]);
void bubble_sort (int n,int list[]);
void quick_sort (int list[],int left,int right);
void insertion_sort (int n,int list[]);
int binary_search (int list[],int searchnum,int left,int right);
void exchange (int data[], int list[],int n);//用於儲存data內的數字到list 避免資料覆蓋 這樣每種不同排序方法都要用時 排序皆是用未排序的資料進行排序
void time_comepare (int method[],double cputime[],int i);//比較通一筆為排列資料 不同排序方法 cpu的執行時間
void self_check (int list[],int n);//自行檢查排序是否正確

int main()
{
    int n,r,data[100000]={0},list[1000000]={0},s,method[30]={0},i,num,success;
    double cputime[30]={0.0};
    char ans;
    do{
        do{
            cout<<"Please input the amount (0<n<100000) of random number you want to sort:"<<endl;
            cout<<"You:";
            cin>>n;//要產生的亂數個數
            if(0>=n||n>100000)
                cout<<endl<<"Please try anothe number!"<<endl<<endl;
        }while(0>=n||n>100000);
        cout<<endl;
        do{
            cout<<"Please input the range (0<r<100000) of random number you want to sort:"<<endl;
            cout<<"You:";
            cin>>r;//亂數產生範圍
            if(0>=r||r>100000)
                cout<<endl<<"Please try anothe number!"<<endl<<endl;
        }while(0>=r||r>100000);
        srand( time(NULL) );
        input(n,r,data);
        cout<<endl<<"Complete random data generating!"<<endl;
        cout<<"Do you want to print the random data?"<<endl<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
        cout<<"You:";
        cin>>ans;
        cout<<endl;
        if(ans=='y'||ans=='Y')
        {
            cout<<"The random data:"<<endl;
            print(n,data);
            cout<<endl;
        }
        cout<<endl;
        i=0;//i紀錄共選擇了幾種排序方式
        do{

            cout<<"Please choose a sort algorithm (enter the number):"<<endl;
            cout<<"1. Selection Sort"<<endl<<"2. Bubble Sort"<<endl<<"3. Quick Sort"<<endl<<"4. Insertion Sort"<<endl;
            cout<<"You:";
            cin>>s;
            exchange(data,list,n);
            sort(n,s,list,method,cputime,i);
            cout<<endl<<"Complete sorting!"<<endl<<"Do you want to print the sorted data?"<<endl<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
            cout<<"You:";
            cin>>ans;
            if(ans=='y'||ans=='Y')
            {
                cout<<endl<<"The sorted data:"<<endl;
                print(n,list);
                cout<<endl;
            }
            cout<<endl;
            cout<<endl<<"Do you want to check if the data is correctly sorted?"<<endl<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
            cout<<"You:";
            cin>>ans;
            if(ans=='y'||ans=='Y')
            {
                cout<<endl;
                self_check(list,n);
            }
            cout<<endl;
            cout<<"Do you want to print the CPU time?"<<endl<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
            cout<<"You:";
            cin>>ans;
            cout<<endl;
            if(ans=='y'||ans=='Y')
            {
                cout<<"CPU time (sec.) = "<<cputime[i]<<" s"<<endl;
            }
            i++;
            if(i==4) break;
            cout<<endl<<"Do you want to sort the same random data with differnt sort algoritm?"<<endl<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
            cout<<"You:";
            cin>>ans;
            cout<<endl;
            if(i>=4) break;
        }while(ans=='y'||ans=='Y');
        cout<<endl<<"Do you want to compare the CPU time of all the sort algorithm that you've chosen?"<<endl;
        cout<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
        cout<<"You:";
        cin>>ans;
        if(ans=='y'||ans=='Y')
        {
            cout<<endl<<"From fast to slow:"<<endl;
            cout<<"Sort Algorithm: "<<endl;
            time_comepare (method,cputime,i);
        }
        cout<<endl;
        cout<<endl<<"Do you want to search a number in sorted data with Binary Search?"<<endl;
        cout<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
        cout<<"You:";
        cin>>ans;
        do{
            if(ans=='y'||ans=='Y')
            {
                cout<<endl<<"Please enter the number you would like to search for:"<<endl;
                cout<<"You:";
                cin>>num;
                success=-1;//不成功是-1
                success=binary_search(list,num,0,n-1);
                if(success>=0 && success<n)//成功
                    cout<<endl<<"The number has been found in list["<<success<<"]"<<endl;
                else
                    cout<<endl<<"The number has not been found"<<endl;
            }
            cout<<endl;
            cout<<"Do you want to search another number in sorted data with Binary Search?"<<endl;
            cout<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
            cout<<"You:";
            cin>>ans;
            cout<<endl;
        }while(ans=='y'||ans=='Y');
        cout<<endl<<"Do you want to sort another random data?"<<endl;
        cout<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
        cout<<"You:";
        cin>>ans;
        cout<<endl;
    }while(ans=='y'||ans=='Y');
    return 0;
}

void input(int n,int r,int data[])
{
    int i;
    for(i=0;i<n;i++)//產生n個變數 放到陣列
    {
        data[i]= rand()%r;//產生0~r-1的範圍的亂數
    }
}

void print(int n,int list[])
{
    int i;
    for(i=0;i<n;i++)
    {
        cout<<list[i]<<" ";
    }
}

void selection_sort (int n,int list[])
{
    int i,j,min,temp;
    for(i=0;i<n;i++)//回合數
    {
        min=i;
        for(j=i+1;j<n;j++)
        {
            if(list[j]<list[min])//設第一個最小 其他要去比是不是最小
                min=j;//min標記最小的數
        }
        SWAP(list[i],list[min],temp);//更小交換 min和每回合起點做交換
    }//做完每一輪可以確定該輪為排序之最小 由小排到大
}

void bubble_sort (int n,int list[])
{
    int i,j,temp;
    for(i=n-1;i>0;i--)//回合數
    {
        for(j=1;j<=i;j++)//最大的往下沉
        {
            if(list[j-1]>list[j])
                SWAP(list[j-1],list[j],temp);//叫大就和下一數交換
        }
    }//做完每一輪可以排出還未排序的數中最大的
}

void quick_sort (int list[],int left,int right)
{
    int i,j,target,temp;
    if (left<right)//boundary condition 遞迴停止條件
    {
        i=left+1;
        j=right;
        target=list[left];
        do
        {
            while(list[i]<target && i<=j) i++;//從左往右掃描 比目標小就left往下一個 遇到較大的應該要在右半邊的位置就停
            while (list[j]>=target && i<=j) j--;//遇到較小的就停
            if (i<j) SWAP(list[i], list[j], temp);//左右都停就交換
        }while (i<j);
        if (left<j) SWAP(list[left],list[j], temp);//放到中間正確的位置
        quick_sort(list, left, j-1);
        quick_sort(list, j+1, right);
    }
}

void insertion_sort (int n,int list[])
{
    int i,j,target;
    for (i=1;i<n;i++)
    {
        target=list[i];//要比較的對象
        j=i;
        while((list[j-1]>target) && (j>0))//和已經排好的數列的最一個數往上比 比到比已排好的數小就插入 將比其大的往後挪開
        {
            list[j]=list[j-1];//list[j-1]較大就移位置
            j--;
        }
        list[j]=target ;
    }
}

int binary_search (int list[],int searchnum,int left,int right)
{
    int middle;
    while (left<=right)
    {
        middle=(left+right)/2;
        switch (COMPARE(list[middle],searchnum))
        {
            case -1:
                left =middle +1;//中間的數比目標小 左半邊不用找
                break;
            case 0 :
                return middle;
                break;
            case 1 :
                right =middle-1;
                break;
        }
    }
    return -1;
}

void exchange (int data[], int list[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        list[i]=data[i];
    }
}

void sort(int n,int s,int list[],int method[],double cputime[],int i)
{
    switch(s)
    {
        case 1:
            clock_t t_begin,t_end;//t_begin,t_end變數名 clock_t為變數型態
            t_begin=clock();//clock()在time.h的函數
            selection_sort (n,list);
            t_end=clock();
            cputime[i]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
            method[i]=1;
            break;
        case 2:
            t_begin=clock();
            bubble_sort (n,list);
            t_end=clock();
            cputime[i]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            method[i]=2;
            break;
        case 3:
            t_begin=clock();
            quick_sort (list,0,n-1);
            t_end=clock();
            cputime[i]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            method[i]=3;
            break;
        case 4:
            t_begin=clock();
            insertion_sort (n,list);
            t_end=clock();
            cputime[i]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            method[i]=4;
            break;
            
    }
}

void time_comepare (int method[],double cputime[],int i)
{
    int j,t,min,temp;
    double tmp;
    for(j=0;j<i;j++)
    {
        min=j;
        for(t=j+1;t<i;t++)//用selection sort的邏輯排執行時間長短
        {
            if(cputime[t]<cputime[min])
                min=t;
        }
        SWAP(cputime[j],cputime[min],tmp);
        SWAP(method[j],method[min],temp);
        switch(method[j])//代號轉換成英文
        {
            case 1:
                cout<<"Selection sort";
                break;
            case 2:
                cout<<"Bubble sort";
                break;
            case 3:
                cout<<"Quick sort";
                break;
            case 4:
                cout<<"Insertion sort";
                break;
        }
        cout<<"("<<cputime[j]<<"s)";
        if(j<i-1)
            cout<<"<";
        
    }//由小排到大
}

void self_check (int list[],int n)
{
    int i;
    for(i=0;i<n-1;i++)
    {
        if(list[i]>list[i+1])//排序好 注標小的應該會比注標大的內的資料小或等於
        {
            break;
        }
    }
    if(i==n-1)
        cout<<"Correctly Sorted!"<<endl;
    else
        cout<<"Not Correctly Sorted!"<<endl;
}
