#ifndef PLY_PARSER
#define PLY_PARSER
#include "raylib.h"
#include "../dynamic_array/dynarr.h"

void parse(const char* file, DArray* points, DArray* edges);

#endif
