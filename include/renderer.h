#ifndef RENDERER_H
#define RENDERER_H
#include "window.h"

typedef struct{
    int x;
    int y;
    int z;
}Vec3;

typedef struct{
    int x;
    int y;
    int z;
    int w;    
}Vec4;

void wireframe(Window* window, const Vec3 * vertex_buffer,const int * index_buffer, const int index_count);
Vec2 basic_projector(Window* window, Vec3 v);

#endif
