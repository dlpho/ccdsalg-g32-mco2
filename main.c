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
    printf("Input start vertex for the transversal: ");
    scanf("%s", startKey);

    // exit if vertex does not exist in graph
    if (vertexIndex(graph, startKey) == -1)
    {
        printf("Vertex %s not found.\n", startKey);
        exit(INVALID_VERTEX_ERROR);
    }

    // FOR TESTING; print adjacency matrix
    // printEdges(graph);

    // proceed to print traversals to file
    Graph *tree = traversalsToFile(graph, startKey);

    // cut off last 4 characters of filename
    filename[strlen(filename) - 4] = '\0';

    // draw graph and tree
    drawGraph(graph, filename);
    drawTree(tree, filename);

    return 0;
}