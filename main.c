#include <string.h>
#include "def.h"
#include "node.c"
#include "graph.c"
#include "traversal.c"
#include "drawer.c"

int main()
{
    Str100 filename;
    Str20 startKey;
    FILE *file;

    // ask for graph file name
    printf("Input filename: ");
    scanf("%s", filename);
    // strcpy(filename, "SAMPLE2_GRAPH.txt"); // FOR TESTING / Swap string with whatever file

    // exit if file does not exist
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("%s not found.\n", filename);
        exit(FILE_NOT_FOUND_ERROR);
    }

    // create graph from content in file
    Graph *graph = createGraphFromFile(file);
    fclose(file);

    // ask for starting vertex
    printf("Input start vertex for the traversal: ");
    scanf("%s", startKey);
    // strcpy(startKey, "Noah"); // FOR TESTING / Swap string with whatever node

    // exit if vertex does not exist in graph
    if (vertexIndex(graph, startKey) == -1)
    {
        printf("Vertex %s not found.\n", startKey);
        exit(INVALID_VERTEX_ERROR);
    }

    // proceed to print traversals to file
    Graph *treeBfs = createGraph(graph->numVertices);
    /* As per specification, only BFS is required for drawing */
    // Graph *treeDfs = createGraph(graph->numVertices);
    // traversalsToFile(graph, startKey, treeBfs, treeDfs);
    traversalsToFile(graph, startKey, treeBfs);

    // cut off last 4 characters of filename
    filename[strlen(filename) - 4] = '\0';
    // Filename, _dfs/_bfs/_tree, .svg, null
    StrDraw buffer;

    // draw graph and tree
    sprintf(buffer, "%s_graph.svg", filename);
    drawGraph(graph, buffer);
    sprintf(buffer, "%s_bfs.svg", filename);
    drawTree(treeBfs, buffer);
    /* As per specification, only BFS is required for drawing */
    // sprintf(buffer, "%s_dfs.svg", filename);
    // drawTree(treeDfs, buffer);

    freeGraph(graph);

    return 0;
}