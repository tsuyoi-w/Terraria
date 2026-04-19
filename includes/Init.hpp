#pragma once

#include "font.hpp"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

struct SDLState
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running = true;

    unsigned int width = 800;
    unsigned int heigth = 600;
    unsigned int logW = 800;
    unsigned int logH = 600;
};

bool initialize(SDLState &);

void cleanup(SDLState &state);