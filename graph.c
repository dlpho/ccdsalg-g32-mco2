#ifndef GRAPH_C
#define GRAPH_C

#include "node.h"
#include "graph.h"

/*
    initializes and returns a graph
*/
Graph *createGraph(int num)
{
    int i;

    // allocate memory for graph
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = num;

    // allocate memory for node array and adjacency matrix
    graph->vertices = (Node **)calloc(num, sizeof(Node *));
    graph->edges = (bool **)calloc(num, sizeof(bool *));

    // if errors exist during memory allocation
    if (graph == NULL || graph->vertices == NULL || graph->edges == NULL)
    {
        exit(MALLOC_ERROR);
    }

    // init vertices as empty or all null
    for (i = 0; i < num; i++)
    {
        graph->vertices[i] = NULL;
    }

    // init edges as empty or all false
    for (i = 0; i < num; i++)
    {
        graph->edges[i] = (bool *)calloc(num, sizeof(bool));
    }

    return graph; // return graph
}

/*
    reads from given file and sets the graph data based on what
    is found in the file. returns the resulting graph
*/
Graph *createGraphFromFile(FILE *fp)
{
    int num;
    Str20 key, temp;
    int i = 0, j;
    Graph *graph;

    // scan number of vertices from the first line
    if (fscanf(fp, "%d", &num) != EOF)
    {

        // initialize graph
        graph = createGraph(num);

        // create list of adjacent vertices per vertex
        Str20 **adjacencies = (Str20 **)malloc(num * sizeof(Str20 *));
        for (i = 0; i < num; i++)
        {
            adjacencies[i] = (Str20 *)calloc(num, sizeof(Str20));
        }

        // if memory allocation for adjacencies fail
        if (adjacencies == NULL)
        {
            freeGraph(graph);
            exit(MALLOC_ERROR);
        }

        i = 0; // reset i for vertices indexing
        while (fscanf(fp, "%s", key) != EOF)
        {
            addVertex(graph, key);

            j = 0; // reset j for the adjacent vertices indexing
            while (fscanf(fp, "%s", temp) && strcmp(temp, "-1"))
            {
                strcpy(adjacencies[i][j], temp);
                j++; // move to the next adjacent key
            }

            i++; // move to the next vertex
        }

        // if provided lines of adajcency lists are insufficient
        if (num != i)
        {
            freeGraph(graph);
            exit(INSUFFICIENT_DATA_ERROR);
        }

        // add all edges of adjacent vertices into the adjacency matrix
        for (i = 0; i < num; i++)
        {
            for (j = 0; j < num && adjacencies[i][j][0] != '\0'; j++)
            {
                addEdge(graph, graph->vertices[i]->key, adjacencies[i][j]);
            }
        }

        // free adjacencies memory
        for (i = 0; i < num; i++)
        {
            free(adjacencies[i]);
        }
        free(adjacencies);
    }

    fclose(fp);   // close file
    return graph; // return graph
}

/*
    frees the memory allocated for all parts of the graph
*/
void freeGraph(Graph *graph)
{
    if (graph != NULL)
    {

        // free vertices and each adjacency row
        for (int i = 0; i < graph->numVertices; i++)
        {
            if (graph->vertices[i] != NULL)
            {
                freeNode(graph->vertices[i]);
            }
            free(graph->edges[i]);
        }

        free(graph->edges);
        free(graph->vertices);
        free(graph);
    }
}

/*
    turns key into a node vertex then adds it to the first null space
*/
void addVertex(Graph *graph, Str20 key)
{
    int i;

    for (i = 0; i < graph->numVertices; i++)
    {
        // add vertex to first found null
        if (graph->vertices[i] == NULL)
        {
            graph->vertices[i] = createNode(key);
            break; // stop loop once vertex is added
        }
    }
}

/*
    returns the degree (count of adjacent vertices) of a vertex
*/
int vertexDegree(Graph *graph, Node *vertex)
{
    int index = vertexIndex(graph, vertex->key);
    int degree = 0;

    if (index == -1)
        return -1; // vertex not found. unlikely but for good measure

    // count adjacent vertices
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (graph->edges[index][i])
        {
            degree++; // count degree if value of edge is 'true'
        }
    }
    return degree; // return count
}

/*
    returns the index of given key from graph
*/
int vertexIndex(Graph *graph, Str20 key)
{
    int i;

    // compare keys if same (case insensitive)
    for (i = 0; i < graph->numVertices; i++)
    {
        if (graph->vertices[i] != NULL)
        {
            if (sameKeys(graph->vertices[i]->key, key))
                return i; // return index if same
        }
    }

    return -1; // vertex not found. unlikely but for good measure
}

/*
    resets the visited flag of each vertex node for DFS
*/
void resetVisited(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        graph->vertices[i]->visited = false;
    }
}

/*
    sets the edge value in adjacency matrix to true given the from-key
    and the to-key from the graph
*/
void addEdge(Graph *graph, Str20 fromKey, Str20 toKey)
{
    int fromIndex = vertexIndex(graph, fromKey);
    int toIndex = vertexIndex(graph, toKey);

    // if both are valid indices
    if (fromIndex != -1 && toIndex != -1)
    {
        // set edge value in adjacency matrix to true
        // ensure that it is SYMMETRIC
        graph->edges[fromIndex][toIndex] = true;
        //        graph->edges[toIndex][fromIndex] = true;
    }
}

/*
    for testing purposes; prints the values in adjacency matrix
*/
void printEdges(Graph *graph)
{
    int i, j;

    for (i = 0; i < graph->numVertices; i++)
    {

        printf("%s\t", graph->vertices[i]->key);

        for (j = 0; j < graph->numVertices; j++)
        {
            printf("%d ", graph->edges[i][j]);
        }

        printf("\n");
    }
}

/*
    returns true if keys are equal (case insensitive), false otherwise.
*/
bool sameKeys(const Str20 key1, const Str20 key2)
{
    Str20 lower1, lower2;

    // convert to lowercase
    strLower(key1, lower1);
    strLower(key2, lower2);

    // return the boolean value of comparison
    return strcmp(lower1, lower2) == 0;
}

/*
    converts string to lowercase and stores in lower
*/
void strLower(const Str20 string, Str20 lower)
{
    int i;
    for (i = 0; string[i]; i++)
    {
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            lower[i] = string[i] + 32; // ascii
        }
        else
        {
            lower[i] = string[i]; // copy if not uppercase
        }
    }
    lower[i] = '\0'; // ensure the null at end
}

#endif // GRAPH_C