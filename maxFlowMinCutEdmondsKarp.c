#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647
#include <stdbool.h>

int N;

void build_residual_network();
int find_path_bfs();
int edmonds_karp();
void dfs();

int main(){
    printf("Edmonds Karp implementation to find min cut and max flow\n");
    printf("\nEnter number of nodes in the graph:\n");
    scanf("%d",&N);

    int map[N][N],src,tar;
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j< N; j++){
            map[i][j] = 0;
        }
    }

     while(1){
        int node1,node2,ch,c;
        printf("Select an option\n");
        printf("1 = Enter the edges:\n");
        printf("2 = Find max flow and min cut\n");
        printf("3 = exit\n");
        scanf("%d",&ch);

        switch(ch){

            case 1:{
                printf("Enter first node\n");
                scanf("%d",&node1);
                printf("Enter second node\n");
                scanf("%d",&node2);
                printf("Enter capacity of the edge\n");
                scanf("%d",&c);
                map[node1][node2] = c;
                break;
                }
           case 2:
                printf("the max flow is ");
                edmonds_karp(node1, node2, map);
                break;
            case 3:
                exit(1);
                break;
            default:
                printf("Wrong Choice..Try again");
                break;
        }
    }
    printf("\nEnter the source node:\n");
    scanf("%d",&src);
    printf("\nEnter the target node:\n");
    scanf("%d",&tar);
    printf("the max flow is:");
    //use edmonds karps algorithm to print max flow
    edmonds_karp(src, tar, map);
    return 0;
}

//depth first search all the visited nodes from the source for min cut
void dfs(int map[N][N], int src, int visit[N]){
    visit[src] = 1;
    for (int i = 0; i<N ; i++)

        if(map[src][i]!=0 && visit[i]!=0)
            dfs(map, i, visit);

}

int edmonds_karp(int src, int tar, int map[N][N]){ // the starting point of the whole picture is src and the end point is tar
    int max_flow = 0;
    int new_flow = 0;
    // go on and find the path and find until the return value is zero
    do{
        new_flow = find_path_bfs(src, tar, map);
        max_flow += new_flow;
    }while ( new_flow != 0 );

    printf("%d\n",max_flow);
    printf("The min cut of the graph is:\n");
    int visit[N];
    memset(visit, 0, sizeof(visit));  // return to zero with memset

    dfs(map, src, visit);

    for(int i = 0; i<N; i++)
        for(int j = 0; j <N; j++)
            if(visit[i]==1 && visit[j]!=1 && map[i][j]!=0)
                printf("%d - %d\n",i,j);
    return 0;

}

// find the way, the return value is the size found this time, the starting point number src, the end point is tar
int find_path_bfs(int src, int tar, int map[N][N]){
    int queue[N];             // used to run bfs
    int qTail;                // The number of elements in current = queue
    int last[N];              // the last point in the bfs record
    int min[N];
    int visited[N];           // running the bfs record, those points were ran over
    memset(visited, 0, sizeof(visited));  // return to zero with memset src itself must be initialized before BFS
    min[src] = INF;
    last[src] = -1;
    visited[src] = 1;
    // put source in the queue
    queue[0] = src;
    qTail = 1;
    int qHead, i;
    for ( qHead = 0 ; qHead < qTail ; qHead++ ){
        if ( queue[qHead] == tar ) break;              // found it
        int cur = queue[qHead];                        // the number of point currently being processed
        for ( i = 0 ; i < N ; i++ ){
            if ( visited[i] == 0 && map[cur][i] != 0 ){
                queue[qTail++] = i;
                min[i] = (min[cur] < map[cur][i]) ? min[cur] : map[cur][i];
                last[i] = cur;
                visited[i] = 1;
            }
        }
    }
    // no way qHead==qTail return 0
    if ( qHead == qTail ) return 0;
    int flow = min[tar];              // the amount of flow of this stream
    int cur = tar;
    while ( last[cur] != -1 ){
        map[ last[cur] ][ cur ] -= flow;  // positive side reduction
        map[ cur ][ last[cur] ] += flow;  // increase in reverse side
        cur = last[cur];
    }
    return min[tar];
}











