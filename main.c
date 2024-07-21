#include <stdio.h>
#include "graph.h"
#include "graph.c"

#define FILE_NOT_FOUND_ERROR 5
#define INVALID_VERTEX_ERROR 6

int main()
{
    char filename[100];
    Str20 startVertex;

    printf("Input filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("%s not found.\n", filename);
        exit(FILE_NOT_FOUND_ERROR);
    }

    Graph *graph = createGraphFromFile(filename);

    printf("Input start vertex for the transversal: ");
    scanf("%s", startVertex);

    if (vertexIndex(graph, startVertex) == -1)
    {
        printf("Vertex %s not found.\n", startVertex);
        exit(INVALID_VERTEX_ERROR);
    }

    // TODO: add transversal codes

    return 0;
}