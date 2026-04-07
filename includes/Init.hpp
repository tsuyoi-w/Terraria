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

bool initialize(SDLState &state)
{
    bool success = true;
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
        success = false;
    }

    state.window = SDL_CreateWindow("Tsurraria", state.width, state.heigth, SDL_WINDOW_RESIZABLE);
    if (!state.window)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing window", nullptr);
        success = false;
    }

    state.renderer = SDL_CreateRenderer(state.window, nullptr);
    if (!state.renderer)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing renderer", nullptr);
        success = false;
    }

    SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return success;
}

void cleanup(SDLState &state)
{
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}