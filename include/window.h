#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

typedef struct Window Window;

typedef struct {
  int r;
  int g;
  int b;
  int a;
}Colour;

struct Window {
  const char* window_title;
  int window_x;
  int window_y;
  int window_width;
  int window_height;
  int window_fps;

  //holds implementation specific widowing data (e.g SDL3's SDL_Window and SDL_Renderer)
  void* backend_data;

  bool (*create_window)(Window *this);
  bool (*destroy_window)(Window *this);
  bool (*poll_events_window)(Window *this);
  void (*update_window)(Window *this);
  void (*clear_window)(Window *this, Colour);
};

bool window_create(Window* window);
bool window_destroy(Window* window);
bool window_poll_events(Window* window);
void window_clear(Window* window, Colour colour);
void window_update(Window* window);

#endif
