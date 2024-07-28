#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MALLOC_ERROR 3
#define INSUFFICIENT_DATA_ERROR 4
#define FILE_NOT_FOUND_ERROR 5
#define INVALID_VERTEX_ERROR 6

typedef char Str20[21];
typedef char Str100[101];
// name, _dfs/_bfs/_graph, .svg, null terminator
typedef char StrDraw[100 + 6 + 4 + 1];

#endif