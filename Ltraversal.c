#ifndef LTRAVERSAL_C
#define LTRAVERSAL_C

#include <stdbool.h>
#include <stdlib.h>

#include "graph.h"
#include "node.h"
#include "def.h"

// forward declarations
void bfsRecursive(Graph *graph, Str20 key);
void dfsRecursive(Graph *graph, Node *node);
int vertexIndex(Graph *graph, Str20 key);
void resetVisited(Graph *graph);

void bfs(Graph *graph, Str20 startKey)
{
    int startIndex = vertexIndex(graph, startKey);
    struct Queue *q = createQueue(graph->numVertices + 1);
    if (startIndex == -1)
    {
        printf("Starting vertex not found.\n");
        return;
    }

    // Reset visited status for all nodes
    resetVisited(graph);

    // Perform BFS starting from the start vertex
    bfsRecursive(graph, graph->vertices[startIndex]->key, q);

    freeQueue(q);
}

void bfsRecursive(Graph *graph, Str20 key, struct Queue *q)
{
    int index = vertexIndex(graph, key);

    // Mark the vertex being checked as explored (if not yet explored)
    if (!(graph->vertices[index]->visited))
    {
        // Enqueue the vertex being checked right now
        enQueue(q, graph->vertices[index]->key);
        graph->vertices[index]->visited = true;
    }

    // Create an array of adjacent node indices for sorting
    int *adjIndices = (int *)malloc(graph->numVertices * sizeof(int));
    int count = 0;

    // Find all adjacent nodes
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (graph->edges[index][i])
        {
            adjIndices[count++] = i;
        }
    }

    // Sort the adjacent indices based on the alphabetical order of keys
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(graph->vertices[adjIndices[i]]->key, graph->vertices[adjIndices[j]]->key) > 0)
            {
                int temp = adjIndices[i];
                adjIndices[i] = adjIndices[j];
                adjIndices[j] = temp;
            }
        }
    }

    // Loop through the adjacent indices and enqueue the ones that aren't explored yet
    for (int i = 0; i < count - 1; i++)
    {
        if (!(graph->vertices[adjIndices[i]]->visited))
        {
            graph->vertices[adjIndices[i]]->visited = true;
            enQueue(q, graph->vertices[adjIndices[i]]->key);
        }
    }

    printf("%s ", key);
    deQueue(q);

    // If queue is not empty, perform bfs again with the head of the queue
    // Repeat until queue is empty (i.e. all vertice keys are printed)
    if (!queueEmpty(q))
        bfsRecursive(graph, head(q), q);
}

void dfs(Graph *graph, Str20 startKey)
{
    int startIndex = vertexIndex(graph, startKey);
    if (startIndex == -1)
    {
        printf("Starting vertex not found.\n");
        return;
    }

    // Reset visited status for all nodes
    resetVisited(graph);

    // Perform DFS starting from the start vertex
    dfsRecursive(graph, graph->vertices[startIndex]);
}

void dfsRecursive(Graph *graph, Node *node)
{
    // Print the key of the current node
    printf("%s ", node->key);

    // Mark the current node as visited
    node->visited = true;

    // Find index of the current node
    int index = vertexIndex(graph, node->key);

    // Create an array of adjacent node indices for sorting
    int *adjIndices = (int *)malloc(graph->numVertices * sizeof(int));
    int count = 0;

    // Find all adjacent nodes that haven't been visited
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (graph->edges[index][i] && !graph->vertices[i]->visited)
        {
            adjIndices[count++] = i;
        }
    }

    // Sort the adjacent indices based on the alphabetical order of keys
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(graph->vertices[adjIndices[i]]->key, graph->vertices[adjIndices[j]]->key) > 0)
            {
                int temp = adjIndices[i];
                adjIndices[i] = adjIndices[j];
                adjIndices[j] = temp;
            }
        }
    }

    // Recursively visit all adjacent nodes
    for (int i = 0; i < count; i++)
    {
        int adjIndex = adjIndices[i];
        if (!graph->vertices[adjIndex]->visited)
        {
            dfsRecursive(graph, graph->vertices[adjIndex]);
        }
    }

    // Free the array of adjacent indices
    free(adjIndices);
}

// Function to reset the visited status of all nodes in the graph
void resetVisited(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        graph->vertices[i]->visited = false;
    }
}

#endif // LTRAVERSAL_C