#include <stdio.h>
#include <stdlib.h>
struct node{
int data;
struct node* right;
struct node* left;
};
struct bstnode{   /*Defining a binary search tree node which has pointers to head of linked list,right,left and parent*/
struct node* head;
struct bstnode* right;
struct bstnode* left;
struct bstnode* parent;
};
void insert_end(struct node** head_ref, int new_data) /*inserts at the end of the linked list*/
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    struct node* last = *head_ref;
    new_node->data = new_data;
    new_node->right = NULL;
    if (*head_ref == NULL) {
        new_node->left = NULL;
        *head_ref = new_node;
        return;
    }

    while (last->right != NULL)
        last = last->right;

    last->right = new_node;
    new_node->left = last;

}
int length(struct node*temp){  /*returns the length of the linked list by traversing the list*/
int x=0;
while(temp!=NULL){
    x++;
    temp=temp->right;
}
return x;
}
int compare(struct node*temp1,struct node*temp2){ /*compares two linked lists by taking head pointers and returns 1,0and 2 if greater,less or equal*/
if(length(temp1)>length(temp2)) return 1;
else if(length(temp2)>length(temp1)) return 0;
else{
    while (temp1!=NULL){
    if(temp1->data>temp2->data) return 1;
    else if(temp2->data>temp1->data) return 0;
    else{
    temp1=temp1->right;
    temp2=temp2->right;
        }
}
if(temp1==NULL) return 2;
}
}
struct bstnode* newnode(struct node* temp){/*to create a new bst node and returns pointer to it*/
struct bstnode *temp1=(struct bstnode *)malloc(sizeof(struct bstnode));
temp1->head = temp;
temp1->right= NULL;
temp1->left = NULL;
temp1->parent = NULL;
return temp1;
};

struct bstnode* insertbst(struct node* head1,struct bstnode* node ) /*inserts given list of numbers in the binary search tree*/
{
    if (node == NULL) return newnode(head1);
    else{
        while(node!=NULL){
            if(compare(head1,node->head)==1){
                if(node->right==NULL){
                    node->right=newnode(head1);
                    node->right->parent=node;
                    return;
                                     }
                else node=node->right;
            }
            else if(compare(head1,node->head)==0){
                if(node->left==NULL){
                    node->left=newnode(head1);
                    node->left->parent=node;
                    return;
                }
                else node=node->left;
            }
            else if(compare(head1,node->head)==2) {
                                                   return;
                                                   }
            }
            }
}

   void deleteList(struct node** head_ref) /*deletes the linked list by taking the address of the head pointer*/
{
   struct node* current = *head_ref;
   struct node* next;

   while (current != NULL)
   {
       next = current->right;
       free(current);
       current = next;
   }

   *head_ref = NULL;
}
void deleteTree(struct bstnode* node)/*this function is used to delete the entire tree*/
{
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    deleteList(&node->head);
    free(node);
}
void print(struct node *temp){ /*prints the linked list by traversing from left to right*/
if(temp==NULL) return;
while(temp!=NULL){
    printf("%d",temp->data);
    temp=temp->right;
}
printf(" ");
}
void find(struct bstnode*root,struct node*temp,struct node**temp1){ /*prints the path from root to the given number by comparing the nodes and traversing forward*/
if(root==NULL){
    deleteList(temp1);
    printf("-1");
    return;
}
else if(compare(root->head,temp)==2){
                            print(*temp1);
                            deleteList(temp1);
                            return;}
else if(compare(root->head,temp)==1){
    insert_end(temp1,0);
    find(root->left,temp,temp1);
                                }
else if(compare(root->head,temp)==0){
    insert_end(temp1,1);
    find(root->right,temp,temp1);   }

}
void printPreorder(struct bstnode* node) /*prints preorder traversal of the bst*/
{
     if (node == NULL)
          return;


     print(node->head);

     printPreorder(node->left);

     printPreorder(node->right);
}
void findgreater(struct node*temp,struct bstnode*root){/* finds the least number greater than the given number and returns*/
struct bstnode*temp1=root;
struct bstnode*temp2;
while(temp1!=NULL){
    if(compare(temp,temp1->head)==1) temp1=temp1->right;
    else if(compare(temp,temp1->head)==0) temp1=temp1->left;
    else if(compare(temp,temp1->head)==2){ temp2=temp1;
            break;}
}
if(temp1->right!=NULL){
    temp2=temp2->right;
    while(temp2->left!=NULL){
        temp2=temp2->left;
    }
    print(temp2->head);
}
else if(temp1->right==NULL){
    if(temp2==root) {printf("-1");return;}
    else{
    while(compare(temp2->parent->head,temp2->head)!=1&&temp2->parent->parent!=NULL){
         temp2=temp2->parent;
                                                                                   }
    if(temp2->parent->parent==NULL&&compare(temp2->parent->head,temp2->head)==1) print(temp2->parent->head);
    else if(temp2->parent->parent==NULL&&compare(temp2->parent->head,temp2->head)==0) printf("-1");
    else print(temp2->parent->head);
        }
                            }

}
struct bstnode* removenode(struct bstnode* root,struct node *head){ /*removes the node from the tree using recursion*/
  if (root==NULL){
    return root;
  }
  if (compare(head,root->head)==0){
    root->left=removenode(root->left,head);
  }
  else if (compare(head,root->head)==1){
    root->right=removenode(root->right,head);
  }
  else{
    struct bstnode *temp;

    if (root->left==NULL){/* if node has only right branch*/
      temp =root->right;
      if(root->right!=NULL){
      temp->parent=root->parent;
      }
      free(root);
      return temp;
    }
    else if (root->right==NULL){/* if node has only left branch*/
      temp=root->left;
      if(root->left!= NULL){
      temp->parent=root->parent;
      }
      free(root);
      return temp;
    }/* else if it has both branches*/
    temp=root->right;
    while(temp->left!=NULL){/* finds minimum in right sub branch and replaces with the node*/
      temp=temp->left;
    }
    root->head=temp->head;
    root->right=removenode(root->right,temp->head);
  }
  return root;
}
int find1(struct node*temp,struct bstnode* root){ /*tells if the number given is present in the tree or not*/
  while(root!=NULL){
    if(compare(temp,root->head)==1) root=root->right;
    else if(compare(temp,root->head)==0) root=root->left;
    else return 1;
  }
  return 0;
}
int main(){
  char digit;
  struct node*head1=NULL;
  struct bstnode*root=NULL;
  int t;
  while((digit=fgetc(stdin))!=EOF){ /*assigning seperate values to t for different cases of input and inserts in bst*/
 if(digit=='N') {
    if(root!=NULL) {deleteTree(root);}
    root = NULL;
    t=1;
 }
 if(digit=='S'){
    t=2;
               }
 if(digit=='P'){
    t=3;
 }
 if(digit=='+'){
    t=4;
 }
 if(digit=='>'){
    t=5;
 }
 if(digit=='-'){
    t=6;
 }
 if(t==1&&digit!='N'){
if(digit=='\n'){
        if(root==NULL) {root=insertbst(head1,root);}
        else if(root!=NULL){
                insertbst(head1,root);
                           }
        head1=NULL;
               }
    else if(digit==' '){
      if(head1!=NULL){
        if(root==NULL){
        root = insertbst(head1,root);
                       }
        else if(root!=NULL){
               insertbst(head1,root);
            }
        head1=NULL;  }
        else {continue;}

                        }
    else {
        if(head1==NULL&&digit=='0') continue;
        else {
                insert_end(&head1,digit-'0');
             }

         }
 }
     if(t==2&&digit!='S'){
      if(digit=='\n'){
            struct node*temp1=NULL;
            find(root,head1,&temp1);
            deleteList(&head1);
            printf("\n");
        }
       else if(digit!=' '&&digit!='\n'){
           if(head1==NULL&&digit=='0') continue;
           else {
                insert_end(&head1,digit-'0');
           }
        }

         }
 if(t==3&&digit!='P') {
    printPreorder(root);
    printf("\n");
          }
 if(t==4&&digit!='+'){
   if(digit==' ') continue;
   else if(digit=='\n') {
                         if(root==NULL) root=insertbst(head1,root);
                         else if(root!=NULL) {
                                insertbst(head1,root);
                                             }
                         head1=NULL;
                        }
   else {if(head1==NULL&&digit=='0') continue;
          else {
               insert_end(&head1,digit-'0');
               }
         }
 }
 if(t==5&&digit!='>'){/* for printing value greater than given number*/
    if(digit==' ') continue;
    else if(digit=='\n') {
                            if(find1(head1,root)==1)
                                                 {
                                                   findgreater(head1,root);
                                                   printf("\n");
                                                   deleteList(&head1);
                                                 }
                           else {
                                insertbst(head1,root);
                                findgreater(head1,root);
                                printf("\n");
                                removenode(root,head1);
                                deleteList(&head1);
                                }

                         }
    else {
            if(head1==NULL&&digit=='0') continue;
             else {
                   insert_end(&head1,digit-'0');
                  }
         }
 }
 if(t==6&&digit!='-'){
    if(digit==' ') continue;
    else if(digit=='\n') { /*for removing the given node*/
                          if(compare(root->head,head1)==2&&root->right==NULL&&root->left==NULL)
                            {
                            root=removenode(root,head1);
                            root=NULL;
                            deleteList(&head1);
                            }
                          else {
                          root=removenode(root,head1);
                          deleteList(&head1);
                               }
                          }
    else {
            if(head1==NULL&&digit=='0') continue;
             else {
                   insert_end(&head1,digit-'0');
                  }
         }
 }

  }

  return(0);

}
