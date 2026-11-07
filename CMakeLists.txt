cmake_minimum_required(VERSION 3.20)

project(Software-Renderer VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)

add_executable(Software-Renderer
    src/main.c
    src/window.c
    src/backends/sdl3/sdl3_backend.c
)

target_include_directories(Software-Renderer PRIVATE
    include
    src/backends/sdl3
)

target_link_libraries(Software-Renderer PRIVATE
    PkgConfig::SDL3
)

target_compile_options(Software-Renderer PRIVATE
  -Wall -Wextra -Wpedantic -DWINDOW_BACKEND_SDL3
)
