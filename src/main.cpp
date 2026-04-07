#define SDL_MAIN_HANDLED

#include "../includes/Init.hpp"
#include "../includes/GameObject/Entity.hpp"
#include "../includes/GameObject/Input.hpp"
#include "../includes/WorldGen.hpp"
#include <memory>

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
        for (auto &obj : worldGen.getLayers())
        {
            if (obj->getType() == ObjectType::player)
                obj->movement(state, deltaTime, worldGen.getLayers());
        }

        SDL_SetRenderDrawColor(state.renderer, 0, 80, 197, 255);
        SDL_RenderClear(state.renderer);

        for (auto &obj : worldGen.getLayers())
        {
            obj->drawObject(state, deltaTime);
        }
        SDL_RenderPresent(state.renderer);
        prevTime = nowTime;
    }

    cleanup(state);
    return 0;
}