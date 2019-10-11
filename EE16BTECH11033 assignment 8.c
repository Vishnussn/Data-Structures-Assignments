#include <stdio.h>
#include <stdlib.h>
struct node* temp;
struct node* nill;
struct node* root;
int i = -1067;
struct node{
	int data;
	char color;
	struct node* left;
	struct node* right;
	struct node* parent;
};

void print(struct node* ptr);
struct node* newnode(int n,struct node* parent);
void leftrotate(struct node* x);
void rightrotate(struct node* y);
void rbfix(struct node* z);
void insert(struct node* rootk,int n);
void find(struct node* rootk,int n);
void rbdelete(struct node*x);
void rbfixup(struct node*x);
int present(int n);
void deleteTree(struct node* n)/*this function is used to delete the entire tree*/
{
    if (n == nill) return;
    deleteTree(n->left);
    deleteTree(n->right);
    free(n);
}
int min(int a,int b)
{
   if(a<=b) return a;
   else return b;
}
void children(int n)
{
    struct node*t=root;
    while(t->data!=i){
        if(t->data>n)
        {
            t=t->left;
        }
        else if(t->data<n)
        {
            t=t->right;
        }
        else
        {
            if(t->left->data!=i){
                printf("%d %c ",t->left->data,t->left->color);
            }
            else if(t->left->data==i){
                printf("L B ");
            }
            if(t->right->data!=i){
                printf("%d %c ",t->right->data,t->right->color);
            }
            else if(t->right->data==i){
                printf("L B ");
            }
            return;
        }
    }
}
void sucessor(int n)
{
    struct node *t=root;
    int p =2147483647;
    while(t->data!=i){
        if(t->data<=n){
            t=t->right;
        }
        else if(t->data>n){
            p=min(p,t->data);
            t=t->left;
        }
    }
    if(p==2147483647) printf("-1\n");
    else printf("%d\n",p);
}
int main()
{

	nill=newnode(i,NULL);
	root=nill;
	nill->color='B';
	char choice;
	while((choice=fgetc(stdin))!=EOF)
	{
		if(choice=='N')
		{
			if(root->data!=i)
            {
                deleteTree(root);
			}
			root=nill;
			int n;
			while(fgetc(stdin)!='\n')
            {
                scanf("%d",&n);
			    insert(root,n);
            }
		}
		else if(choice=='+')
        {
            int k;
            scanf("%d",&k);
            insert(root,k);
		}
		else if(choice=='P')
		{
			print(root);
			printf("\n");
		}
		else if(choice=='>')
		{
            int foo;
			scanf("%d",&foo);
			sucessor(foo);
		}
		else if(choice=='C')
        {
            int k;
            scanf("%d",&k);
            children(k);
            printf("\n");
		}
		else if(choice=='-')
		{
            int r;
            scanf("%d",&r);
            struct node* p=root;
            while(p->data!=i){
                if(p->data>r) p=p->left;
                else if(p->data<r) p=p->right;
                else {
                    break;
                }
            }
            if(p->data!=i)
            {
                rbdelete(p);
            }
		}
		else if(choice=='S')
        {
            int s;
            scanf("%d",&s);
            if(present(s)==1) /*prints path if only present in the tree*/
            {
                find(root,s);
            }
            else
            {
                printf("-1");
            }
            printf("\n");
		}
	}
}

int present(int n)        /*returns 1 if present*/
{
     struct node* t=root;
     if ( t == nill){
        return 0;
     }
     while(t!=nill){
        if(t->data>n){
            t=t->left;
        }
        else if(t->data<n){
            t=t->right;
        }
        else{
            return 1;
        }
     }
     return 0;
}
void print(struct node *ptr) /*preorder tree traversal*/
{
	if(ptr==nill) return;

	printf("%d ",ptr->data);

    print(ptr->left);

	print(ptr->right);
}
struct node* newnode(int n,struct node* parent)
{
	struct node* p = malloc(sizeof(struct node));
	p->data=n;
	p->left=nill;
	p->right=nill;
	p->parent=parent;
	p->color ='R';
	if(parent==nill)
		p->color='B';
	return p;
}

void leftrotate(struct node* x)
{
	struct node* y=x->right;
	x->right=y->left;
	if(y->left->data!=i)
	{
		y->left->parent=x;
	}
	y->parent=x->parent;
	if(x->parent->data==i)
	{
		root = y;
	}
	else if(x==x->parent->left)
	{
		x->parent->left=y;
	}
	else
	{
		x->parent->right=y;
	}
	y->left=x;
	x->parent=y;
}

void rightrotate(struct node* y)
{
	struct node* x=y->left;
	y->left=x->right;
	if(x->right->data!=i)
	{
		x->right->parent=y;
	}
	x->parent=y->parent;
	if(y->parent->data==i)
	{
		root = x;
	}
	else if(y==y->parent->right)
	{
		y->parent->right=x;
	}
	else
	{
		y->parent->left=x;
	}
	x->right=y;
	y->parent=x;
}


void rbfix(struct node* z)
{
	while(z->parent->color=='R')
	{
		if(z->parent==z->parent->parent->left)			//z'parent is left child of z's grand parent
		{
			struct node* y=z->parent->parent->right;
			if(y->color=='R')							//z's Uncle y is red
			{
				z->parent->color='B';
				y->color='B';
				z->parent->parent->color='R';
				z=z->parent->parent;
			}
			else if(z==z->parent->right)				//z's Uncle y is black and z is a right child
			{
				z=z->parent;
				leftrotate(z);
			}

			else										//z's Uncle y is black and z is a left child
			{
				z->parent->color='B';
				z->parent->parent->color='R';
				rightrotate(z->parent->parent);
			}

		}
		else											//z'parent is right child of z's grand parent
		{
			struct node* y=z->parent->parent->left;
			if(y->color=='R')							//z's Uncle y is red
			{
				z->parent->color='B';
				y->color='B';
				z->parent->parent->color='R';
				z=z->parent->parent;
			}
			else if(z==z->parent->left)					//z's Uncle y is black and z is a left child
			{
				z=z->parent;
				rightrotate(z);
			}

			else										//z's Uncle y is black and z is a left child
			{
				z->parent->color='B';
				z->parent->parent->color='R';
				leftrotate(z->parent->parent);
			}
		}
	}
	root->color='B';
}
void insert(struct node* rootk,int n)
{
	if(rootk->data==i)                   /*checks if rootk is nill*/
	{
		root=newnode(n,nill);
		return;
	}
	temp = nill;

	while(rootk->data!=i)
	{
        if(rootk->data==n)
        {
            return;
        }
		else if(rootk->data<n)
		{
			temp=rootk;
			rootk=rootk->right;
		}
		else if(rootk->data>n)
		{
			temp=rootk;
			rootk=rootk->left;
		}
	}

	if(rootk->data==i)
	{
		struct node* p = newnode(n,temp);

		if(temp->data<=n)
		{
			temp->right=p;
		}
		else
			temp->left=p;

		rbfix(p);

	}
}
void transplant(struct node*x,struct node*y)
{
    if(x->parent->data==i)               /*changing x parents to y parents*/
    {
        root=y;
    }
    else if(x==x->parent->left){
        x->parent->left=y;
    }
    else
    {
        x->parent->right=y;
    }
    y->parent=x->parent;
}
void rbdelete(struct node *z)             /*Deletes the node from the rb tree*/
{
	struct node *x=NULL,*y=z;

	char y_old_colour=y->color;

	if(z->left->data==i)                     /*case 1 when only right subtree is present*/
	{
		x=z->right;

		transplant(z,z->right);
	}

	else if(z->right->data==i)               /*case 2 when only left subtree is present*/
	{
		x=z->left;

		transplant(z,z->left);
	}

	else                                  /*case 3 in this case z is replaced by its predecessor*/
	{
		if(z->left->right->data==i) y=z->left;

		else
		{
			y=z->left->right;

			while(y->right->data!=i)
			{
				y=y->right;
			}
		}

		y_old_colour=y->color;

		x=y->left;

        transplant(y,y->left);

		z->data=y->data;
	}

	if(y_old_colour=='B')            /*performs rbfixup if replaced node colour is black*/
	{
		rbfixup(x);
	}
	free(y);
}
void rbdelete1(struct node *w,struct node *x)
{
    if(w=x->parent->right)                  //x sibling w is red
    {
    w->color='B';

    x->parent->color='R';

    leftrotate(x->parent);

    w=x->parent->right;
    }
    else if(w=x->parent->left)
    {
    w->color='B';

    x->parent->color='R';

    rightrotate(x->parent);

    w=x->parent->left;
    }

}
void rbdelete2(struct node *w,struct node *x)
{

     if(w=x->parent->right)
    {
      w->color='B';                                //when x sibling w is black and both of w children are black

      x=x->parent;
    }
    else if(w=x->parent->left)
    {
      w->color='R';

      x=x->parent;
    }
}
void rbdelete3(struct node *w,struct node *x){
        if(w=x->parent->right)
        {
            if(w->right->color=='B')                 //x sibling w is black, w left child is red and w right child is black
            {
                w->left->color='B';

                w->color='R';

                rightrotate(w);

                w=x->parent->right;
            }

            w->color=x->parent->color;                 //the above case changes into case where x sibling w is black and w right child is red

            x->parent->color='B';

            w->right->color='B';

            leftrotate(x->parent);

            x=root;
        }
        else if(w=x->parent->left)
        {
            if(w->left->color=='B')
				{
					w->right->color='B';

					w->color='R';

					leftrotate(w);

					w=x->parent->left;
				}

				w->color=x->parent->color;

				x->parent->color='B';

				w->left->color='B';

				rightrotate(x->parent);

				x=root;
        }
}
void rbfixup(struct node *x)         /*Fixes up the delete tree*/
{
	struct node *w=NULL;

	while(x!=root && x->color=='B')
	{
		if(x==(x->parent->left))
		{
			w=x->parent->right;

			if(w->color=='R')
			{
				rbdelete1(w,x);
			}

			if(w->left->color=='B' && w->right->color=='B')
			{
				rbdelete2(w,x);
			}

			else
			{
                rbdelete3(w,x);
			}
		}
		else
		{
			w=x->parent->left;

			if(w->color=='R')
			{
				rbdelete1(w,x);
			}

			if(w->right->color=='B' && w->left->color=='B')
			{
				rbdelete2(w,x);
			}

			else
			{
				rbdelete3(w,x);
			}
		}
	}

	x->color='B';
}
void find(struct node*t,int n){
    if(t->data==i)
        {
        printf("-1");
        return;
        }
    else if(t->data==n)
        {
            printf(" %c",t->color);
            return;
        }
    else if(t->data>n)
        {
        printf("0");
        find(t->left,n);
        }
    else if(t->data<n)
        {
        printf("1");
        find(t->right,n);
        }
}
