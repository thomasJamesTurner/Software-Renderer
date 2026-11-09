#include "window.h"

//TODO move all vertex and 
typedef struct{
    int x;
    int y;
    int z;
}Vec3;

Vec3 vertices[] = {
    {-1, -1, 0},
    { 1, -1, 0},
    { 1,  1, 0},
    {-1,  1, 0},
};

int indices[] = {
    0, 1, 2,   // first triangle
    0, 2, 3    // second triangle
};


Vec2 basic_projector(Window* window,Vec3 v){

    //TODO change cam distance and focal length 
    //with traditional projection matrix with fov and
    //fnear and ffar values
    const float camera_distance = 5.0f;
    const float focal_length    = 3.0f;
    float z = v.z + camera_distance;

    float px = (v.x * focal_length) / z;
    float py = (v.y * focal_length) / z;

    //map to screen space, just needs to be visable
    float half_h = window->window_height / 2.0f;

    Vec2 out;
    out.x = (int)(window->window_width  / 2.0f + px * half_h + 0.5f);
    out.y = (int)(window->window_height / 2.0f - py * half_h + 0.5f);
    return out;
}

void wireframe(Window* window){
    int index_count = sizeof(indices)/sizeof(indices[0]);
    for (int i = 0; i < index_count; i += 3) {
        Vec3 a = vertices[indices[i]];
        Vec3 b = vertices[indices[i + 1]];
        Vec3 c = vertices[indices[i + 2]];

        window_draw_line(window, basic_projector(window,a), basic_projector(window,b), (Colour){255, 255, 255, 255});
        window_draw_line(window, basic_projector(window,b), basic_projector(window,c), (Colour){255, 255, 255, 255});
        window_draw_line(window, basic_projector(window,c), basic_projector(window,a), (Colour){255, 255, 255, 255});
    }
}



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

    while (window_poll_events(&window)) {
        window_clear(&window, (Colour){30, 30, 30, 255});
        wireframe(&window);
        window_update(&window);
    }

    window_destroy(&window);
    return 0;
}
