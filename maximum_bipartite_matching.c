// C program to find the maximum bipartite in a network graph using ford fulkerson algorithm

#include <stdio.h>
#include <stdlib.h>


int no_of_nodes;
int target, source;
int **cap, *augpath;
int Q[100];
int front=-1, rear=-1;
int **rGraph,*visited,**aGraph;

void enqueue(int node);		//enqueue
void dequeue();						//dequeue
int isQEmpty();
int breadth_first_search();						//breadth first search for the graph
int edmund_karp();

int main()
{
	int i,j,first,second;
	printf("Enter the total number of nodes in bipartite graph : ");
	scanf("%d",&no_of_nodes);
	printf("Enter the number of nodes in set 1 : ");
	scanf("%d",&first);
	printf("Enter the number of nodes in set2 : ");
	scanf("%d",&second);
	no_of_nodes+=2;
	cap=(int **)malloc((no_of_nodes)*sizeof(int *)); //capacity matrix for the edge capacities
	for(i=0;i<no_of_nodes;i++)
	{
		cap[i]=(int *)malloc((no_of_nodes)*sizeof(int));
	}
	for(i=0;i<no_of_nodes;i++)
	{
		for(j=0;j<no_of_nodes;j++)
		{
			cap[i][j]=0;
		}
	}
	printf("\nEnter the capacities\n : ");
	for(i=1;i<=first;i++)
	{
		printf("\nEnter the edges from %d \n: ",i);
		for(j=first+1;j<=first+second;j++)
		{
            printf("[Enter 0 or 1] Does edge exist between %d and %d : ",i,j);
			scanf("%d",&cap[i][j]);
		}
	}
	for(i=1;i<=first;i++)
	{
		cap[0][i]=1;
	}
	for(i=first+1;i<=first+second;i++)
	{
		cap[i][first+second+1]=1;
	}

	source=0;
	target=no_of_nodes-1;
    printf("\nThe maximum bipartite matching in the graph : %d ",edmund_karp());
    return 0;
}

//find augmentation path from source to target
int breadth_first_search()
{
    int i,j,x,y;
    visited=(int *)malloc(no_of_nodes*sizeof(int));
    for(i=0;i<no_of_nodes;i++)
    {
    	visited[i]=0;
	}

    enqueue(source); 	//inserting source in the queue
    visited[source] = 1; //marking it as visited
    augpath[source] = -1;	//adding it to the augmented path

    while (!isQEmpty())
    {
        x = Q[front];
        dequeue();

        for (y=0; y<no_of_nodes; y++)
        {
            if (visited[y]==0 && rGraph[x][y] > 0)
            {
            	enqueue(y);
                augpath[y] = x;
                visited[y] = 1;
            }
        }
    }


    return (visited[target] == 1);
}

void enqueue(int node)
{
    if(rear == 100-1)
        printf("\nQueue Overflow\n");
    else
    {
        if(front == -1)
            front = 0;
        rear = rear+1;
        Q[rear] = node;
    }
}

int isQEmpty()
{
    if(front == -1 || front > rear)
        return 1;
    else
        return 0;
}

void dequeue()
{
    int tmp;
    if(front == -1 || front > rear)
    {
        printf("Queue Underflow\n");
        exit(1);
    }

    tmp = Q[front];
    front = front+1;
}

// Returns the maximum flow from s to t in the given graph
int edmund_karp()
{
    int x, y,i,j, max_flow=0,temp_flow;
    rGraph=(int **)malloc(no_of_nodes*sizeof(int *));
    for(i=0;i<no_of_nodes;i++)
	{
		rGraph[i]=(int *)malloc(no_of_nodes*sizeof(int));
	}
    for (x = 0; x < no_of_nodes; x++)
    {
    	for (y = 0; y < no_of_nodes; y++)
        {
             rGraph[x][y] = cap[x][y];
        }
    }
    augpath=(int *)malloc(no_of_nodes*sizeof(int));
    // Augment the flow while tere is path from source to target
    while (breadth_first_search())
    {
        temp_flow = 9999;
        for (y=target; y!=source;)
        {
            x = augpath[y];
            if(temp_flow<rGraph[x][y])
            	temp_flow = temp_flow;
            else
            	temp_flow=rGraph[x][y];
            y=augpath[y];
        }


        // update residual capacities of the edges and reverse edges along the path
        for (y=target; y != source;)
        {
            x = augpath[y];
            rGraph[x][y] -= temp_flow;
            rGraph[y][x] += temp_flow;
            y=augpath[y];
        }

        // Add path flow to overall flow
        max_flow += temp_flow;
    }

    return max_flow;
}




