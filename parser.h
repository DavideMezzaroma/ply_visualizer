#ifndef PLY_PARSER
#define PLY_PARSER
#include "raylib.h"
#include "../utilities/dynarr.h"

void parse(const char* file, DArray* points, DArray* edges);

#endif
