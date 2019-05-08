#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// # of vertices in graph
#define V 9

int minDistance(int dist[],
                bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false &&
            dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

//print shortest path from source to j
void printPath(int parent[], int j)
{

    if (parent[j] == - 1)
        return;

    printPath(parent, parent[j]);

    printf("%d ", j);
}

// print distance array
int printSolution(int dist[], int n,
                  int parent[])
{
    int src = 0;
    printf("Vertex\t Distance\tPath");
    for (int i = 1; i < V; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ",
               src, i, dist[i], src);
        printPath(parent, i);
    }
}

/* implements Dijkstra's algorithm - single
 * source shortest path algorithm
 * for a graph represented using adjacency matrix */

void dijkstra(int graph[V][V], int src)
{

    // output array dist[i]
    int dist[V];

    //sptSet[i] is true if vertex i is included in shortest path tree
    bool sptSet[V];

    // shortest path tree
    int parent[V];

    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // distance of source vertex
    dist[src] = 0;

    //find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet);

        // select the vertex
        sptSet[u] = true;

        //Update dist value of the adjacent vertices of the vertex
        for (int v = 0; v < V; v++)

            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    //print constructed distance array
    printSolution(dist, V, parent);
}

/*returns all shortest paths from 0->N
 *last one is full-length shortest path from 0->8*/

int main()
{
    //eight vertex graph
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 0, 10, 0, 2, 0, 0},
                       {0, 0, 0, 14, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    dijkstra(graph, 0);
    return 0;
}