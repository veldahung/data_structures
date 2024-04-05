#include <iostream>
#include <time.h>
using namespace std;

struct node
{
    int data;
    struct node *next;
};
struct node *first, *last, *top, *front, *rear;
struct Dnode
{
    struct Dnode *prev;
    int datad;
    struct Dnode *nextd;
};
struct Dnode *head;

struct node *newnode(int element);
struct Dnode *newdnode(int element);
void initial();
void initialstack();
void initialqueue();
void initiald();
void insertfirst(int element);
void insertafter(struct node *x, int element);
void insertlast(int element);
int deleteafter(struct node *q);
void clearlist(struct node *first);
struct node *searchdata(int target);
struct node *searchdatabefore(int target);
void printlist(struct node *first);
void invert();
void pushstack(int element);
int popstack();
void printstack(struct node *top);
void clearstack(struct node *top);
void addqueue(int element);
int deletequeue();
void printqueue(struct node *front);
void clearqueue(struct node *front);
void insertfirstdlist(int element);
void insertafterdlist(struct Dnode *x, int element);
void insertlastdlist(int element);
int deletedlist(struct Dnode *x);
void cleardlist(struct Dnode *head);
struct Dnode *searchdlist(int target);
struct Dnode *searchdatadbefore(int target);
void printdlist(struct Dnode *head);
void invertd();

int main()
{
    int element,n,target,item,range,fun,mode,funs,funq,result,fund;
    int *data;
    struct node *x;
    struct Dnode *y;
    char ans;
    do
    {
        cout<<"Choose the mode (Please enter the number) :"<<endl<<"1.Singly Linked List"<<endl<<"2.Linked Stack"<<endl<<"3.Linked Queue"<<endl<<"4.Double Linked List "<<endl<<"You:";
        cin>>mode;
        switch(mode)
        {
            case 1:
                initial();
                cout<<"Choose the function (Please enter the number) :"<<endl<<"1.Insert first"<<endl<<"2.Insert last"<<endl<<"3.Insert after"<<endl<<"4.Insert before"<<endl<<"5.Insert n random numbers"<<endl<<"6.Delete target"<<endl<<"7.Clear list"<<endl<<"8.Search target "<<endl<<"9.Invert list"<<endl<<"You:";
                cin>>fun;
                do
                {
                    switch(fun)
                    {
                        case 1:
                            cout<<"Please enter the element you want to insert:";
                            cin>>element;
                            insertfirst(element);
                            printlist(first);
                            break;
                        case 2:
                            cout<<"Please enter the element you want to insert:";
                            cin>>element;
                            insertlast(element);
                            printlist(first);
                            break;
                        case 3:
                            cout<<"Please enter the target you want to insert an element after it:";
                            cin>>target;
                            cout<<"Please enter the element you want to insert after the target :";
                            cin>>element;
                            x=searchdata(target);
                            if(x)
                            {
                                insertafter(x,element);
                                printlist(first);
                            }
                            else
                                cout<<target<<" has not been found"<<endl;
                            break;
                        case 4:
                            cout<<"Please enter the target you want to insert an element before it:";
                            cin>>target;
                            cout<<"Please enter the element you want to insert before the target :";
                            cin>>element;
                            x=searchdatabefore(target);
                            if(x)
                            {
                                insertafter(x,element);
                                printlist(first);
                            }
                            else
                                cout<<target<<" has not been found"<<endl;
                            break;
                        case 5:
                            cout<<"Please enter n for total random numbers you want to insert:";
                            cin>>n;
                            cout<<"Please enter range for the random numbers you want to generate:";
                            cin>>range;
                            data = new int[n];
                            srand(time(NULL));
                            for(int i=0;i<n;i++)
                            {
                                data[i] = rand() % range +1;
                                insertlast(data[i]);
                            }
                            cout<<"random numbers: ";
                            for(int i=0;i<n;i++)
                            {
                                cout<<data[i]<<" ";
                            }
                            cout<<endl;
                            printlist(first);
                            delete[] data;
                            break;
                        case 6:
                            cout<<"Please enter the target you want to delete:";
                            cin>>target;
                            x=searchdatabefore(target);
                            if(x)
                            {
                                item=deleteafter(x);
                                cout<<item<<" has been deleted"<<endl;
                                printlist(first);
                            }
                            else
                                cout<<target<<" has not been found"<<endl;
                            break;
                        case 7:
                            clearlist(first);
                            printlist(first);
                            break;
                        case 8:
                            cout<<"Please enter the target you want to search:";
                            cin>>target;
                            x=searchdata(target);
                            if(x)
                                cout<<x->data<<" has been found"<<endl;
                            else
                                cout<<target<<" has not been found"<<endl;
                            break;
                        case 9:
                            invert();
                            printlist(first);
                            break;
                    }
                    cout<<"Try another function ? Please enter the number derectly. If you wnat to quit enter 0"<<endl<<"Function:"<<endl<<"1.Insert first"<<endl<<"2.Insert last"<<endl<<"3.Insert after"<<endl<<"4.Insert before"<<endl<<"5.Insert n random numbers"<<endl<<"6.Delete target"<<endl<<"7.Clear list"<<endl<<"8.Search target "<<endl<<"9.Invert list"<<endl<<"You:";
                    cin>>fun;
                }while(fun!=0);
                clearlist(first);
                break;
            case 2:
                initialstack();
                cout<<"Choose the function (Please enter the number) :"<<endl<<"1.Push"<<endl<<"2.Pop"<<endl<<"3.Clear stack"<<endl<<"You:";
                cin>>funs;
                do
                {
                    switch(funs)
                    {
                        case 1:
                            cout<<"Please enter the element you want to push:";
                            cin>>element;
                            pushstack(element);
                            printstack(top);
                            break;
                        case 2:
                            result=popstack();
                            if(result != -1)
                            {
                                cout<<result<<" is pop from the stack"<<endl;
                                printstack(top);
                            }
                            else
                                cout<<"Stack is empty."<<endl;
                            break;
                        case 3:
                            clearstack(top);
                            printstack(top);
                            break;
                    }
                    cout<<"Try another function ? Please enter the number derectly. If you wnat to quit enter 0"<<endl<<"Function:"<<endl<<"1.Push"<<endl<<"2.Pop"<<endl<<"3.Clear stack"<<endl<<"You:";
                    cin>>funs;
                }while(funs!=0);
                clearstack(top);
                break;
            case 3:
                initialqueue();
                cout<<"Choose the function (Please enter the number) :"<<endl<<"1.Add"<<endl<<"2.Delete"<<endl<<"3.Clear queue"<<endl<<"You:";
                cin>>funq;
                do
                {
                    switch(funq)
                    {
                        case 1:
                            cout<<"Please enter the element you want to add:";
                            cin>>element;
                            addqueue(element);
                            printqueue(front);
                            break;
                        case 2:
                            item=deletequeue();
                            if(item != -1)
                            {
                                cout<<item<<" is delete from the queue"<<endl;
                                printqueue(front);
                            }
                            else
                                cout<<"Queue is empty."<<endl;
                            break;
                        case 3:
                            clearqueue(front);
                            printqueue(front);
                            break;
                    }
                    cout<<"Try another function ? Please enter the number derectly. If you wnat to quit enter 0"<<endl<<"Function:"<<endl<<"1.Add"<<endl<<"2.Delete"<<endl<<"3.Clear queue"<<endl<<"You:";
                    cin>>funq;
                }while(funq!=0);
                clearqueue(front);
                break;
            case 4:
                initiald();
                cout<<"Choose the function (Please enter the number) :"<<endl<<"1.Insert first"<<endl<<"2.Insert last"<<endl<<"3.Insert after"<<endl<<"4.Insert before"<<endl<<"5.Insert n random numbers"<<endl<<"6.Delete target"<<endl<<"7.Clear list"<<endl<<"8.Search target "<<endl<<"9.Invert list"<<endl<<"You:";
                cin>>fund;
                do
                {
                    switch(fund)
                    {
                       case 1:
                            cout<<"Please enter the element you want to insert:";
                            cin>>element;
                            insertfirstdlist(element);
                            printdlist(head);
                            break;
                        case 2:
                            cout<<"Please enter the element you want to insert:";
                            cin>>element;
                            insertlastdlist(element);
                            printdlist(head);
                            break;
                        case 3:
                            cout<<"Please enter the target you want to insert an element after it:";
                            cin>>target;
                            cout<<"Please enter the element you want to insert after the target :";
                            cin>>element;
                            y=searchdlist(target);
                            if(y)
                            {
                                insertafterdlist(y,element);
                                printdlist(head);
                            }
                            else
                                cout<<target<<" has not been found"<<endl;
                            break;
                        case 4:
                            cout<<"Please enter the target you want to insert an element before it:";
                            cin>>target;
                            cout<<"Please enter the element you want to insert before the target :";
                            cin>>element;
                            y=searchdatadbefore(target);
                            if(y)
                            {
                                insertafterdlist(y,element);
                                printdlist(head);
                            }
                            else
                                cout<<target<<" has not been found"<<endl;
                            break;
                        case 5:
                            cout<<"Please enter n for total random numbers you want to insert:";
                            cin>>n;
                            cout<<"Please enter range for the random numbers you want to generate:";
                            cin>>range;
                            data = new int[n];
                            srand(time(NULL));
                            for(int i=0;i<n;i++)
                            {
                                data[i] = rand() % range +1;
                                insertlastdlist(data[i]);
                            }
                            cout<<"random numbers: ";
                            for(int i=0;i<n;i++)
                            {
                                cout<<data[i]<<" ";
                            }
                            cout<<endl;
                            printdlist(head);
                            delete[] data;
                            break;
                        case 6:
                            cout<<"Please enter the target you want to delete:";
                            cin>>target;
                            y=searchdlist(target);
                            if(y)
                            {
                                item=deletedlist(y);
                                cout<<item<<" has been deleted"<<endl;
                                printdlist(head);
                            }
                            else
                                cout<<target<<" has not been found"<<endl;
                            break;
                        case 7:
                            cleardlist(head);
                            printdlist(head);
                            break;
                        case 8:
                            cout<<"Please enter the target you want to search:";
                            cin>>target;
                            y=searchdlist(target);
                            if(y)
                                cout<<y->datad<<" has been found"<<endl;
                            else
                                cout<<target<<" has not been found"<<endl;
                            break;
                        case 9:
                            invertd();
                            printdlist(head);
                            break;
                    }
                    cout<<"Try another function ? Please enter the number derectly. If you wnat to quit enter 0"<<endl<<"Function:"<<endl<<"1.Insert first"<<endl<<"2.Insert last"<<endl<<"3.Insert after"<<endl<<"4.Insert before"<<endl<<"5.Insert n random numbers"<<endl<<"6.Delete target"<<endl<<"7.Clear list"<<endl<<"8.Search target "<<endl<<"9.Invert list"<<endl<<"You:";
                    cin>>fund;
                }while(fund!=0);
                cleardlist(head);
                break;
        }
        cout<<"Try another mode? Please enter Y or N"<<endl<<"You:";
        cin>>ans;
    }while(ans=='y'||ans=='Y');
    free(first);
    free(top);
    free(front);
    free(head);
    return 0;
}

struct node *newnode(int element)
{
    struct node *p;
    p = (struct node *) malloc (sizeof(struct node));
    p->data = element;
    p->next = NULL;
    return p;
}

struct Dnode *newdnode(int element)
{
    struct Dnode *p;
    p = (struct Dnode *) malloc (sizeof(Dnode));
    p->datad = element;
    p->prev = NULL;
    p->nextd = NULL;
    return p;
}

void initial()
{
    first = newnode(0);
    first->next = first;
    last = first;
}

void initialstack()
{
    top = newnode(0);
    top->next = top;
}

void initialqueue()
{
    front = newnode(0);
    front->next = front;
    rear = front;
}

void initiald()
{
    head = newdnode(0);
    head->nextd = head->prev = head;
}

void insertfirst(int element)
{
    struct node*p = newnode(element);
    p->next = first->next;
    first->next = p;
    if(last==first)
        last = p;
}

void insertafter(struct node *x, int element)
{
    struct node *p = newnode(element);
    p->next = x->next;
    x->next = p;
}

void insertlast(int element)
{
    struct node *p = newnode(element);
    p->next = last->next;
    last->next = p;
    last = p;
}

int deleteafter(struct node *p)
{
    struct node *q;
    int item;
    q = p->next;
    p->next =q->next;
    item = q->data;
    if(q==last)
        last=p;//p變first
    free(q);
    return item;
}

void clearlist(struct node *first)
{
    struct node *p;
    for (p=first->next;p!=first;p=first->next)
    {
        first->next = p->next;
        free(p);
    }
    last = first;
}

struct node *searchdata(int target)
{
    struct node *p;
    for (p=first->next;(p!=first && p->data!=target);p=p->next);
    if(p == first)
        return NULL;
    return p;
}

struct node *searchdatabefore(int target)
{
    struct node *p, *q;
    p = first;
    for (q=first,p=first->next;(p!=first && p->data!=target);q=p,p=p->next);
    if(p == first)
        return NULL;
    return q;
}

void printlist(struct node * first)
{
    struct node *p;
    for(p=first->next;p!=first;p=p->next)
        cout<<p->data<<" ==> ";
    cout<<"<"<<endl;
}

void invert()
{
    struct node *r,*s,*t;
    last = first->next;
    r = first->next ;
    s = first;
    while (r!= first)
    {
        t = s;
        s = r;
        r = r->next;
        s->next = t;
    }
    first->next = s;
}

void pushstack(int element)
{
    struct node *x;
    x = newnode(element);
    x->next = top->next;
    top->next = x;
}

int popstack()
{
    int element;
    struct node *p = top->next;
    if(p==top)
        return -1;
    element = p->data;
    top->next = p->next;
    free(p);
    return element;
}

void printstack(struct node *first)
{
    struct node *p;
    string list ="";
    for(p=first->next;p!=first;p=p->next)
        cout<<p->data<<" ==> ";
    cout<<"<"<<endl;
}

void clearstack(struct node *top)
{
    struct node *p;
    for (p=top->next;p!=top;p=top->next)
    {
        top->next = p->next;
        free(p);
    }
}

void addqueue(int element)
{
    struct node *p;
    p = newnode(element);
    p->next = rear->next;
    rear->next = p;
    rear = p;
}

int deletequeue()
{
    struct node *p;
    int element;
    if(front == rear)
        return -1;
    p = front->next;
    front->next = front->next->next;
    element = p->data;
    if(p==rear)
        rear = front;
    free(p);
    return element;
}

void printqueue(struct node *front)
{
    struct node *p;
    string list ="";
    for(p=front->next;p!=front;p=p->next)
        cout<<p->data<<" ==> ";
    cout<<"<"<<endl;
}

void clearqueue(struct node *front)
{
    struct node *p;
    for (p=front->next;p!=front;p=front->next)
    {
        front->next = p->next;
        free(p);
    }
    rear = front;
}

void insertfirstdlist(int element)
{
    struct Dnode*p = newdnode(element);
    p->nextd = head ->nextd;
    p->prev = head;
    head->nextd = p;
    if(head->prev==head)
        head->prev = p;
}

void insertafterdlist(struct Dnode *x,int element)
{
    struct Dnode *p = newdnode(element);
    p->prev = x;
    p->nextd = x->nextd;
    x->nextd->prev = p;
    x->nextd = p;
}

void insertlastdlist(int element)
{
    struct Dnode *p = newdnode(element);
    p->prev = head->prev;
    p->nextd = head;
    head->prev->nextd=p;
    head->prev=p;
}

int deletedlist(struct Dnode *x)
{
    int item;
    item = x->datad;
    x->prev->nextd = x->nextd;
    x->nextd->prev = x->prev;
    free(x);
    return item;
}

void cleardlist(struct Dnode *head)
{
    struct Dnode *p;
    for (p=head->nextd;p!=head;p=head->nextd)
    {
        head->nextd = p->nextd;
        p->nextd->prev=head;
        free(p);
    }
}

struct Dnode *searchdlist(int target)
{
    struct Dnode *p;
    for(p=head->prev;((p->datad!=target)&&(p->prev!=head));p=p->prev);
    if(p->prev == head)
        return NULL;
    return p;
}

struct Dnode *searchdatadbefore(int target)
{
    struct Dnode *p;
    for(p=head->prev;((p->datad!=target)&&(p->prev!=head));p=p->prev);
    if(p->prev == head)
        return NULL;
    return p->prev;
    
}

void printdlist(struct Dnode * head)
{
    struct Dnode *p;
    for(p = head->nextd;p!=head;p=p->nextd)
        cout<<p->datad<<" ==> ";
    cout<<"<"<<endl;
   
}

void invertd()
{
    struct Dnode *r,*s,*t;
    head->prev = head->nextd;
    r = head->nextd;
    s = head;
    while (r!= head)
    {
        t = s;
        s = r;
        r = r->nextd;
        s->nextd = t;
    }
    head->nextd = s;
}


