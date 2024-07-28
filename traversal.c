#include "traversal.h"

#ifndef TRANVERSAL_C
#define TRANVERSAL_C

void traversalsToFile(Graph *graph, Str20 startKey, Graph *tree)
{
    FILE *fp;
    int i;

    // open file for write
    fp = fopen("TRAVERSALS.txt", "w");

    // print degrees of all vertices by order
    for (i = 0; i < graph->numVertices; i++)
    {
        Node *vertex = graph->vertices[i];
        fprintf(fp, "%s\t%d\n", graph->vertices[i], vertexDegree(graph, vertex));
    }
    fprintf(fp, "\n");

    // print traversals from start key
    bfs(fp, graph, startKey, tree);
    fprintf(fp, "\n");
    dfs(fp, graph, startKey);
    fprintf(fp, "\n");

    // close file
    fclose(fp);
}

// as per specification, BFS is only required for drawing
void bfs(FILE *fp, Graph *graph, Str20 startKey, Graph *tree)
{
    // reset visited flags for verticed in graph
    resetVisited(graph);

    // start BFS from given start key
    bfsRecursive(fp, graph, vertexIndex(graph, startKey), tree);
    fprintf(fp, "\n");
}

void bfsRecursive(FILE *fp, Graph *graph, int startIndex, Graph *tree)
{
    bool allVisited;
    int i, j, count, temp;
    int *adjIndices = (int *)malloc(graph->numVertices * sizeof(int));

    // print and mark the start vertex as visited if not already visited
    if (!graph->vertices[startIndex]->visited)
    {
        addVertex(tree, graph->vertices[startIndex]->key);
        fprintf(fp, "%s ", graph->vertices[startIndex]->key);
        graph->vertices[startIndex]->visited = true;
    }

    // find all adjacent nodes and count
    count = 0;
    for (i = 0; i < graph->numVertices; i++)
    {
        if (graph->edges[startIndex][i])
        {
            adjIndices[count++] = i;
        }
    }

    // check if all adjacent nodes are visited
    allVisited = true;
    for (i = 0; i < count; i++)
    {
        if (!graph->vertices[adjIndices[i]]->visited)
        {
            allVisited = false;
            break;
        }
    }

    // if all adjacent nodes are visited, return
    if (allVisited)
    {
        free(adjIndices);
        return;
    }

    // sort the adjacent indices alphabetically
    sortAlphabetically(graph, adjIndices, count);

    // print all unvisited adjacent nodes first
    for (i = 0; i < count; i++)
    {
        if (!graph->vertices[adjIndices[i]]->visited)
        {
            addVertex(tree, graph->vertices[adjIndices[i]]->key);
            addEdge(tree, graph->vertices[startIndex]->key, graph->vertices[adjIndices[i]]->key);
            fprintf(fp, "%s ", graph->vertices[adjIndices[i]]->key);
            graph->vertices[adjIndices[i]]->visited = true;
        }
    }

    // then recursively visit each unvisited adjacent node
    for (i = 0; i < count; i++)
    {
        bfsRecursive(fp, graph, adjIndices[i], tree);
    }

    // free the array of adjacent indices
    free(adjIndices);
}

void dfs(FILE *fp, Graph *graph, Str20 startKey)
{
    // reset visited flags for vertices
    resetVisited(graph);

    // start DFS from the specificed start key
    dfsRecursive(fp, graph, vertexIndex(graph, startKey));
    fprintf(fp, "\n");
}

void dfsRecursive(FILE *fp, Graph *graph, int startIndex)
{
    int i, j, temp, count = 0;
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