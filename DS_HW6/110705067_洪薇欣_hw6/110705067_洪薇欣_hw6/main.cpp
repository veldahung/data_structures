#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct btreenode
{
    struct btreenode *leftchild;
    int data;
    struct btreenode *rightchild;
};

struct stacknode
{
    struct btreenode *treenode;
    struct stacknode *next;
};

struct qnode
{
    struct btreenode *treenode;
    struct qnode *next;
};

struct avltreenode
{
    struct avltreenode *avlleftchild;
    int avldata;
    int height;
    struct avltreenode *avlrightchild;
};

struct qnode_avl
{
    struct avltreenode *avltreenode;
    struct qnode_avl *next;
};

struct btreenode *root;
struct stacknode *top;
struct qnode *front, *rear;
struct avltreenode *avlroot;
struct qnode_avl *avlfront, *avlrear;

void push_node(struct btreenode *node);
struct btreenode *pop_node();
void addqueue(struct btreenode *tnode);
struct btreenode *deletequeue();
void inorder_rec(struct btreenode *node);
void postorder_rec(struct btreenode *node);
void preorder_rec(struct btreenode *node);
void inorder_stack(struct btreenode *node);
void preorder_stack(struct btreenode *node);
void postoredr_stack(struct btreenode *node);
void levelorder(struct btreenode *node);
struct btreenode *searchbst_rec(struct btreenode *tree, int x);
struct btreenode *searchbst_iterative(struct btreenode *node, int x);
struct btreenode *newbstnode(int x);
struct btreenode *insertbstree_rec(struct btreenode *node, int x);
int insertbst_nr(int x);
struct btreenode * inordersucc(struct btreenode *node);
struct btreenode * deletebstree_rec(struct btreenode *node, int x);
int deletebstree_nr(int x);
int height(struct avltreenode *node);
struct avltreenode *newavlnode(int x);
struct avltreenode *leftrotate(struct avltreenode *x);
struct avltreenode *rightrotate(struct avltreenode *y);
int getbalance(struct avltreenode *n);
void addqueue_avl(struct avltreenode *tnode);
struct avltreenode *deletequeue_avl();
void avl_inorder_rec(struct avltreenode *node);
void avl_postorder_rec(struct avltreenode *node);
void avl_preorder_rec(struct avltreenode *node);
void avl_levelorder(struct avltreenode *node);
struct avltreenode *insertavltree_rec(struct avltreenode *node, int x);
struct avltreenode *searchavl_rec(struct avltreenode *tree, int x);
struct avltreenode *avl_inordersucc(struct avltreenode *node);
struct avltreenode *deleteavltree_rec(struct avltreenode *node, int x);
void print_bst(int num);
void print_avl(int num);

int main()
{
    
     int element,n,target,range,fun,mode,way;
     int *data;
     struct btreenode *tree;
     struct avltreenode *avltree;
     char ans;
     clock_t t_begin,t_end;
     double cputime;
     do
     {
         cout<<"Choose the mode (Please enter the number) :"<<endl<<"1.Binary Search Tree (recursively)"<<endl<<"2.Binary Search Tree (non-recursively)"<<endl<<"3.AVL Tree"<<endl<<"You:";
         cin>>mode;
         switch(mode)
         {
             case 1:
                 cout<<"Choose the function (Please enter the number) :"<<endl<<"1.Insert an data"<<endl<<"2.Insert n random numbers"<<endl<<"3.Delete target"<<endl<<"4.Search target "<<endl<<"You:";
                 cin>>fun;
                 do
                 {
                     switch(fun)
                     {
                         case 1:
                             cout<<"Please enter the element you want to insert:";
                             cin>>element;
                             t_begin=clock();
                             root=insertbstree_rec(root,element);
                             t_end=clock();
                             cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                             cout<<"Insert recursively:"<<cputime<<"s"<<endl;
                             cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                             cin>>way;
                             do
                             {
                                 print_bst(way);
                                 cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                                 cin>>way;
                             }while(way!=0);
                             break;
                         case 2:
                             cout<<"Please enter n for total random numbers you want to insert:";
                             cin>>n;
                             cout<<"Please enter range for the random numbers you want to generate:";
                             cin>>range;
                             data = new int[n];
                             srand(time(NULL));
                             t_begin=clock();
                             for(int i=0;i<n;i++)
                             {
                                 data[i] = rand() % range +1;
                                 root=insertbstree_rec(root,data[i]);
                             }
                             t_end=clock();
                             cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                             cout<<"Insert recursively:"<<cputime<<"s"<<endl;
                             cout<<"random numbers: ";
                             for(int i=0;i<n;i++)
                             {
                                 cout<<data[i]<<" ";
                             }
                             cout<<endl;
                             delete[] data;
                             cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                             cin>>way;
                             do
                             {
                                 print_bst(way);
                                 cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                                 cin>>way;
                             }while(way!=0);
                             break;
                         case 3:
                             cout<<"Please enter the target you want to delete:";
                             cin>>target;
                             t_begin=clock();
                             root=deletebstree_rec(root, target);
                             t_end=clock();
                             cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                             cout<<"Delete recursively:"<<cputime<<"s"<<endl;
                             cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                             cin>>way;
                             do
                             {
                                 print_bst(way);
                                 cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                                 cin>>way;
                             }while(way!=0);
                             break;
                         case 4:
                             cout<<"Please enter the target you want to search:";
                             cin>>target;
                             t_begin=clock();
                             tree=searchbst_rec(root, target);
                             t_end=clock();
                             cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                             cout<<"Search recursively:"<<cputime<<"s"<<endl;
                             if(tree==NULL)
                                 cout<<target<<" has not been found"<<endl;
                             else
                                 cout<<tree->data<<" has beeen found"<<endl;
                             break;
                     }
                     cout<<"Try another function ? Please enter the number derectly. If you wnat to quit enter 0"<<endl<<"Function:"<<endl<<"1.Insert an data"<<endl<<"2.Insert n random numbers"<<endl<<"3.Delete target"<<endl<<"4.Search target "<<endl<<"You:";
                     cin>>fun;
                 }while(fun!=0);
                 break;
             case 2:
                 cout<<"Choose the function (Please enter the number) :"<<endl<<"1.Insert an data"<<endl<<"2.Insert n random numbers"<<endl<<"3.Delete target"<<endl<<"4.Search target "<<endl<<"You:";
                 cin>>fun;
                 do
                 {
                     switch(fun)
                     {
                         case 1:
                             cout<<"Please enter the element you want to insert:";
                             cin>>element;
                             t_begin=clock();
                             insertbst_nr(element);
                             t_end=clock();
                             cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                             cout<<"Insert non-recursively:"<<cputime<<"s"<<endl;
                             cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                             cin>>way;
                             do
                             {
                                 print_bst(way);
                                 cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                                 cin>>way;
                             }while(way!=0);
                             break;
                         case 2:
                             cout<<"Please enter n for total random numbers you want to insert:";
                             cin>>n;
                             cout<<"Please enter range for the random numbers you want to generate:";
                             cin>>range;
                             data = new int[n];
                             srand(time(NULL));
                             t_begin=clock();
                             for(int i=0;i<n;i++)
                             {
                                 data[i] = rand() % range +1;
                                 insertbst_nr(data[i]);
                             }
                             t_end=clock();
                             cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                             cout<<"Insert non-recursively:"<<cputime<<"s"<<endl;
                             cout<<"random numbers: ";
                             for(int i=0;i<n;i++)
                             {
                                 cout<<data[i]<<" ";
                             }
                             cout<<endl;
                             delete[] data;
                             cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                             cin>>way;
                             do
                             {
                                 print_bst(way);
                                 cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                                 cin>>way;
                             }while(way!=0);
                             break;
                         case 3:
                             cout<<"Please enter the target you want to delete:";
                             cin>>target;
                             t_begin=clock();
                             if(deletebstree_nr(target)==0)
                                 cout<<target<<" has not been found"<<endl;
                             t_end=clock();
                             cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                             cout<<"Delete non-recursively:"<<cputime<<"s"<<endl;
                             cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                             cin>>way;
                             do
                             {
                                 print_bst(way);
                                 cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"5.Inoreder non-Recursively"<<endl<<"6.Postorder non-Recucursively"<<endl<<"7.Preorder non-Recursively"<<endl<<"You:";
                                 cin>>way;
                             }while(way!=0);
                             break;
                         case 4:
                             cout<<"Please enter the target you want to search:";
                             cin>>target;
                             t_begin=clock();
                             tree=searchbst_iterative(root, target);
                             t_end=clock();
                             cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                             cout<<"Search non-recursively:"<<cputime<<"s"<<endl;
                             if(tree==NULL)
                                 cout<<target<<" has not been found"<<endl;
                             else
                                 cout<<tree->data<<" has beeen found"<<endl;
                             break;
                             
                     }
                     cout<<"Try another function ? Please enter the number derectly. If you wnat to quit enter 0"<<endl<<"Function:"<<endl<<"1.Insert an data"<<endl<<"2.Insert n random numbers"<<endl<<"3.Delete target"<<endl<<"4.Search target "<<endl<<"You:";
                     cin>>fun;
                 }while(fun!=0);
                 break;
                 case 3:
                     cout<<"Choose the function (Please enter the number) :"<<endl<<"1.Insert an data"<<endl<<"2.Insert n random numbers"<<endl<<"3.Delete target"<<endl<<"4.Search target "<<endl<<"You:";
                     cin>>fun;
                     do
                     {
                         switch(fun)
                         {
                             case 1:
                                 cout<<"Please enter the element you want to insert:";
                                 cin>>element;
                                 t_begin=clock();
                                 avlroot=insertavltree_rec(avlroot, element);
                                 t_end=clock();
                                 cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                                 cout<<"Insert recursively(AVL):"<<cputime<<"s"<<endl;
                                 cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"You:";
                                 cin>>way;
                                 do
                                 {
                                     print_avl(way);
                                     cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"You:";
                                     cin>>way;
                                 }while(way!=0);
                                 break;
                             case 2:
                                 cout<<"Please enter n for total random numbers you want to insert:";
                                 cin>>n;
                                 cout<<"Please enter range for the random numbers you want to generate:";
                                 cin>>range;
                                 data = new int[n];
                                 srand(time(NULL));
                                 t_begin=clock();
                                 for(int i=0;i<n;i++)
                                 {
                                     data[i] = rand() % range +1;
                                     avlroot=insertavltree_rec(avlroot, data[i]);
                                 }
                                 t_end=clock();
                                 cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                                 cout<<"Insert recursively(AVL):"<<cputime<<"s"<<endl;
                                 cout<<"random numbers: ";
                                 for(int i=0;i<n;i++)
                                 {
                                     cout<<data[i]<<" ";
                                 }
                                 cout<<endl;
                                 delete[] data;
                                 cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"You:";
                                 cin>>way;
                                 do
                                 {
                                     print_avl(way);
                                     cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"You:";
                                     cin>>way;
                                 }while(way!=0);
                                 break;
                             case 3:
                                 cout<<"Please enter the target you want to delete:";
                                 cin>>target;
                                 t_begin=clock();
                                 avlroot=deleteavltree_rec(avlroot, target);
                                 t_end=clock();
                                 cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                                 cout<<"Delete recursively(AVL):"<<cputime<<"s"<<endl;
                                 cout<<"Choose the way you want to go through the tree (Please enter the number) :"<<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"You:";
                                 cin>>way;
                                 do
                                 {
                                     print_avl(way);
                                     cout<<"Try another the way? Please enter the number derectly. If you wnat to quit enter 0." <<endl<<"1.Inoreder Recursively"<<endl<<"2.Postorder Recucursively"<<endl<<"3.Preorder Recursively"<<endl<<"4.Level Order"<<endl<<"You:";
                                     cin>>way;
                                 }while(way!=0);
                                 break;
                             case 4:
                                 cout<<"Please enter the target you want to search:";
                                 cin>>target;
                                 t_begin=clock();
                                 avltree=searchavl_rec(avlroot, target);
                                 t_end=clock();
                                 cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
                                 cout<<"Delete recursively(AVL):"<<cputime<<"s"<<endl;
                                 if(avltree==NULL)
                                     cout<<target<<" has not been found"<<endl;
                                 else
                                     cout<<avltree->avldata<<" has beeen found"<<endl;
                                 break;
             }
            cout<<"Try another function ? Please enter the number derectly. If you wnat to quit enter 0"<<endl<<"Function:"<<endl<<"1.Insert an data"<<endl<<"2.Insert n random numbers"<<endl<<"3.Delete target"<<endl<<"4.Search target "<<endl<<"You:";
             cin>>fun;
         }while(fun!=0);
         break;
         }
         cout<<"Try another mode? Please enter Y or N"<<endl<<"You:";
         cin>>ans;
     }while(ans=='y'||ans=='Y');
}

void push_node(struct btreenode *node)
{
    struct stacknode *old_top;
    old_top = top;
    top = (struct stacknode*) malloc (sizeof(struct stacknode));
    top->treenode = node;
    top->next = old_top;
}

struct btreenode *pop_node()
{
    struct btreenode *tnode;
    struct stacknode *old_top;
    if(top==NULL)
    {
        cout<<"stack is empty"<<endl;
    }
    else
    {
        tnode = top->treenode;
        old_top = top;
        top =top->next;
        free(old_top);
        return tnode;
    }
    return root;
}

void addqueue(struct btreenode *tnode)
{
    struct qnode *node;
    node=(struct qnode *) malloc (sizeof(struct qnode));
    node->treenode=tnode;
    node->next=NULL;
    if(front==NULL)
        front=node;
    else
        rear->next=node;
    rear=node;
}

struct btreenode *deletequeue()
{
    struct btreenode *tnode;
    struct qnode *old_front;
    if(rear==NULL)
    {
        cout<<"queue is empty"<<endl;
    }
    else
    {
        tnode=front->treenode;
        old_front=front;
        front=front->next;
        free(old_front);
        return tnode;
    }
    return root;
}

void inorder_rec(struct btreenode *node)
{
    if(node!=NULL)
    {
        inorder_rec(node->leftchild);
        cout<<node->data<<"-";
        inorder_rec(node->rightchild);
    }
}

void postorder_rec(struct btreenode *node)
{
    if(node!=NULL)
    {
        postorder_rec(node->leftchild);
        postorder_rec(node->rightchild);
        cout<<node->data<<"-";
    }
}

void preorder_rec(struct btreenode *node)
{
    if(node!=NULL)
    {
        cout<<node->data<<"-";
        preorder_rec(node->leftchild);
        preorder_rec(node->rightchild);
    }
}

void inorder_stack(struct btreenode *node)
{
    do
    {
        while(node!=NULL)
        {
            push_node(node);
            node=node->leftchild;
        }
        if(top!=NULL)
        {
            node=pop_node();
            cout<<node->data<<"-";
            node=node->rightchild;
        }
    }while((top!=NULL)||(node!=NULL));
}

void preorder_stack(struct btreenode *node)
{
    do
    {
        while(node!=NULL)
        {
            cout<<node->data<<"-";
            push_node(node);
            node=node->leftchild;
        }
        if(top!=NULL)
        {
            node=pop_node();
            node=node->rightchild;
        }
    }while((top!=NULL)||(node!=NULL));
}

void postorder_stack(struct btreenode *node)
{
    do
    {
        while(node!=NULL)
        {
            cout<<node->data<<"-";
            push_node(node);
            node=node->rightchild;
        }
        if(top!=NULL)
        {
            node=pop_node();
            node=node->leftchild;
        }
    }while((top!=NULL)||(node!=NULL));
}

void levelorder(struct btreenode *node)
{
    addqueue(node);
    while(front!=NULL)
    {
        node=deletequeue();
        cout<<node->data<<"-";
        if(node->leftchild!=NULL)
            addqueue(node->leftchild);
        if(node->rightchild!=NULL)
            addqueue(node->rightchild);
    }
}

struct btreenode *searchbst_rec(struct btreenode *tree, int x)
{
    if(tree==NULL)
        return NULL;
    if(x==tree->data)
        return tree;
    if(x<tree->data)
        return searchbst_rec(tree->leftchild,x);
    return searchbst_rec(tree->rightchild,x);
}

struct btreenode *searchbst_iterative(struct btreenode *node, int x)
{
    while(node!=NULL)
    {
        if(x==node->data)
            return node;
        if(x<node->data)
            node=node->leftchild;
        else
            node=node->rightchild;
    }
    return NULL;
}

struct btreenode *newbstnode(int x)
{
    struct btreenode *node = (struct btreenode *) malloc (sizeof(struct btreenode)) ;
    node->data=x;
    node->leftchild=NULL;
    node->rightchild=NULL;
    return node;
}

struct btreenode *insertbstree_rec(struct btreenode *node, int x)
{
    if(node==NULL)
        return newbstnode(x);
    if(x<node->data)
        node->leftchild=insertbstree_rec(node->leftchild,x);
    else
        node->rightchild=insertbstree_rec(node->rightchild,x);
    return node;
}

int insertbst_nr(int x)
{
    struct btreenode *p,*q;
    p=root;
    q=NULL;
    while(p!=NULL)
    {
        q=p;
        if(x<p->data)
            p=p->leftchild;
        else
            p=p->rightchild;
    }
    p=(struct btreenode *)malloc(sizeof(btreenode));
    p->data=x;
    p->leftchild = p->rightchild = NULL;
    if(root==NULL)
        root=p;
    else if(x<q->data)
        q->leftchild=p;
    else
        q->rightchild=p;
    return 1;
}

struct btreenode * inordersucc(struct btreenode *node)
{
    struct btreenode *p=node;
    while(p->leftchild!=NULL)
        p=p->leftchild;
    return p;
}

struct btreenode * deletebstree_rec(struct btreenode *node, int x)
{
    struct btreenode *temp;
    if(node==NULL)
        return node;
    if(x<node->data)
        node->leftchild=deletebstree_rec(node->leftchild,x);
    else if(x>node->data)
        node->rightchild=deletebstree_rec(node->rightchild,x);
    else
    {
        if((node->leftchild==NULL)||(node->rightchild==NULL))
        {
            temp=node->leftchild ? node->leftchild:node->rightchild;
            if(temp==NULL)
            {
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;
            free(temp);
        }
        else
        {
            temp=inordersucc(node->rightchild);
            node->data=temp->data;
            node->rightchild=deletebstree_rec(node->rightchild,temp->data);
        }
    }
    return node;
}

int deletebstree_nr(int x)
{
    struct btreenode *p,*father,*k,*f;
    p=root;
    father=NULL;
    while(p!=NULL)
    {
        if(x==p->data)
        {
            if((p->leftchild==NULL)&&(p->rightchild==NULL))
                k=NULL;
            else if(p->leftchild!=NULL)
            {
                f=p;
                k=p->leftchild;
                while(k->rightchild != NULL)
                {
                    f=k;
                    k=k->rightchild;
                }
                if(p==f)
                    f->leftchild=k->leftchild;
                else
                    f->rightchild=k->leftchild;
                
            }
            else
            {
                f=p;
                k=p->leftchild;
                while(k->leftchild!=NULL)
                {
                    f=k;
                    k=k->leftchild;
                }
                if(p==f)
                    f->rightchild=k->rightchild;
                else
                    f->leftchild=k->rightchild;
            }
            if(k!=NULL)
            {
                k->leftchild=p->leftchild;
                k->rightchild=p->rightchild;
            }
            if(father==NULL)
                root=k;
            else if(x<father->data)
                father->leftchild=k;
            else
                father->rightchild=k;
            free(p);
            return 1;
        }
        else//未找到，往下一層
        {
            father=p;
            if(x<p->data)
                p=p->leftchild;
            else
                p=p->rightchild;
        }
    }
    return 0;//未找到
}

int height(struct avltreenode *node)
{
    if(node==NULL)
        return 0;
    return node->height;
}

struct avltreenode *newavlnode(int x)
{
    struct avltreenode *node=(struct avltreenode *) malloc (sizeof(struct avltreenode));
    node->avldata=x;
    node->height=1;
    node->avlleftchild=NULL;
    node->avlleftchild=NULL;
    return node;
}

struct avltreenode *leftrotate(struct avltreenode *x)
{
    struct avltreenode *y=x->avlrightchild;
    struct avltreenode *t2=y->avlleftchild;
    y->avlleftchild=x;
    x->avlrightchild=t2;
    x->height=max(height(x->avlleftchild),height(x->avlrightchild))+1;
    y->height=max(height(y->avlleftchild),height(y->avlrightchild))+1;
    return y;
}

struct avltreenode *rightrotate(struct avltreenode *y)
{
    struct avltreenode *x=y->avlleftchild;
    struct avltreenode *t2=x->avlrightchild;
    x->avlrightchild=y;
    y->avlleftchild=t2;
    y->height=max(height(y->avlleftchild),height(y->avlrightchild))+1;
    x->height=max(height(x->avlleftchild),height(x->avlrightchild))+1;
    return x;
}

int getbalance(struct avltreenode *n)
{
    if(n==NULL)
        return 0;
    return height(n->avlleftchild)-height(n->avlrightchild);
}

void addqueue_avl(struct avltreenode *tnode)
{
    struct qnode_avl *node;
    node=(struct qnode_avl *) malloc (sizeof(struct qnode_avl));
    node->avltreenode=tnode;
    node->next=NULL;
    if(avlfront==NULL)
        avlfront=node;
    else
        avlrear->next=node;
    avlrear=node;
}

struct avltreenode *deletequeue_avl()
{
    struct avltreenode *tnode;
    struct qnode_avl *old_front;
    if(avlrear==NULL)
    {
        cout<<"queue is empty"<<endl;
    }
    else
    {
        tnode=avlfront->avltreenode;
        old_front=avlfront;
        avlfront=avlfront->next;
        free(old_front);
        return tnode;
    }
    return avlroot;
}

void avl_inorder_rec(struct avltreenode *node)
{
    if(node!=NULL)
    {
        avl_inorder_rec(node->avlleftchild);
        cout<<node->avldata<<"-";
        avl_inorder_rec(node->avlrightchild);
    }
}

void avl_postorder_rec(struct avltreenode *node)
{
    if(node!=NULL)
    {
        avl_postorder_rec(node->avlleftchild);
        avl_postorder_rec(node->avlrightchild);
        cout<<node->avldata<<"-";
    }
}

void avl_preorder_rec(struct avltreenode *node)
{
    if(node!=NULL)
    {
        cout<<node->avldata<<"-";
        avl_preorder_rec(node->avlleftchild);
        avl_preorder_rec(node->avlrightchild);
    }
}

void avl_levelorder(struct avltreenode *node)
{
    addqueue_avl(node);
    while(avlfront!=NULL)
    {
        node=deletequeue_avl();
        cout<<node->avldata<<"-";
        if(node->avlleftchild!=NULL)
            addqueue_avl(node->avlleftchild);
        if(node->avlrightchild!=NULL)
            addqueue_avl(node->avlrightchild);
    }
}

struct avltreenode *insertavltree_rec(struct avltreenode *node, int x)
{
    if(node==NULL)
        return newavlnode(x);
    if(x<node->avldata)
        node->avlleftchild=insertavltree_rec(node->avlleftchild,x);
    else
        node->avlrightchild=insertavltree_rec(node->avlrightchild,x);
    node->height=max(height(node->avlleftchild),height(node->avlrightchild))+1;
    int balance=getbalance(node);
    if(balance>1&&x<node->avlleftchild->avldata)
        return rightrotate(node);
    if(balance<-1&&x>node->avlrightchild->avldata)
        return leftrotate(node);
    if(balance>1&&x>node->avlleftchild->avldata)
    {
        node->avlleftchild=leftrotate(node->avlleftchild);
        return rightrotate(node);
    }
    if(balance<-1&&x>node->avlrightchild->avldata)
    {
        node->avlrightchild=rightrotate(node->avlrightchild);
        return leftrotate(node);
    }
    return node;
}

struct avltreenode *searchavl_rec(struct avltreenode *tree, int x)
{
    if(tree==NULL)
        return NULL;
    if(x==tree->avldata)
        return tree;
    if(x<tree->avldata)
        return searchavl_rec(tree->avlleftchild,x);
    return searchavl_rec(tree->avlrightchild,x);
}

struct avltreenode * avl_inordersucc(struct avltreenode *node)
{
    struct avltreenode *p=node;
    while(p->avlleftchild!=NULL)
        p=p->avlleftchild;
    return p;
}

struct avltreenode * deleteavltree_rec(struct avltreenode *node, int x)
{
    struct avltreenode *temp;
    if(node==NULL)
        return node;
    if(x<node->avldata)
        node->avlleftchild=deleteavltree_rec(node->avlleftchild,x);
    else if(x>node->avldata)
        node->avlrightchild=deleteavltree_rec(node->avlrightchild,x);
    else
    {
        if((node->avlleftchild==NULL)||(node->avlrightchild==NULL))
        {
            temp=node->avlleftchild ? node->avlleftchild:node->avlrightchild;
            if(temp==NULL)
            {
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;
            free(temp);
        }
        else
        {
            temp=avl_inordersucc(node->avlrightchild);
            node->avldata=temp->avldata;
            node->avlrightchild=deleteavltree_rec(node->avlrightchild,temp->avldata);
        }
    }
    if(node==NULL)
        return node;
    node->height=max(height(node->avlleftchild),height(node->avlrightchild))+1;
    int balance=getbalance(node);
    if(balance>1&&x<node->avlleftchild->avldata)
        return rightrotate(node);
    if(balance<-1&&x>node->avlrightchild->avldata)
        return leftrotate(node);
    if(balance>1&&x>node->avlleftchild->avldata)
    {
        node->avlleftchild=leftrotate(node->avlleftchild);
        return rightrotate(node);
    }
    if(balance<-1&&x>node->avlrightchild->avldata)
    {
        node->avlrightchild=rightrotate(node->avlrightchild);
        return leftrotate(node);
    }
    return node;
}

void print_bst(int num)
{
    clock_t t_begin,t_end;//t_begin,t_end變數名 clock_t為變數型態
    double cputime;
    switch(num)
    {
        case 1:
            t_begin=clock();
            inorder_rec(root);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Inorder recursively:"<<cputime<<"s"<<endl;
            break;
        case 2:
            t_begin=clock();
            postorder_rec(root);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Postorder recursively:"<<cputime<<"s"<<endl;
            break;
        case 3:
            t_begin=clock();
            preorder_rec(root);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Preorder recursively:"<<cputime<<"s"<<endl;
            break;
        case 4:
            t_begin=clock();
            levelorder(root);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Level order:"<<cputime<<"s"<<endl;
            break;
        case 5:
            t_begin=clock();
            inorder_stack(root);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Inorder non-recursively:"<<cputime<<"s"<<endl;
            break;
        case 6:
            t_begin=clock();
            postorder_stack(root);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Postorder non-recursively:"<<cputime<<"s"<<endl;
            break;
        case 7:
            t_begin=clock();
            preorder_stack(root);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Preorder non-recursively:"<<cputime<<"s"<<endl;
            break;
    }
}

void print_avl(int num)
{
    clock_t t_begin,t_end;//t_begin,t_end變數名 clock_t為變數型態
    double cputime;
    switch(num)
    {
        case 1:
            t_begin=clock();
            avl_inorder_rec(avlroot);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Inorder recursively:"<<cputime<<"s"<<endl;
            break;
        case 2:
            t_begin=clock();
            avl_postorder_rec(avlroot);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Postorder recursively:"<<cputime<<"s"<<endl;
            break;
        case 3:
            t_begin=clock();
            avl_preorder_rec(avlroot);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Preorder recursively:"<<cputime<<"s"<<endl;
            break;
        case 4:
            t_begin=clock();
            avl_levelorder(avlroot);
            t_end=clock();
            cputime=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
            cout<<endl<<"Level order:"<<cputime<<"s"<<endl;
            break;
    }
}
