#include "window.h"

// The only place that knows which backend is in use.
// Pick one at build time, e.g. -DWINDOW_BACKEND_SDL3
#if defined(WINDOW_BACKEND_SDL3)
    #include "sdl3_backend.h"
    #define BACKEND_INIT sdl3_window_init
#else
    #error "No window backend selected"
#endif

bool window_create(Window* window)
{
    BACKEND_INIT(window);
    return window->create_window(window);
}

bool window_destroy(Window* window)
{
    if (!window->destroy_window) return false;
    return window->destroy_window(window);
}

bool window_poll_events(Window* window)
{
    return window->poll_events_window(window);
}

void window_clear(Window* window, Colour colour)
{
    window->clear_window(window, colour);
}

void window_update(Window* window)
{
    window->update_window(window);
}
