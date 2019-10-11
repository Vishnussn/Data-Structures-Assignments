#include <stdio.h>
#include <stdlib.h>
#define ll long long
#include <string.h>
struct node{
ll data;
struct node*left;
struct node*right;
};
void insert_end(struct node** head_ref, int new_data)
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
 void insert_begin(struct node** temp,int x){
 struct node*temp1 = (struct node*)malloc(sizeof(struct node));
 temp1->data=x;
 temp1->right=*temp;
 temp1->left=NULL;
 if((*temp)==NULL){
    *temp=temp1;
 }
 else
    (*temp)->left=temp1;
    *temp=temp1;
}
void add (struct node**first,struct node**second,struct node**temp,ll r,ll q){
while((*first)->right!=NULL){
        (*first)=(*first)->right;
}
while((*second)->right!=NULL){
        (*second)=(*second)->right;
}
ll i=0;
for(i=0;i<q;i++){
    if((*first)->data+(*second)->data+r<10){
        insert_begin(temp,(*first)->data+(*second)->data+r);
        r=0;
    }
    else
        {insert_begin(temp,(*first)->data+(*second)->data+r-10);
        r=1;}
    if(i!=q-1){(*first)=(*first)->left;
        (*second)=(*second)->left;}
}
if(r==1){
    insert_begin(temp,1);
}
}
void print(struct node*temp){
 while(temp!=NULL){
    printf("%d",temp->data);
    temp=temp->right;
 }
}
ll max(int x,int y){
    if(x>=y){
        return x;
            }
    else
        return y;
                   }
   void deleteList(struct node** head_ref)
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

int main(){
  char digit;
  int i;
  int x=0;int y=0;
  int t=0;

  struct node*head1=NULL;
  struct node*end1=NULL;
  struct node*head2=NULL;

  while((digit=fgetc(stdin))!=EOF){
    if(digit=='\n'){
        if(head1==NULL&&head2==NULL){
            printf("0\n");
            x=0;y=0;t=0;
                                    }
        else {
        for(i=0;i<abs(x-y);i++){
        if(x>y) insert_begin(&head2,0);
        else {insert_begin(&head1,0);}
                               }
        struct node*head3=NULL;
        int r=0;
        add(&head1,&head2,&head3,0,max(x,y));
        print(head3);
        printf("\n");
        deleteList(&head3);
        deleteList(&head1);
        deleteList(&head2);
        x=0;y=0;t=0;}
    }
    else if(digit==' '){
      struct node*head2=NULL;
      t=2;
    }
    else{
      if(t==2)             {
        if(head2==NULL&&digit=='0') continue;
        else {
                insert_end(&head2,digit-'0');
                y++;
             }

                       }
       if(t==0){

          if(head1==NULL&&digit=='0') continue;
          else {
                insert_end(&head1,digit-'0');
                x++;
               }

               }
        }
  }
  return(0);
}
