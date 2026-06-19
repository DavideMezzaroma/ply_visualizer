#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "../dynamic_array/dynarr.h"

void parse(const char* file, DArray* points, DArray* edges){

	FILE *fd = fopen(file, "r");
	if(fd == NULL){
		printf("Could not open file %s. Aborting\n", file);
		exit(-1);
	}

	char line[64];
	int num_verteces;
	int num_faces;

	while(fgets(line, sizeof(line), fd)){
		if(sscanf(line, "element vertex %d", &num_verteces) == 1){
			//printf("vertex: %d", num_verteces);
		}
		else if(sscanf(line, "element face %d", &num_faces) == 1){
			//printf("face: %d", num_faces);
		}
		else if(!strncmp(line, "end_header", 10)){
			break;
		}
	}

	for(int i = 0; i < num_verteces; i++){
		Vector3 point = {0.0f, 0.0f, 0.0f};
		fgets(line, sizeof(line), fd);
		sscanf(line, " %f %f %f", &point.x, &point.z, &point.y);
		da_add(points, &point);
	}

	for(int i = 0; i < num_faces; i++){
		int count;
		fscanf(fd, " %d", &count);

		int indeces[count];
		for(int j = 0; j < count; j++){
			fscanf(fd, " %d", &indeces[j]);
		}

		for(int j = 0; j < count; j++){
			Vector2 edge;
			edge.x = (float)indeces[j];
			edge.y = (float)indeces[(j+1)%count];
			da_add(edges, &edge);
		}
	}

	return;
}
