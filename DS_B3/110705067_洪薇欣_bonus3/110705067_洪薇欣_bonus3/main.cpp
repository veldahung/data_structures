#include <iostream>
#include <string>

using namespace std;
int top_opn,top_opr;
string stack_opn[200],stack_opr[200];

void push(int flag, string data);
string pop(int flag);
int opn(string data);//判斷是operand or operator
int opr_before(string x);
int opr_after(string x);
string getfix(string x,int flag);
string infix2postfix(string e);
string infix2prefix(string e);
string postfix2prefix(string e);
string prefix2postfix(string e);
string postfix2infix(string e);
string prefix2infix(string e);


int main()
{
    char e[100];
    int mode;
    char ans;
    do
    {
        cout<<"Please choose a mode. Please enter the number."<<endl<<"1.infix2postfix"<<endl<<"2.infix2prefix"<<endl<<"3.postfix2prefix"<<endl<<"4.prefix2postfix"<<endl<<"5.postfix2infix"<<endl<<"6.prefix2infix"<<endl<<"You:";
        cin>>mode;
        cout<<"Please enter the string you wnat to transfer:";
        cin>>e;
        switch(mode)
        {
            case 1:
                cout<<infix2postfix(e)<<endl;
                break;
            case 2:
                cout<<infix2prefix(e)<<endl;
                break;
            case 3:
                cout<<postfix2prefix(e)<<endl;
                break;
            case 4:
                cout<<prefix2postfix(e)<<endl;
                break;
            case 5:
                cout<<postfix2infix(e)<<endl;
                break;
            case 6:
                cout<<prefix2infix(e)<<endl;
                break;
        }
        cout<<"Try another mode? If yes, enter y. Else, enter n."<<endl<<"You:";
        cin>>ans;
    }while(ans=='y'||ans=='Y');
    return 0;
}

void push(int flag, string data)
{
    switch(flag)
    {
        case 1:
            if(top_opr==199)
                cout<<"Stack is full"<<endl;
            else
                stack_opr[++top_opr]=data;
            break;
        case 2:
            if(top_opn == 199)
                cout<<"Stack is full"<<endl;
            else
                stack_opn[++top_opn]=data;
            break;
    }
}

string pop(int flag)
{
    switch(flag)
    {
        case 1:
            if(top_opr==-1)
            {
                cout<<"Stack is empty"<<endl;
                return 0;
            }
            else
                return stack_opr[top_opr--];
            break;
        case 2:
            if(top_opn==-1)
            {
                cout<<"Stack is empty"<<endl;
                return 0;
            }
            else
                return stack_opn[top_opn--];
            break;
    }
    return 0;
}

int opn(string s)
{  if ((s!="+") && (s!="-") && (s!="*") && (s!="/")&& (s!="<") && (s!=">")  && (s!="&") && (s!="|") && (s!="^") && (s!="#"))
    return 0;
   return 1;
}

int opr_before(string s)
{
    int p;
    if(s=="#")
         p=-1;
    else if(s=="<")
        p=9;
    else if(s=="@")
        p=10;
    else if(s=="|")
        p=1;
    else if(s=="&")
        p=2;
    else if((s=="*") || (s=="/") || (s=="%"))
        p=7;
    else if((s=="+") || (s=="-"))
        p=6;
    else if(s=="^")
        p=8;
    else
        p=-2;
    return p;
}

int opr_after(string s)
{
    int q;
    if(s=="#")
        q=-1;
    else if(s=="<")
        q=0;
    else if((s=="+") || (s=="-"))
        q=6;
    else if((s=="*") || (s=="/") || (s=="%"))
        q=7;
    else if(s=="|")
        q=1;
    else if(s=="&")
        q=2;
    else if(s=="^")
        q=8;
    else
        q=-2;
    return q;
}
string getfix(string x,int flag)
{
    string a = pop(2);
    string b = pop(2);
    a=(flag==1) ? b+a+x : x+b+a;
    return a;
    
}

string infix2postfix(string e)
{
    long n = e.length();//把字串分割，字串總長度為n
    string postfix;
    string s,x;
    push(2,"#");  //讓operator皆可進
    for(int i=0;i<n;i++)
    {
        s=e[i];
        if (opn(s)==0)
           postfix += s;
        else if (s == ">" ) //遇到“)”，將“(”前的東西全部輸出
        {
            while( (x=pop(2)) != "<" )
                postfix += x;
        }
        else
        {
           while( opr_before(s) <= opr_after(stack_opn[top_opn]))//比operator的優先順序大小
            {
                x = pop(2);   //堆疊內元素比外的元素>=皆要pop出
                postfix += x;
            }
            push(2,s);
        }
    }
    while (stack_opn[top_opn] != "#")  //stack內還有東西就將所有東西pop出來
    {
        x = pop(2);
        postfix += x;
    }
    x = pop(2);
    return postfix;
}

string infix2prefix(string e)
{
    long n = e.length();
    string s,x,prefix;
    push(1,"#");  //讓operator皆可進
    for(int i=0;i<n;i++)
    {
        s=e[i];
        if (opn(s)==0)
           push(2,s);
        else if (s == ">" ) //遇到“)”，將“(”前的東西全部輸出
        {
            while( (x=pop(1)) != "<" )
                push(2,getfix(x,0));
        }
        else
        {
           while( opr_before(s) <= opr_after(stack_opr[top_opr]))//比operator的優先順序大小
            {
                x = pop(1);   //堆疊內元素比外的元素>=皆要pop出
                push(2,getfix(x,0));
            }
            push(1,s);
        }
    }
    while ((x=pop(1)) != "#") //stack內還有東西就將所有東西pop出來
    {
        push(2,getfix(x,0));
    }
    prefix=pop(2);
    pop(1);
    return prefix;
}

string postfix2prefix(string e)
{
     long n = e.length();
     string s,prefix;
     for (int i=0; i<n; i++)
     {
             s = e[i];
             if ( opn(s)==0)
                 push(2,s);  //push至operand的stack
             else
                 push( 2,getfix (s,0) );
            
     }
     prefix=pop(2);  //從operand的stack pop出
    return prefix;
}

string prefix2postfix(string e)
{
    
    long n = e.length();
    string s,x,y,postfix;
    push(2,"#");
     for (int i=0; i<n; i++)
     {
             s = e[i];
             if ( opn(s)==0)
             {
                 while(opn(stack_opn[top_opn])==0)
                 {
                     y = pop(2);  //pop出前一個operand
                     x = pop(2);  //pop出前一個operator
                     s = y+s+x;
                 }  //如果結合完後Stack[top]仍是operand，還要再結合
                 push(2,s);  //將已結合的operand丟回Stack
             }
             else
                 push(2,s);  //將operator push進stack
     }
    postfix=pop(2);
    pop(2);
    return postfix;
}

string postfix2infix(string e)
{
     int i;
     string s1,s2,s,x,y,infix;
     long n = e.length();
     for (i=0; i<n; i++)
     {
             s = e[i];
             if ( opn(s)==0)
             {
                 push(2, s);
                 push(1, "@");  //每個未結合的operand 給一對應operator @
                                // ( @有最大的優先順序，不用加括號的)
             }
             else
             {
                 s1 = pop(1);//從stack 1 (放operand的stack)將第一個operand pop出
                 s2 = pop(1);//從stack 1 (放operand的stack)將第二個operand pop出
                 //（運算需要兩個operand）
                 x = pop(2);//從stack 2 (放對應的operator的stack)將s1的operator pop出
                 y = pop(2);//從stack 2 (放對應的operator的stack)將s2的operator pop出
                 if ( opr_before(s) > opr_before(s1) )
                     x = "(" + x + ")" ;//如果要結合的operator 比已結合的operator優先順序大，已結合的operand要加()。Ex. operand:A+B, operator: *. * > + , A+B要加括號，變(A+B)
                 if ( opr_before(s) > opr_before(s2) )
                     y = "(" + y+ ")" ;
                 push (2, y+s+x );  //結合後再放入operand的stack
                 push (1, s);//將結合後的operand所對應的operator放入operator的stack
             }
     }
     while ( top_opr != -1)
     x = pop(1);  //將operator的stack清空
     return pop(2);
}

string prefix2infix(string e)
{
     int i;
     string s1,s2,s,x,y;
     long n = e.length();
     for (i=(int)n-1; i>=0; i--)
     {
             s = e[i];
             if ( opn(s)==0)
             {
                 push(2, s);
                 push(1, "@");  //每個未結合的operand 給一對應operator @
                                // ( @有最大的優先順序，不用加括號的)
             }
             else
             {
                 s1 = pop(1);//從stack 1 (放operand的stack)將第一個operand pop出
                 s2 = pop(1);//從stack 1 (放operand的stack)將第二個operand pop出
                 //（運算需要兩個operand）
                 x = pop(2);//從stack 2 (放對應的operator的stack)將s1的operator pop出
                 y = pop(2);//從stack 2 (放對應的operator的stack)將s2的operator pop出
                 if ( opr_before(s) > opr_before(s1) )
                     x = "(" + x + ")" ;//如果要結合的operator 比已結合的operator優先順序大，已結合的operand要加()。Ex. operand:A+B, operator: *. * > + , A+B要加括號，變(A+B)
                 if ( opr_before(s) > opr_before(s2) )
                     y = "(" + y+ ")" ;
                 push (2, x+s+y );  //結合後再放入operand的stack
                 push (1, s);//將結合後的operand所對應的operator放入operator的stack
             }
     }
     while ( top_opr != -1)
     x = pop(1);  //將operator的stack清空
     return pop(2);
}
