#pragma once

#include <glm/glm.hpp>
#include <SDL3/SDL.h>

struct SDLState
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running = true;

    unsigned int width = 800;
    unsigned int heigth = 600;
    unsigned int logW = 640;
    unsigned int logH = 320;
};

bool initialize(SDLState &);

void cleanup(SDLState &state);