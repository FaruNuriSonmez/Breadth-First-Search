#include<stdio.h>
#define  SIZE 40


struct queue
{
    int items[SIZE];
    int front;
    int rear;

};

struct queue* createQueue()
{
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
};

int isEmpty(struct queue*q)
{
    if(q->rear==-1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue *q , int value)
{
    if(q->rear == SIZE-1)
        printf("\n Queue is Full");
    else
    {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }

}

int dequeue(struct queue *q)
{
    int item;

    if(isEmpty(q))
    {
        printf("Queue is Empty");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;

        if(q->front > q->rear)
        {
            //printf("\nResetting Queue\n");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q)
{
    int i;
    if(isEmpty(q))
    {
        printf("Queue is Empty");
    }
    else
    {
        printf("\nQueue is : ");
        for (i=q->front; i<q->rear+1;i++)
        {
            printf("%d " , q->items[i]);
        }
    }
}


struct node
{
    int vertex;
    struct node* next;
};


struct Graph
{
    int vertex;
    struct node** adjlist;
    int* visited;
};


struct node * createNode(int v)
{
    struct node* newnode = malloc(sizeof(struct node));
    newnode->vertex = v;
    newnode->next = NULL;
    return newnode;
};

struct Graph * createGraph(int vertex)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->vertex = vertex;
    graph->adjlist = malloc(vertex * sizeof(struct node*));
    graph->visited = malloc(vertex *sizeof(int));

    int i;

    for(i=0;i<vertex;i++)
    {
        graph->adjlist[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
};


void addEdge(struct Graph* graph , int src , int dest)
{
    struct node* newnode = createNode(dest);
    newnode->next = graph->adjlist[src];
    graph->adjlist[src] = newnode;

    newnode = createNode(src);
    newnode->next = graph->adjlist[dest];
    graph->adjlist[dest] = newnode;
}

void bfs(struct Graph* graph , int startvertex)
{
    struct queue *q = createQueue();
    graph->visited[startvertex] = 1;

    enqueue(q , startvertex);


    while(!isEmpty(q))
    {
        //printQueue(q);

        int current = dequeue(q);
        printf("Visited %d\n" , current);

        struct node* temp = graph->adjlist[current];

        while(temp)
        {
            int adjvertex = temp->vertex;

            if(graph->visited[adjvertex]==0)
            {
                graph->visited[adjvertex] = 1;
                enqueue(q , adjvertex);
            }
            temp = temp->next;
        }
    }
}



int main()
{

    struct Graph * graph = createGraph(6);

    addEdge(graph , 0,1);
    addEdge(graph , 0,2);
    addEdge(graph , 1,2);
    addEdge(graph , 1,4);
    addEdge(graph , 1,3);
    addEdge(graph , 2,4);
    addEdge(graph , 3,4);


    bfs(graph , 0);

    return 0;


}








