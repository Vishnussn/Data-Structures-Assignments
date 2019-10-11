#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct node
{
    int data;
    int weight;
    struct node* next;
};
struct Graph                                        /* defining structure for graph*/
{
    int numVertices;
    struct node** adjLists;
};
struct HeapNode                          /*each heap node contains the value and the distance from the source node*/
{
    int  v;
    int dist;
};
int * pre=NULL;                          //for storing the predecessor vertices
int * dist=NULL;
int size;
int *pos;
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
struct HeapNode **create()                 // creates an empty minHeap array pointer to heap node
{
    struct HeapNode **minHeap = (struct HeapNode **) malloc(size*sizeof(struct HeapNode *));
    for(int i=0;i<size;i++)
    minHeap[i] = NULL;
    return minHeap;
}
struct HeapNode* newHeapNode(int v, int dist)
{
    struct HeapNode* temp =
           (struct HeapNode*) malloc(sizeof(struct HeapNode));
    temp->v = v;
    temp->dist = dist;
    return temp;
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
struct HeapNode **clear(struct HeapNode** h,int n){
    if(h==NULL)
              return NULL;
    for(int i=0;i<n;i++){
        free(h[i]);
    }
    return NULL;
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
            printf("%d\n",temp->weight);
            return;
        }
        else temp=temp->next;
    }
    printf("-1\n");
    return;
}
void addEdge(struct Graph* graph) /* adding edge to the graph in the given order*/
{
                                // Add edge from src to dest at the end of the adjacency list of the src
    int src, dest,w;
    scanf("%d",&src);
    struct node* temp=graph->adjLists[src-1];
    while(fgetc(stdin)!='\n'){
        scanf("%d",&dest);
        scanf("%d",&w);
        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        newNode->data= dest-1;
        newNode->weight=w;
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
void swapHeapNode(struct HeapNode** a, struct HeapNode** b)
{
    struct HeapNode* t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(struct HeapNode** minHeap, int i)  /* heapifies the nodes if they dont form minheap*/
{
    int s, l, r;
    s=i;

    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < size && minHeap[l]->dist < minHeap[s]->dist )
        s=l;

    if (r < size && minHeap[r]->dist < minHeap[s]->dist )
        s=r;

    if (s!=i)
    {
        struct HeapNode *temp = minHeap[s];
        struct HeapNode *temp1 = minHeap[i];
        pos[temp->v] = i;                         /*changes positions of the nodes*/
        pos[temp1->v] = s;
        swapHeapNode(&minHeap[s], &minHeap[i]);
        minHeapify(minHeap, s);                   /*again performs heapify at the node where interchange took place*/
    }
}
struct HeapNode* extractMin(struct HeapNode **minHeap) /*returns the heapnode at the zeroth index*/
{
    if(size==0) return NULL;

    struct HeapNode* root = minHeap[0];
    struct HeapNode* lastNode = minHeap[size-1];
    minHeap[0] = lastNode;
    pos[root->v] = size-1;                          /*interchanges the position of first node with last*/
    pos[lastNode->v] = 0;
    size=size-1;
    minHeapify(minHeap, 0);                         /*again performs heapify at the zeroth index*/

    return root;
}
void decreaseKey(struct HeapNode **a, int v, int dist)   /*changes the distance of the node and interchanges with the nodes above until it satisfies minhep condition*/
{
    int i = pos[v];
    a[i]->dist = dist;
    while (i && a[i]->dist < a[(i - 1) / 2]->dist)
    {
        pos[a[i]->v] = (i-1)/2;
        pos[a[(i-1)/2]->v] = i;
        swapHeapNode(&a[i],  &a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
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
    printf("%d ",dist[v]);
    print_path(v);
}
void dijkstra(struct Graph* graph, int src,int b)
{
    int n=graph->numVertices;
    if(pre!=NULL){
        free(pre);
    }
    if(dist!=NULL){
        free(dist);
    }
    if(pos!=NULL){
        free(pos);
    }
    pre=NULL;
    pos=NULL;
    dist=NULL;
    pre=(int *)malloc((n+1)*sizeof(int));
    dist=(int *)malloc(n*sizeof(int));
    pos=(int *)malloc(n*sizeof(int));
    int i;
    for(i=0;i<n;i++){
        pre[i]=-2;
    }
    pre[n]=src;
    pre[src]=-1;
    size=n;
    struct HeapNode** minHeap = create();      /* initiating minheap with the size of number of vertices in graph*/
    for (int v = 0; v < n; ++v)
    {
        dist[v] = INT_MAX;
        minHeap[v] = newHeapNode(v, dist[v]);  /*initially all heapnodes are at infinite distance*/
        pos[v] = v;
    }
    minHeap[src] = newHeapNode(src, dist[src]);
    pos[src]   = src;                           /*position of a heapnode is noted so that the position of a node can be found in the minheap array*/
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    while (size>0)
    {
        struct HeapNode* heapnode = extractMin(minHeap); /*returns the node at min distance*/
        int u = heapnode->v;
        if(b==1){
            if(dist[u]==INT_MAX) printf("%d -1\n",u+1);
            else
                printf("%d %d\n",u+1,dist[u]);            /*prints the node since its distance doesnt change after it is extracted from minheap*/
        }
        struct node* temp = graph->adjLists[u];
        while (temp!= NULL)
        {
            int v = temp->data;
            if (pos[v]<size && dist[u]!= INT_MAX && temp->weight + dist[u] < dist[v])  /*updating the distance*/
            {
                dist[v] = dist[u] + temp->weight;
                pre[v]=u;
                decreaseKey(minHeap, v, dist[v]);          /*updating the position in the min heap*/
            }
            temp=temp->next;
        }
    }
    minHeap=clear(minHeap,n);
    minHeap=NULL;
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
            free(dist);
            dist =NULL;
            delet(graph);
            graph=createGraph();
        }
        if(digit=='E'){
            addEdge(graph);            //adding edge
        }
        if(digit=='?'){
            present(graph);
        }
        if(digit=='D'){
            fgetc(stdin);
            scanf("%d",&x);
            fgetc(stdin);
            dijkstra(graph,x-1,1);
        }
        if(digit=='P'){
            fgetc(stdin);
            scanf("%d",&x);
            fgetc(stdin);
            scanf("%d",&y);
            fgetc(stdin);
            if(pre!=NULL&&pre[graph->numVertices]==x-1){ /*if predecessor array already stores the predecessors obtained by the dijkstra of the given number it doesnt perform djikstra again*/
                check(y-1);
                printf("\n");                              /* checks if the vertices are connected in any way*/
            }
            else{
                dijkstra(graph,x-1,0);                     /* performs djikstras and stores predecessors but doesnt print*/
                check(y-1);                                /* checks if shortest distance is not infinity*/
                printf("\n");
            }
        }
    }
    return(0);
}
