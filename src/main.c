#include "window.h"

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
        window_update(&window);
    }

    window_destroy(&window);
    return 0;
}
