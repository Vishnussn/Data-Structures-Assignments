#include<stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node* next;
};

struct Graph                                        /* defining structure for graph*/
{
    int numVertices;
    struct node** adjLists;
};

struct queue
{
  struct node*front;
  struct node*rear;

};

int * pre=NULL;                                       /* for storing the predecessor vertices*/
int condition;

struct Graph* createGraph()               /* initializing the graph*/
{
    int vertices;
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    fgetc(stdin);
    scanf("%d",&vertices);
    graph->numVertices=vertices;
    fgetc(stdin);
    graph->adjLists = (struct node**) malloc(vertices * sizeof(struct node*));
    int i;
    for (i = 0; i < graph->numVertices; i++){
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph) /* adding edge to the graph in the given order*/
{
                                  // Add edge from src to dest at the end of the adjacency list of the src
     int src, dest;
    scanf("%d",&src);
    struct node* temp=graph->adjLists[src-1];
    while(fgetc(stdin)!='\n'){
        scanf("%d",&dest);
        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        newNode->data= dest-1;
        newNode->next=NULL;
        if(temp==NULL)
        {
            temp = graph->adjLists[src-1]=newNode;
            continue;
        }
        else
            temp->next=newNode;
        temp=temp->next;

    }

}

void deleteList(struct node** head_ref)    /*deletes the linked list by taking the address of the head pointer*/
{
   struct node* current = *head_ref;
   struct node* next;

   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }

   *head_ref = NULL;
}
void present(struct Graph* graph){          /* for checking if the edge exists between two nodes*/
    int x,y;
    fgetc(stdin);
    scanf("%d",&x);
    fgetc(stdin);
    scanf("%d",&y);
    fgetc(stdin);
    struct node*temp=graph->adjLists[x-1];
    while(temp!=NULL){                      /* checks in the adjacency list of the source*/
        if(temp->data==y-1){
            printf("1\n");
            return;
        }
        else temp=temp->next;
    }
    printf("0\n");
    return;
}
int isEmpty(struct queue* q) {             /* for telling if queue is null*/
    if(q->rear == NULL)
        return 0;
    else
        return 1;
}
void enqueue(struct queue *q, int value)   /* for inserting node into the queue the rear pointer of the queue is updated*/
{
    struct node *tmp =(struct node*)malloc(sizeof(struct node));   /* using temp as struct node pointer*/
    tmp->data = value;
    tmp->next = NULL;
    if(isEmpty(q)==1)
    {
        q->rear->next = tmp;
        q->rear = tmp;
    }
    else
    {
        q->front = q->rear = tmp;
    }
}
int dequeue(struct queue *q)                   /* for dequeing the queue(the node at the front is removed) and the front and rear of the queue are updated*/
{
    struct node *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    if(q->front==NULL){
        q->rear=NULL;
    }
    free(tmp);
    return(n);
}
void print_path(int v)                          /*prints the path using the pre array which stores the predeccesors*/
{
    if(pre[v]!=-1)
        print_path(pre[v]);
    printf("%d ",v+1);
}
void check(int v){                                               /* checks if path exists between given vertices exists or not*/
    if(pre[v]==-2){                                              /* if prdecessor doesnt get updated in the bfs function no path exists*/
        printf("-1");
        return;
    }
    print_path(v);
}
void bfs(int n,struct Graph* graph, int v) {                    /* bfs takes arguments size of graph, graph and the vertex */
    if(pre!=NULL){                                              /* the pre array(dynamic) stores the previous vertex of all the vertices when bfs of a given vertex is asked*/
        free(pre);
    }
    pre=NULL;
    pre=(int *)malloc((n+1)*sizeof(int));
    int i;
    int visited[n+1];
    for(i=0;i<n;i++){                                            /* initializing all the predecessor vertices of the given array to -2*/
        visited[i]=0;
        pre[i]=-2;
    }
    pre[n]=v;                                                    /* predecessor array stores the vertex for which bfs is found*/
    pre[v]=-1;                                                   /*predecessor of the given vertex is made -1*/
    struct queue *q =(struct queue*)malloc(sizeof(struct queue));/* initializing the queue*/
    q->front=NULL;
    q->rear=NULL;
    visited[v] = 1;
    enqueue(q, v);
    while(isEmpty(q)!=0){                                        /* in bfs it enqueues all the elements in the adjacency list and later deques the queues and now the numbers in adjacency list of the dequed element are enqued this is continued till the queue becomes empty*/
        int currentVertex = dequeue(q);
        if(condition==1) printf("%d ", currentVertex+1);

       struct node* temp = graph->adjLists[currentVertex];
       while(temp!=NULL) {
            int adjVertex = temp->data;
            if(visited[adjVertex] == 0){
                pre[adjVertex]=currentVertex;                    /* the predecessor of the vertex is changed and updated*/
                visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
       }
    }
}

void delet(struct Graph *g)      //deleting graph
{
    if(g ==NULL)
        return;
    for (int i = 0; i < g->numVertices; i++){
            deleteList(&g->adjLists[i]);
    }

}

int main(){
    char digit;
    struct Graph* graph=NULL;
    int x;
    int i;
    int y;
    while((digit=fgetc(stdin))!=EOF){
        if(digit=='N'){
            free(pre);                 //freeing pre and graph
            pre = NULL;
            delet(graph);
            graph=createGraph();
        }
        if(digit=='E'){
            addEdge(graph);            //adding edge
        }
        if(digit=='?'){
            present(graph);
        }
        if(digit=='B'){
            condition=1;
            fgetc(stdin);
            scanf("%d",&x);
            fgetc(stdin);
            bfs(graph->numVertices,graph,x-1);
            printf("\n");
        }
        if(digit=='P'){
            condition=2;
            fgetc(stdin);
            scanf("%d",&x);
            fgetc(stdin);
            scanf("%d",&y);
            fgetc(stdin);
            if(pre!=NULL&&pre[graph->numVertices]==x-1){ /*if predecessor array already stores the predecessors obtained by the bfs of the given number it doesnt perform bfs again*/
                check(y-1);                              /* checks if the vertices are connected in any way*/
            }
            else{
                condition=2;                              /* performs bfs and stores predecessors but doesnt print*/
                bfs(graph->numVertices,graph,x-1);
                check(y-1);                               /* checks if they are connected*/
            }
            printf("\n");
        }
    }
    return(0);
}
