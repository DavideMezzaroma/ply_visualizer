#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./parser.h"
#include "../utilities/dynarr.h"

#define WIN_W 900
#define WIN_H 900
#define TARGET_FPS 60

const float BASE_Z_OFFSET = 3.0f;
const float ROTATION_SPEED = 0.03f;

float angle = 0.0f;
Vector3 object_speed = {0.0f, 0.0f, 0.0f};
Vector3 object_pos = {0.0f, 0.0f, 0.0f};

typedef enum {X, Y, Z} Axis ;

//----------------------------------------------------------------------------------------------------------------
Vector3 normalize_and_project(Vector3 point) {
    float final_z = point.z + BASE_Z_OFFSET;

    float norm_x = (point.x/final_z + 1) / 2 * WIN_W;
    float norm_y = -1 * (point.y/final_z - 1) / 2 * WIN_H;

    Vector3 new_point = {
      norm_x,
      norm_y,
      final_z
    };
    return new_point;
}

void draw_points(Vector3* points, int len_points) {
    for (int i = 0; i < len_points; ++i) {
        Vector3 norm_point = normalize_and_project(points[i]);
        DrawCircle((int)norm_point.x, (int)norm_point.y, 5.0f, RED);
    }
}

void draw_edges(Vector3* points, Vector2* edges, int len_edges) {
    for (int i = 0; i < len_edges; ++i) {
        Vector3 norm_start = normalize_and_project(points[(int)edges[i].x]);
        Vector3 norm_end = normalize_and_project(points[(int)edges[i].y]);

        DrawLineEx((Vector2){norm_start.x, norm_start.y}, (Vector2){norm_end.x, norm_end.y}, 3.0f, GREEN);
    }
}

void rotate(Vector3* point, float theta, Axis axis) {
    if(axis == X){
        float new_y = point->y * cos(theta) - point->z * sin(theta);
        float new_z = point->y * sin(theta) + point->z * cos(theta);
        point->y = new_y;
        point->z = new_z;
    }
    else if(axis == Y){
        float new_x = point->x * cos(theta) - point->z * sin(theta);
        float new_z = point->x * sin(theta) + point->z * cos(theta);
        point->x = new_x;
        point->z = new_z;
    }
    else if(axis == Z){
        float new_x = point->x * cos(theta) - point->y * sin(theta);
        float new_y = point->x * sin(theta) + point->y * cos(theta);
        point->x = new_x;
        point->y = new_y;
    }
}

void move(Vector3 *object_pos, Vector3 speed_vector){
    object_pos->x += speed_vector.x;
    object_pos->y += speed_vector.y;
    object_pos->z += speed_vector.z;
}

//----------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {

    if(argc != 2){
        printf("Correct usage:%s <file.pyl>\n", argv[0]);
        exit(-1);
    }

    DArray* points = da_create(sizeof(Vector3));
    DArray* edges = da_create(sizeof(Vector2));

    parse(argv[1], points, edges);

    InitWindow(WIN_W, WIN_H, "Spinning object");
    SetTargetFPS(TARGET_FPS);
    while (!WindowShouldClose()) {

        angle += ROTATION_SPEED;
        move(&object_pos, object_speed);
        if(object_pos.z > 6.0f || object_pos.z < 0.0f) object_speed.z *= -1;

        Vector3* cp_points = malloc(points->size * sizeof(Vector3));
        for (int i = 0; i < points->size; i++){
            cp_points[i] = ((Vector3*)points->data)[i];
            rotate(&cp_points[i], angle, Y);
            move(&cp_points[i], object_pos);         //needed to place the points in the correct spot after rotating them
        }

        BeginDrawing();

            ClearBackground(BLACK);
            //draw_points(cp_points, points->size);
            draw_edges(cp_points, (Vector2*)edges->data, (int)edges->size);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
