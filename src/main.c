#include "window.h"
#include "renderer.h"

Vec3 vertices[] = {
    {-1, -1, 0},
    { 1, -1, 0},
    { 1,  1, 0},
    {-1,  1, 0},
};

int indices[] = {
    0, 1, 2,   // first triangle
    0, 2, 3,   // second triangle
    3, 2, 1    // third triangle, should see a cross patern 
};

int main(void)
{
    Window window = {
        .window_title  = "My Application",
        .window_width  = 800,
        .window_height = 600,
        .window_x      = 100,
        .window_y      = 100
    };

    if (!window_create(&window)) {
        return 1;
    }
    int index_count = sizeof(indices)/sizeof(indices[0]);

    while (window_poll_events(&window)) {
        window_clear(&window, (Colour){30, 30, 30, 255});
        wireframe(&window, vertices, indices,index_count);
        window_update(&window);
    }

    window_destroy(&window);
    return 0;
}
