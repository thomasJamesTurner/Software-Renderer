#include "renderer.h"
void wireframe(Window* window,const Vec3 * vertex_buffer,const int * index_buffer, const int index_count){
    for (int i = 0; i < index_count; i += 3) {
        Vec3 a = vertex_buffer[index_buffer[i]];
        Vec3 b = vertex_buffer[index_buffer[i + 1]];
        Vec3 c = vertex_buffer[index_buffer[i + 2]];

        window_draw_line(window, basic_projector(window,a), basic_projector(window,b), (Colour){255, 255, 255, 255});
        window_draw_line(window, basic_projector(window,b), basic_projector(window,c), (Colour){255, 255, 255, 255});
        window_draw_line(window, basic_projector(window,c), basic_projector(window,a), (Colour){255, 255, 255, 255});
    }
}


Vec2 basic_projector(Window* window, Vec3 v){

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
