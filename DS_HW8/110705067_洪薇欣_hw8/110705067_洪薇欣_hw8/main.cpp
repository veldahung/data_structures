#include <iostream>
#include <stdio.h>
#include <stdlib.h> //亂數相關函數
#include <time.h>//計算cpu時間用 產生亂數用
#include <stdlib.h>//計算cpu時間用
#include <math.h>
#define SWAP(x,y,t) (t=x,x=y,y=t)//macro 交換數值用的
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1)
using namespace std;

int top;
int Stack[1000000],heap[1000003],t[100000];
void input (int n,int r,int data[]);//輸入亂數資料
void print (int n,int list[]);//輸出資料
void push(int data);//push進堆疊
int pop();//pop出堆疊
void sort(int n,int s,int list[],int method[],double cputime[][30],int i,int times,int t);//決定用何種排序方式 並進行排序
void selection_sort (int n,int list[]);
void bubble_sort (int n,int list[]);
void insertion_sort (int n,int list[]);
void quick_sort_r (int list[],int left,int right);
void quick_sort_nr (int list[],int left,int right);
void merge(int c[], int k, int a[], int i, int m, int b[], int j, int n);
void merge_sort_r(int a[],int left, int right);
void merge_sort_nr(int a[],int left, int right,int n);
void restore(int s, int t,int heap[]);
void heapsort(int n,int list[]);
void radixsort(int n,int list[]);
void exchange (int data[], int list[],int n);//用於儲存data內的數字到list 避免資料覆蓋 這樣每種不同排序方法都要用時 排序皆是用未排序的資料進行排序
void time_comepare (int method[],double cputime[][30],int i,int t);//比較通一筆為排列資料 不同排序方法 cpu的執行時間
void self_check (int list[],int n);//自行檢查排序是否正確

int main()
{
    int n,r,data[1000000]={0},list[1000000]={0},s,method[30]={0},i,times,t=0;
    double cputime[30][30]={0.0};
    char ans;
    do{
        do{
            cout<<"Please input the amount (0<n<100000) of random number you want to sort:"<<endl;
            cout<<"You:";
            cin>>n;//要產生的亂數個數
            if(0>=n||n>1000000)
                cout<<endl<<"Please try anothe number!"<<endl<<endl;
        }while(0>=n||n>1000000);
        cout<<endl;
        do{
            cout<<"Please input the range (0<r<100000) of random number you want to sort:"<<endl;
            cout<<"You:";
            cin>>r;//亂數產生範圍
            if(0>=r||r>1000000)
                cout<<endl<<"Please try anothe number!"<<endl<<endl;
        }while(0>=r||r>1000000);
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
        cout<<"Please enter the times each sorting algorithm should run:";
        cin>>times;
        cout<<endl;
        i=0;//i紀錄共選擇了幾種排序方式
        do{

            cout<<"Please choose a sort algorithm (enter the number):"<<endl;
            cout<<"1. Selection Sort"<<endl<<"2. Bubble Sort"<<endl<<"3. Insertion Sort"<<endl<<"4. Quick Sort - Recursive"<<endl<<"5. Quick Sort - Nonrecursive"<<endl<<"6. Merge Sort - Recursive"<<endl<<"7. Merge Sort - Nonrecursive"<<endl<<"8. Heap Sort"<<endl<<"9. Radix Sort"<<endl;
            cout<<"You:";
            cin>>s;
            exchange(data,list,n);
            sort(n,s,list,method,cputime,i,times,t);
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
                cout<<"CPU time (sec.) = "<<cputime[i][t]<<" s"<<endl;
            }
            i++;
            if(i==9) break;
            cout<<endl<<"Do you want to sort the same random data with differnt sort algoritm?"<<endl<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
            cout<<"You:";
            cin>>ans;
            cout<<endl;
            if(i>=9) break;
        }while(ans=='y'||ans=='Y');
        cout<<endl<<"Do you want to compare the CPU time of all the sort algorithm that you've chosen?"<<endl;
        cout<<"If yes,please enter 'y'. If no,please enter 'n'."<<endl;
        cout<<"You:";
        cin>>ans;
        if(ans=='y'||ans=='Y')
        {
            cout<<" n = "<<n;
            cout<<endl<<"From fast to slow:"<<endl;
            time_comepare (method,cputime,i,t);
        }
        t++;
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

void push(int data)
{
    if (top==99999)//滿了
        cout<<"The stack is full"<<endl;
    else
        Stack[++top]=data;//先++再將資料放入
}

int pop()
{
    if(top==-1)//防呆
    {
        cout<<"The stack is empty"<<endl;
        return Stack[0];
    }
    else
        return Stack[top--];//資料先回傳才--
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

void quick_sort_r(int list[],int left,int right)
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
        quick_sort_r(list, left, j-1);
        quick_sort_r(list, j+1, right);
    }
}

void quick_sort_nr (int list[],int left,int right)
{
    int i,j,target,tmp;
    top=-1;//初始化stack;
    push(left);
    push(right);
    while(top!=-1)
    {
        right=pop();
        left=pop();
        target=list[left];
        i=left+1;
        j=right;
        do
        {
            while(list[i]<target && i<=j) i++;
            while (list[j]>=target && i<=j) j--;
            if (i<j) SWAP(list[i], list[j], tmp);
        }while(i<j);
        if(left<j) SWAP(list[left],list[j], tmp);
        if(j+1<right)
        {
            push(j+1);
            push(right);
        }
        if(left<j-1)
        {
            push(left);
            push(j-1);
        }
    }
}

void merge(int c[], int k, int a[], int i, int m, int b[], int j, int n)
{
    int p;
    for(p=i;p<=m;p++)
        t[p]=a[p];
    for(p=j;p<=n;p++)
        t[p]=b[p];
    while((i<=m)&&(j<=n))
    {
        if(t[i]<=t[j])
            c[k++]=t[i++];
        else
            c[k++]=t[j++];
    }
    while(i<=m) c[k++]=t[i++];
    while(j<=n) c[k++]=t[j++];
}

void merge_sort_r(int a[],int left, int right)
{
    int m;
    if(left<right)
    {
        m=(left+right)/2;
        merge_sort_r(a,left,m);
        merge_sort_r(a,m+1,right);
        merge(a,left,a,left,m,a,m+1,right);
    }
}

void merge_sort_nr(int a[],int left, int right,int n)
{
    int len=1,i;
    while(len<n)
    {
        for(i=0;i<n-len;i+=len*2)
        {
            merge(a,i,a,i,i+len-1,a,i+len,min(i+2*len-1,n-1));
        }
        len*=2;
    }
}

void exchange (int data[], int list[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        list[i]=data[i];
    }
}

void restore(int s, int t,int heap[])
{
    int tmp;
    int i=s,j;
    while(i<=t/2)
    {
        if(heap[2*i]>heap[2*i+1])
            j=2*i;
        else
            j=2*i+1;
        if(heap[i]>heap[j])
            break;
        SWAP(heap[i],heap[j],tmp);
        i=j;
    }
}

void heapsort(int n,int list[])
{
    int i;
    for(i=0;i<n;i++)
    {
        heap[i+1]=list[i];
    }
    for(i=n/2;i>=1;i--)
        restore(i,n,heap);
    for(i=n;i>=1;i--)
    {
        list[i-1]=heap[1];
        heap[1]=heap[i];
        restore(1,i-1,heap);
        
    }
}

void radixsort(int n,int list[])
{
    int max=0,i,j,radix,count[10000],temp[10000],index[10000],digit;
    double k;
    for(i=0;i<n;i++)
    {
        if(list[i]>max)
            max=list[i];
    }
    radix=log10(max+1);
    for(i=1;i<=radix;i++)
    {
        for(j=0;j<10;j++)
        {
            count[j]=0;
            index[j]=0;
        }
        k=(double)i-1;
       for(j=0;j<10;j++)
        {
            digit=((list[j]/((int)pow(10.0,i-1)))%10);
            count[digit]++;
        }
        index[0]=0;
        for(j=1;j<10;j++) index[j]=index[j-1]+count[j-1];
        for(j=0;j<n;j++)
        {
            digit=((list[j]/((int)pow(10.0,i-1)))%10);
            temp[index[digit]++]=list[j];
        }
        for(j=0;j<n;j++) list[j]=temp[j];
    }
}

void sort(int n,int s,int list[],int method[],double cputime[][30],int i,int times,int t)
{
    int j,k;
    double min=100.0,max=0.0,cpu=0.0,tmp;
    switch(s)
    {
        case 1:
            clock_t t_begin,t_end;//t_begin,t_end變數名 clock_t為變數型態
            for(k=1;k<=12;k++)
            {
                t_begin=clock();//clock()在time.h的函數
                for(j=0;j<times;j++)
                {
                    selection_sort (n,list);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=1;
            break;
        case 2:
            for(k=1;k<=12;k++)
            {
                t_begin=clock();
                for(j=0;j<times;j++)
                {
                    bubble_sort (n,list);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=2;
            break;
        case 3:
            for(k=1;k<=12;k++)
            {
                t_begin=clock();//clock()在time.h的函數
                for(j=0;j<times;j++)
                {
                    insertion_sort (n,list);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=3;
            break;
        case 4:
            for(k=1;k<=12;k++)
            {
                t_begin=clock();//clock()在time.h的函數
                for(j=0;j<times;j++)
                {
                    quick_sort_r (list,0,n-1);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=4;
            break;
        case 5:
            for(k=1;k<=12;k++)
            {
                t_begin=clock();//clock()在time.h的函數
                for(j=0;j<times;j++)
                {
                    quick_sort_nr (list,0,n-1);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=5;
            break;
        case 6:
            for(k=1;k<=12;k++)
            {
                t_begin=clock();//clock()在time.h的函數
                for(j=0;j<times;j++)
                {
                   merge_sort_r (list,0,n-1);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=6;
            break;
        case 7:
            for(k=1;k<=12;k++)
            {
                t_begin=clock();//clock()在time.h的函數
                for(j=0;j<times;j++)
                {
                    merge_sort_nr (list,0,n-1,n);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=7;
            break;
        case 8:
            for(k=1;k<=12;k++)
            {
                t_begin=clock();//clock()在time.h的函數
                for(j=0;j<times;j++)
                {
                    heapsort(n,list);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=8;
            break;
        case 9:
            for(k=1;k<=12;k++)
            {
                t_begin=clock();//clock()在time.h的函數
                for(j=0;j<times;j++)
                {
                    radixsort(n,list);
                }
                t_end=clock();
                tmp=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                if(tmp<min)
                    min=tmp;
                if(tmp>max)
                    max=tmp;
                cpu+=tmp;
            }
            cputime[i][t]=(cpu-min-max)/10.0;
            method[i]=9;
            break;
            
    }
}

void time_comepare (int method[],double cputime[][30],int i,int t)
{
    int j,k,min,temp;
    double tmp;
    for(j=0;j<i;j++)
        {
            min=j;
            for(k=j+1;k<i;k++)//用selection sort的邏輯排執行時間長短
            {
                if(cputime[k][t]<cputime[min][t])
                    min=k;
            }
            SWAP(cputime[j][t],cputime[min][t],tmp);
            SWAP(method[j],method[min],temp);
            switch(method[j])//代號轉換成英文
            {
                case 1:
                    cout<<"Selection sort : ";
                    break;
                case 2:
                    cout<<"Bubble sort : ";
                    break;
                case 3:
                    cout<<"Insertion sort : ";
                    break;
                case 4:
                    cout<<"Quick sort - recursive : ";
                    break;
                case 5:
                    cout<<"Quick sort - nonrecursive : ";
                    break;
                case 6:
                    cout<<"Merge sort - recursive : ";
                    break;
                case 7:
                    cout<<"Merge sort - nonrecursive : ";
                    break;
                case 8:
                    cout<<"Heap sort : ";
                    break;
                case 9:
                    cout<<"Radix sort : ";
                    break;

            }
            cout<<cputime[j][t]<<"s";
            if(j<i-1)
            {
                cout<<" < ";
            }
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
