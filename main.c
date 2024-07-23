#include "def.h"
#include "node.c"
#include "graph.c"
#include "traversal.c"

int main()
{
    Str100 filename;
    Str20 startVertex;
	
	// ask input
    printf("Input filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("%s not found.\n", filename);
        exit(FILE_NOT_FOUND_ERROR);
    }

    Graph *graph = createGraphFromFile(file);

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