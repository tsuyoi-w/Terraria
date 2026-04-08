#define SDL_MAIN_HANDLED
#include "../includes/WorldGen.hpp"

void render(WorldGen &worldGen, SDLState &state, float deltaTime);

int main()
{
    SDLState state;
    WorldGen worldGen(state);

    if (!initialize(state))
        return 1;

    uint64_t prevTime = SDL_GetTicks();
    while (state.running)
    {
        uint64_t nowTime = SDL_GetTicks();
        float deltaTime = (nowTime - prevTime) / 1000.0f;
        SDL_Event event = {0};
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                state.running = false;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                state.width = event.window.data1;
                state.heigth = event.window.data2;
                break;
            }
        }

        render(worldGen, state, deltaTime);

        SDL_RenderPresent(state.renderer);
        prevTime = nowTime;
    }

    cleanup(state);
    return 0;
}

void render(WorldGen &worldGen, SDLState &state, float deltaTime)
{
    for (auto &layer : worldGen.LAYERS)
    {
        for (auto &obj : layer)
        {
            if (obj->type == ObjectType::player)
                obj->update(state, deltaTime, worldGen.LAYERS[worldGen.TILES_INDEX]);
        }
    }

    SDL_SetRenderDrawColor(state.renderer, 0, 80, 197, 255);
    SDL_RenderClear(state.renderer);

    for (auto &layer : worldGen.LAYERS)
    {
        for (auto &obj : layer)
        {
            obj->drawObject(state, deltaTime);
        }
    }
}