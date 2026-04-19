#define SDL_MAIN_HANDLED
#include "../includes/WorldGen.hpp"

void render(WorldGen &worldGen, SDLState &state, float deltaTime, Player *player);

int main()
{
    SDLState state;
    std::vector<Chunk> chunks;
    chunks.push_back(Chunk());
    chunks.push_back(Chunk());
    chunks.push_back(Chunk());
    chunks.push_back(Chunk());
    chunks.push_back(Chunk());
    chunks.push_back(Chunk());
    chunks.push_back(Chunk());
    WorldGen worldGen(state, chunks);
    Player *player = worldGen.getPlayer();

    std::cout << chunks.size() << std::endl;

    if (!initialize(state))
        return 1;

    uint64_t prevTime = SDL_GetTicks();
    while (state.running)
    {
        if (player->data.life <= 0)
        {
            cleanup(state);
            state.running = false;
        }
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

        render(worldGen, state, deltaTime, player);

        SDL_RenderPresent(state.renderer);
        prevTime = nowTime;
    }

    cleanup(state);
    return 0;
}

void render(WorldGen &worldGen, SDLState &state, float deltaTime, Player *player)
{
    for (auto &layer : worldGen.LAYERS)
    {
        for (auto &obj : layer)
        {
            if (obj->type == ObjectType::player)
                obj->update(state, deltaTime, worldGen.LAYERS[1]);
        }
    }

    SDL_SetRenderDrawColor(state.renderer, 0, 80, 197, 255);
    SDL_RenderClear(state.renderer);

    for (auto &layer : worldGen.LAYERS)
    {
        for (auto &obj : layer)
        {
            obj->position.x += player->camera.pos.x;
            if (obj->position.x >= -50 && obj->position.x < 800)
            {
                obj->drawObject(state, deltaTime);
            }
            obj->debugLog(state);
            obj->position.x -= player->camera.pos.x;
        }
    }
}