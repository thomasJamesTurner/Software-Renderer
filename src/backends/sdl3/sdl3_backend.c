#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "sdl3_backend.h"

// SDL-specific window data.
// This structure is private to this backend.
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} SDL3WindowData;


// Create SDL window
static bool sdl3_create_window(Window* this)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL Init Error: %s\n", SDL_GetError());
        return false;
    }

    SDL3WindowData* data = malloc(sizeof(SDL3WindowData));

    if (!data) {
        return false;
    }

    data->window = NULL;
    data->renderer = NULL;

    if (!SDL_CreateWindowAndRenderer(
        this->window_title,
        this->window_width,
        this->window_height,
        SDL_WINDOW_RESIZABLE,
        &data->window,
        &data->renderer
    )) {
        fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
        free(data);
        SDL_Quit();
        return false;
    }
    // Set initial window position
    SDL_SetWindowPosition(
        data->window,
        this->window_x,
        this->window_y
    );

    this->backend_data = data;

    return true;
}


// Destroy SDL window
static bool sdl3_destroy_window(Window* this)
{
    SDL3WindowData* data = this->backend_data;

    if (!data) {
        return true;
    }

    SDL_DestroyRenderer(data->renderer);
    SDL_DestroyWindow(data->window);

    free(data);
    this->backend_data = NULL;

    SDL_Quit();
    return true;
}


// Process SDL events
static bool sdl3_poll_events_window(Window* this)
{
    SDL3WindowData* data = this->backend_data;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }

        if (
            event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
            event.window.windowID == SDL_GetWindowID(data->window)
        ) {
            return false;
        }
    }

    return true;
}


// Clear window
static void sdl3_clear_window(Window* this, Colour colour)
{
    SDL3WindowData* data = this->backend_data;

    SDL_SetRenderDrawColor(
        data->renderer,
        colour.r,
        colour.g,
        colour.b,
        colour.a
    );

    SDL_RenderClear(data->renderer);
}


// Present rendered frame
static void sdl3_update_window(Window* this)
{
    SDL3WindowData* data = this->backend_data;

    SDL_RenderPresent(data->renderer);
}

void sdl3_window_init(Window* window)
{
    window->backend_data       = NULL;
    window->create_window      = sdl3_create_window;
    window->destroy_window     = sdl3_destroy_window;
    window->poll_events_window = sdl3_poll_events_window;
    window->update_window      = sdl3_update_window;
    window->clear_window       = sdl3_clear_window;
}
