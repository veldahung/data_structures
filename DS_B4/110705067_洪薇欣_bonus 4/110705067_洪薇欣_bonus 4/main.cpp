#include <iostream>
using namespace std;

struct term
{
    int coef;
    int expo;
    struct term *next;
};

struct term *a_first,*b_first,*c_first,*a_last,*b_last,*c_last;

struct term *insertterm(int coef,int expo,struct term *poly);
struct term *newheader(int coef,int expo);
struct term *newterm(struct term *s);
struct term *addpoly(struct term *a_first, struct term *b_first);
void print_poly(struct term *head);

int main()
{
    int coef,expo,prexpo=99;
    a_last=a_first=newheader(0,-1);
    b_last=b_first=newheader(0,-1);
    cout<<"Please enter the polynomial A:"<<endl;
    do
    {
        cout<<"Please enter the exponent (If you wnat to stop entering the polynomial just enter -2):"<<endl;
        cin>>expo;
        while(expo>=prexpo)
        {
            cout<<"Please enter the polynomial decreasingly, pleasee try another exponoent!"<<endl;
            cin>>expo;
        }
        if(expo<0)
            break;
        prexpo=expo;
        cout<<"Please enter the coefficient:"<<endl;
        cin>>coef;
        if(coef!=0)
            a_last=insertterm(coef,expo,a_last);
    }while(expo>0);
    cout<<"A: ";
    print_poly(a_first);
    cout<<"Please enter the polynomial B:"<<endl;
    prexpo=99;
    do
    {
        cout<<"Please enter the exponent (If you wnat to stop entering the polynomial just enter -2):"<<endl;
        cin>>expo;
        while(expo>=prexpo)
        {
            cout<<"Please enter the polynomial decreasingly, pleasee try another exponoent!"<<endl;
            cin>>expo;
        }
        if(expo<0)
            break;
        prexpo=expo;
        cout<<"Please enter the coefficient:"<<endl;
        cin>>coef;
        if(coef!=0)
            b_last=insertterm(coef,expo,b_last);
    }while(expo>0);
    cout<<"B: ";
    print_poly(b_first);
    c_first=addpoly(a_first,b_first);
    cout<<"A: ";
    print_poly(a_first);
    cout<<"B: ";
    print_poly(b_first);
    cout<<"C: ";
    print_poly(c_first);
    return 0;
}

struct term *newheader(int coef,int expo)
{
    struct term *r = new struct term;
    r->coef = coef;
    r->expo = expo;
    r->next = r;
    return r;
}

struct term *newterm(struct term *s)
{
    struct term *r = new struct term;
    *r = *s;
    return r;
}

struct term *insertterm(int coef,int expo,struct term *poly)
{
    int c,e;
    c=coef;
    e=expo;
    struct term *p = newheader(c,e);
    p->next = poly->next;
    poly->next = p;
    return p;

}

struct term *addpoly(struct term *a_first, struct term *b_first)
{
    struct term *p,*q,*r,*t;
    int flag=0;
    c_last=c_first=newheader(0,-1);
    p=a_first->next;
    q=b_first->next;
    while(p!=a_first||q!=b_first)
    {
        if(p->expo>q->expo)
        {
            r=newterm(p);
            p=p->next;
        }
        else if(p->expo<q->expo)
        {
            r=newterm(q);
            q=q->next;
        }
        else
        {
                r=newterm(p);
                r->coef+=q->coef;
                p=p->next;
                q=q->next;
        }
        if(r->coef!=0)
        {
            c_last->next=r;
            t=c_last->next;
            c_last=t;
        }
        flag=0;
    }
    c_last->next = c_first;
    return c_first;
}

void print_poly(struct term *head)
{
    struct term *p = head->next;
    if(p->expo!=0&&p->coef==1)
    {
        cout<<"x^"<<p->expo;
    }
    else if(p->expo!=0&&p->coef<0)
    {
        cout<<"("<<p->coef<<")x^"<<p->expo;
    }
    else if(p->expo!=0&&p->coef>0)
    {
        cout<<p->coef<<"x^"<<p->expo;
    }
    else if(p->expo==0&&p->coef<0)
    {
        cout<<"+("<<p->coef<<")";
    }
    else
        cout<<p->coef;
    for(p=p->next;p!=head;p=p->next)
    {
        if(p->expo!=0&&p->coef==1)
        {
            cout<<"+x^"<<p->expo;
        }
        else if(p->expo!=0&&p->coef<0)
        {
            cout<<"+("<<p->coef<<")x^"<<p->expo;
        }
        else if(p->expo!=0&&p->coef>0)
        {
            cout<<"+"<<p->coef<<"x^"<<p->expo;
        }
        else if(p->expo==0&&p->coef<0)
        {
            cout<<"+("<<p->coef<<")";
        }
        else
            cout<<"+"<<p->coef;
    }
    cout<<endl;
}
