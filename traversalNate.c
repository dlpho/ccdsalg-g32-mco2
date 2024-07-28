#define MAIN

#include "traversalNate.h"

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
        fprintf(fp, "%s\t%d\n", graph->vertices[i]->key, vertexDegree(graph, vertex));
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

    Str20 verticesAtLevel[graph->numVertices];

    // start BFS from given start key
    bfsRecursive(fp, graph, vertexIndex(graph, startKey), vertexIndex(graph, startKey), tree, 1, verticesAtLevel);
    fprintf(fp, "\n");
}

void bfsRecursive(FILE *fp, Graph *graph, int currentIndex, int originalIndex, Graph *tree, int verticesAtLevelCount, Str20 verticesAtLevel[])
{
    bool allVisited;
    int i, j, count, temp;
    int *adjIndices = (int *)malloc(graph->numVertices * sizeof(int));

    printf("Index: %s (%d)\n", graph->vertices[currentIndex]->key, currentIndex);

    // print and mark the start vertex as visited if not already visited
    if (!graph->vertices[currentIndex]->visited)
    {
        printf("Currently visiting: %s\n", graph->vertices[currentIndex]->key);
        addVertex(tree, graph->vertices[currentIndex]->key);
        fprintf(fp, "%s ", graph->vertices[currentIndex]->key);
        graph->vertices[currentIndex]->visited = true;
    }

    // find all adjacent nodes and count
    count = 0;
    for (i = 0; i < graph->numVertices; i++)
    {
        if (graph->edges[currentIndex][i])
        {
            printf("Currently adding as edge: %s\n", graph->vertices[i]->key);
            adjIndices[count++] = i;
        }
    }

    printf("Adjacent Edge Count: %d\n", count);
    // printf("Checking if all visited...\n");

    // check if all adjacent nodes are visited
    /*  allVisited = true;
     for (i = 0; i < count; i++)
     {
         if (!graph->vertices[adjIndices[i]]->visited)
         {
              printf("key %s: unvisited.\n", graph->vertices[adjIndices[i]]->key);
              allVisited = false;
             printf("NOT ALL VISITED!\n");
             break;
         }
     } */

    // if all adjacent nodes are visited, return
    /* if (allVisited)
    {
        printf("ALL VISITED!\n");
        free(adjIndices);
        return true;
    } */

    // sort the adjacent indices alphabetically
    sortAlphabetically(graph, adjIndices, count);

    // print all unvisited adjacent nodes first
    for (i = 0; i < count; i++)
    {
        printf("Further exploring: %s\n", graph->vertices[adjIndices[i]]->key);

        // If the edge is not visited, add it to the graph
        if (!graph->vertices[adjIndices[i]]->visited)
        {
            addVertex(tree, graph->vertices[adjIndices[i]]->key);                                   // graph.c
            addEdge(tree, graph->vertices[currentIndex]->key, graph->vertices[adjIndices[i]]->key); // graph.c
            fprintf(fp, "%s ", graph->vertices[adjIndices[i]]->key);
            printf("\n|----------|\n");
            printf("   %s\n", graph->vertices[adjIndices[i]]->key);
            printf("|----------|\n\n");
            graph->vertices[adjIndices[i]]->visited = true;
        }
    }

    // then recursively visit each unvisited adjacent node

    /* if (moveOn)
    {
        edgesAtCurrentDepth = adjIndices;

        for (i = 0; i < count; i++)
        {
            printf("Count: %d\n", i);
            bfsRecursive(fp, graph, edgesAtCurrentDepth[i], tree);
        }
    } */

    if (currentIndex + 1 == verticesAtLevelCount)
    {
        printf("Original index %d finished!!!!!\n", originalIndex);
        // Add everything to verticesAtLevel array to keep track of the new level we are at
        printf("Creating new verticesAtLevel...\n");

        free(adjIndices);
        adjIndices = (int *)malloc(graph->numVertices * sizeof(int));

        // find all adjacent nodes and count
        count = 0;
        for (i = 0; i < graph->numVertices; i++)
        {
            if (graph->edges[adjIndices[0]][i])
            {
                printf("Edge found!\n");
                // printf("Currently adding as edge: %s\n", graph->vertices[i]->key);
                adjIndices[count++] = i;
            }
        }

        sortAlphabetically(graph, adjIndices, count);
        printf("New Original Index: %s\n", graph->vertices[adjIndices[0]]->key);
        printf("Adjacent Edge Count: %d\n", count);

        for (i = 0; i < count; i++)
        {
            printf("index %d: %s\n", i, graph->vertices[originalIndex]->key);
            strcpy(verticesAtLevel[i], graph->vertices[adjIndices[i]]->key); // atp adjIndices should have reset right please god
        }

        printVisitedMatrix(graph);
        bfsRecursive(fp, graph, adjIndices[0], adjIndices[0], tree, count, verticesAtLevel);

        // then recursively visit each unvisited adjacent node
        /* for (i = 0; i < count; i++)
        {
            printf("Count: %d\n", i);
            bfsRecursive(fp, graph, adjIndices[i], tree, false, verticesAtLevel);
        } */

        // return true;
    }
    else
    {
        printf("Level unfinished...\n");
        printVisitedMatrix(graph);
        bfsRecursive(fp, graph, vertexIndex(graph, verticesAtLevel[currentIndex + 1]), originalIndex, tree, verticesAtLevelCount, verticesAtLevel);
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

void printVisitedMatrix(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%s: ", graph->vertices[i]->key);

        if (graph->vertices[i]->visited)
            printf("visited\n");
        else
            printf("unvisited\n");
    }
}

#endif // TRANVERSAL_C
