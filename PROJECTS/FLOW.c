//c program to find maximum flow by ford fulkerson-BFS(or Edmond-Karp) method
#include <stdio.h>
#define MAX 50

int bfs(int G[MAX][MAX], int s, int t, int n, int parent[MAX])//O(v^2)
{
	int visited[MAX];
	int Bfs[MAX],v;
	int front=-1,rear=-1;
	
	for(v=1;v<=n;v++)
	{
  		visited[v]=0;
 	}
 	rear++;
	Bfs[rear]=s;
	visited[s]=1;
	parent[s]=-1;
	
    while (front!=rear)
    {
    	front++;
        int u =Bfs[front];

        for(v=1; v<=n; v++)
        {
            if (visited[v]==0 && G[u][v] > 0)
            {
            	rear++;
                Bfs[rear]=v;
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }

    return (visited[t] == 1);
}

int fordFulkerson(int G[MAX][MAX], int s, int t, int n)//O(vE^2)
{
    int u, v;
    int parent[MAX];
	     
    int max_flow = 0;
    while (bfs(G, s, t, n, parent))
    {
     
        int path_flow =9999;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            if(G[u][v]<path_flow)
            {
            	path_flow = G[u][v];	
			}
        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            G[u][v] -= path_flow;
            G[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main()
{
 	int i,j;
 	int G[MAX][MAX];
 	int FLOW;
 	int n, s, t;
 	
    printf("TOTAL VERTICES: ");
    scanf("%d",&n);
    printf("ADJANCENCY MATRIX: \n");
    for(i=1;i<=n;i++)
	{
     	for(j=1;j<=n;j++)
		{
      		scanf("%d",&G[i][j]);
     	}
    }
    
    printf("S: ");
    scanf("%d",&s);
    printf("T: ");
    scanf("%d",&t);
    
    FLOW = fordFulkerson(G, s, t, n);
    
    printf("MAX FLOW : %d",FLOW);

    return 0;
}

/*
0 7 10 0 0 0 0 
0 0 1 3 5 0 0 
0 0 0 2 0 7 0
0 0 0 0 3 2 0
0 0 0 0 0 2 10
0 0 0 0 0 0 4
0 0 0 0 0 0 0  
*/
