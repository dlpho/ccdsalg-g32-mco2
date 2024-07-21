#include"graph.h"

Graph *createGraph(int num) {
    int i;

    // allocate memory for graph
	Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->numVertices = num;
	
    // allocate memory for node array and adjacency matrix
    graph->vertices = (Node **) malloc(num * sizeof(Node));
    graph->edges = (bool **) malloc(num * sizeof(bool*));
	
	// init vertices as empty or all null
	for (i = 0; i < num; i++) {
        graph->vertices[i] = NULL;
	}
	
    // init edges as empty or all false 
    for (i = 0; i < num; i++) {
        graph->edges[i] = (bool*) calloc(num, sizeof(bool));
    }
	
    return graph; // return graph
}

Graph *createGraphFromFile(FILE *fp) {
    int num;
    Str20 key, temp;
    int i = 0, j;
    Graph *graph;

    // Scan number of vertices from the first line
    if (fscanf(fp, "%d", &num) != EOF) {
            
        // initialize graph
        graph = createGraph(num);

        // create list of adjacent vertices per vertex
        Str20 **adjacencies = (Str20 **)malloc(num * sizeof(Str20 *));
        for (i = 0; i < num; i++) {
            adjacencies[i] = (Str20 *)calloc(num, sizeof(Str20));
        }
		
        i = 0; // reset i for vertices indexing
        while (fscanf(fp, "%s", key) != EOF) {
            addVertex(graph, key);
//            printf("%s's adjacence: ", graph->vertices[i]->key);

            j = 0; // reset j for the adjacent vertices indexing
            while (fscanf(fp, "%s", temp) && strcmp(temp, "-1")) {
                strcpy(adjacencies[i][j], temp);
//                printf("%s ", adjacencies[i][j]);
                j++; // move to the next adjacent key
            }

//            printf("\n");
            i++; // move to the next vertex
        }
//	
        // add all edges of adjacent vertices into the adjacency matrix
        for (i = 0; i < num; i++) {
            for (j = 0; j < num && adjacencies[i][j][0] != '\0'; j++) {
                addEdge(graph, graph->vertices[i]->key, adjacencies[i][j]);
            }
        }

        // free adjacencies memory
        for (i = 0; i < num; i++) {
            free(adjacencies[i]);
        }
        free(adjacencies);
    }

    return graph;
}



void addVertex(Graph *graph, Str20 key) {
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        // add vertex to first found null 
        if (graph->vertices[i] == NULL) {
            graph->vertices[i] = createNode(key);
            break; // stop loop once vertex is added
        }
    }
}

void addEdge(Graph *graph, Str20 fromKey, Str20 toKey) {
    int fromIndex = vertexIndex(graph, fromKey);
    int toIndex = vertexIndex(graph, toKey);

    // if both are valid indices
    if (fromIndex != -1 && toIndex != -1) {
        // set edge values in adjacency matrix to true
        graph->edges[fromIndex][toIndex] = true;
        graph->edges[toIndex][fromIndex] = true;
    }
}

void printGraph(Graph *graph);

void freeGraph(Graph *graph) {
    if (graph != NULL) {

        // free vertices and each adjacency row
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->vertices[i] != NULL) {
                freeNode(graph->vertices[i]);
            }
            free(graph->edges[i]);
        }

        free(graph->edges); 
        free(graph->vertices); 
        free(graph); 
    }
}

int vertexDegree(Graph *graph, Node *vertex) {
    int index = vertexIndex(graph, vertex->key);
    int degree = 0;

    if (index == -1) 
        return -1;  // vertex not found. unlikely but for good measure

    // count adjacent vertices
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->edges[index][i]) {
            degree++; // count degree if value of edge is 'true'
        }
    }
    return degree; // return count
}


int vertexIndex(Graph *graph, Str20 key) {
    int i;
	
	// compare keys if same (case insensitive)
    for (i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i] != NULL) {
			if (sameKeys(graph->vertices[i]->key, key)) 
            	return i; // return index if same 
		}
    }

    return -1; // vertex not found. unlikely but for good measure
}

/*
    returns string converted to lowercase
*/
bool sameKeys(const Str20 key1, const Str20 key2) {
    Str20 lower1, lower2;
    
    strLower(key1, lower1);
    strLower(key2, lower2);
    
    return strcmp(lower1, lower2) == 0;
}

void strLower(const Str20 string, Str20 lower) {
    int i;
    for (i = 0; string[i]; i++) {
        lower[i] = tolower(string[i]);
    }
    lower[i] = '\0';  // Null-terminate the string
}