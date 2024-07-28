
#ifndef TRANVERSAL_C
#define TRANVERSAL_C

#include "traversal.h"
#include "queue.h"
#include "queue.c"

/* As per specification, only BFS is required for drawing */
// void traversalsToFile(Graph *graph, Str20 startKey, Graph *treeBfs, Graph *treeDfs)
void traversalsToFile(Graph *graph, Str20 startKey, Graph *treeBfs)
{
    FILE *fp;
    int i;

    // open file for write
    fp = fopen("TRAVERSALS.txt", "w");

    // print degrees of all vertices by order
    for (i = 0; i < graph->numVertices; i++)
    {
        Node *vertex = graph->vertices[i];
        fprintf(fp, "%s\t%d\n", graph->vertices[i]->key, vertexDegree(graph, vertex));
    }
    fprintf(fp, "\n");

    // print traversals from start key
    bfs(fp, graph, startKey, treeBfs);
    fprintf(fp, "\n");

    /* As per specification, only BFS is required for drawing */
    // dfs(fp, graph, startKey, treeDfs);
    dfs(fp, graph, startKey);
    fprintf(fp, "\n");

    // close file
    fclose(fp);
}

void bfs(FILE *fp, Graph *graph, Str20 startKey, Graph *tree)
{
    int startIndex = vertexIndex(graph, startKey);
    struct Queue *q = createQueue(graph->numVertices + 1); // no need for queuuFull because I intentiaonlly amde it slightly bigger jic
    addVertex(tree, startKey);

    // Reset visited status for all nodes
    resetVisited(graph);

    // Perform BFS starting from the start vertex
    bfsRecursive(fp, graph, graph->vertices[startIndex]->key, q, tree);

    freeQueue(q);
}

void bfsRecursive(FILE *fp, Graph *graph, Str20 key, struct Queue *q, Graph *tree)
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
    sortAlphabetically(graph, adjIndices, count);

    // Loop through the adjacent indices and enqueue the ones that aren't explored yet
    for (int i = 0; i < count; i++)
    {
        if (!(graph->vertices[adjIndices[i]]->visited))
        {
            addVertex(tree, graph->vertices[adjIndices[i]]->key);
            addEdge(tree, key, graph->vertices[adjIndices[i]]->key);
            graph->vertices[adjIndices[i]]->visited = true;
            enQueue(q, graph->vertices[adjIndices[i]]->key);
        }
    }

    fprintf(fp, "%s ", key);
    Str20 buffer;
    deQueue(q, buffer);

    // If queue is not empty, perform bfs again with the head of the queue
    // Repeat until queue is empty (i.e. all vertice keys are printed)
    if (!queueEmpty(q))
    {
        head(q, buffer);
        bfsRecursive(fp, graph, buffer, q, tree);
    }
}

/* As per specification, only BFS is required for drawing */
// void dfs(FILE *fp, Graph *graph, Str20 startKey, Graph *tree)
void dfs(FILE *fp, Graph *graph, Str20 startKey)
{
    // reset visited flags for vertices
    resetVisited(graph);

    // add root node
    // addVertex(tree, startKey);
    // start DFS from the specificed start key
    // dfsRecursive(fp, graph, vertexIndex(graph, startKey), tree);
    dfsRecursive(fp, graph, vertexIndex(graph, startKey));
    fprintf(fp, "\n");
}

/* As per specification, only BFS is required for drawing */
// void dfsRecursive(FILE *fp, Graph *graph, int startIndex, Graph *tree)
void dfsRecursive(FILE *fp, Graph *graph, int startIndex)
{
    int i, count = 0;
    int *adjIndices = (int *)malloc(graph->numVertices * sizeof(int));
    Node *vertex = graph->vertices[startIndex];

    // print the key of the current vertex
    fprintf(fp, "%s ", vertex->key);

    // mark the current vertex as visited
    vertex->visited = true;

    // find all adjacent nodes that haven't been visited
    for (i = 0; i < graph->numVertices; i++)
    {
        if (graph->edges[startIndex][i] && !graph->vertices[i]->visited)
        {
            adjIndices[count++] = i;
        }
    }

    // sort the adjacent indices alphabetically
    sortAlphabetically(graph, adjIndices, count);

    // recursively visit all adjacent nodes
    for (i = 0; i < count; i++)
    {
        if (!graph->vertices[adjIndices[i]]->visited)
        {
            /* As per specification, only BFS is required for drawing */
            // addVertex(tree, graph->vertices[adjIndices[i]]->key);
            // addEdge(tree, vertex->key, graph->vertices[adjIndices[i]]->key);
            // dfsRecursive(fp, graph, adjIndices[i], tree);
            dfsRecursive(fp, graph, adjIndices[i]);
        }
    }

    // free the array of adjacent indices
    free(adjIndices);
}

void sortAlphabetically(Graph *graph, int *adjIndices, int count)
{
    int i, j, temp;

    // sort the adjacent indices alphabetically using bubble sort
    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            // swap if vertex i should come after vertex j
            if (strcmp(graph->vertices[adjIndices[i]]->key, graph->vertices[adjIndices[j]]->key) > 0)
            {
                temp = adjIndices[i];
                adjIndices[i] = adjIndices[j];
                adjIndices[j] = temp;
            }
        }
    }
}

#endif // TRANVERSAL_C
