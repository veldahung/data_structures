#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main()
{
    int x,n,i,j,k,t,a[1000000],y=1,res=0,funp,funpo;
    long long int anspo,ans=1;
    double cputime[5];
    char you;
    clock_t t_begin,t_end;//t_begin,t_end變數名 clock_t為變數型態
    do
    {
        cout<<"Choose the mode."<<endl<<"Compute x^n , enter 1."<<endl<<"Compute f(x) for x=1, 2, ... , n where f(x)=a0+a1x^1+a2x^2+ ... ak-1x^(k-1) , enter 2."<<endl<<"You:";
        cin>>res;
        switch(res)
        {
            case 1:
                cout<<"Please enter x and n for x^n"<<endl;
                cout<<"x=";
                cin>>x;
                cout<<"n=";
                cin>>n;
                do
                {
                    cout<<"Please choose the method you want to use to compute the answer. Enter the number"<<endl<<"1. For-loop."<<endl<<"2. pow(k,n)"<<endl<<"You:";
                    cin>>funp;
                    switch(funp)
                    {
                        case 1:
                            t_begin=clock();//clock()在time.h的函數
                            for(t=0;t<1000000000;t++)
                            {
                                ans=1;
                                for(i=0;i<n;i++)
                                {
                                    ans*=x;
                                }
                            }
                            t_end=clock();
                            cputime[1]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                            cout<<"For-loop: "<<x<<"^"<<n<<"="<<ans<<". Time:"<<cputime[1]<<"s(1000000000times)"<<endl;
                            break;
                        case 2:
                            t_begin=clock();
                            for(t=0;t<1000000000;t++)
                            {
                                ans=pow(x,n);
                            }
                            t_end=clock();
                            cputime[2]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;//把t_end-t_begin做浮點數在除
                            cout<<"Pow(x,n): "<<x<<"^"<<n<<"="<<ans<<". Time:"<<cputime[2]<<"s(1000000000times)"<<endl;
                            break;
                    }
                    cout<<"Want to try another method? If yes, enter y. Else, enter n"<<endl<<"You:";
                    cin>>you;
                }while(you=='y'||you=='Y');
                break;
            
            case 2:
                cout<<"Please enter k and n for f(x) = a[0] + a[1]x + a[2]x^2 + … + a[k-1]x^(k-1) (a[0]~a[k-1] are randomly genarated) and caculate f(1),f(2),...,f(n)"<<endl;
                cout<<"k=";
                cin>>k;
                cout<<"n=";
                cin>>n;
                srand(time(NULL));
                for(i=0;i<k;i++)
                {
                    a[i]=rand()%30;
                    cout<<"a["<<i<<"]="<<a[i]<<endl;
                }
                do
                {
                    cout<<"Please choose the method you want to use to compute the answer. Enter the number"<<endl<<"1. For-loop."<<endl<<"2. Horner's method"<<endl<<"You:";
                    cin>>funpo;
                    switch(funpo)
                    {
                        case 1:
                            cout<<"For-loop:"<<endl;
                            t_begin=clock();
                            for(i=1;i<=n;i++)
                            {
                                anspo=a[0];
                                y=1;
                                for(j=1;j<k;j++)
                                {
                                    y*=i;
                                    anspo+=a[j]*y;
                                }
                                cout<<"f("<<i<<")="<<anspo<<endl;
                            }
                            t_end=clock();
                            cputime[3]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                            cout<<"For-loop: Time:"<<cputime[3]<<"s"<<endl;
                            break;
                        case 2:
                            cout<<"Horner's Method:"<<endl;
                            t_begin=clock();
                            for(i=1;i<=n;i++)
                            {
                                anspo=a[k];
                                y=1;
                                for(j=k-1;j>=0;j--)
                                {
                                    anspo=anspo*i+a[j];
                                }
                                cout<<"f("<<i<<")="<<anspo<<endl;
                            }
                            t_end=clock();
                            cputime[4]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                            cout<<"Horner's Method: Time:"<<cputime[4]<<"s"<<endl;
                            break;
                    }
                    cout<<"Want to try another method? If yes, enter y. Else, enter n"<<endl<<"You:";
                    cin>>you;
                }while(you=='y'||you=='Y');
                break;
        }
        cout<<"Want to try another mode? If yes, enter y. Else, enter n"<<endl<<"You:";
        cin>>you;
    }while(you=='y'||you=='Y');

    return 0;
}

