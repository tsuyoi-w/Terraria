#pragma once

#include "Chunk.hpp"

class WorldGen
{
private:
    static constexpr unsigned int MAP_ROWS = 10;
    static constexpr unsigned int MAP_COLS = 50;
    static constexpr unsigned int TILE_SIZE = 32;

public:
    std::vector<Chunk> chunks;

    Player *player;

    std::array<std::vector<GameObject *>, 3> LAYERS;

    WorldGen(SDLState &state, std::vector<Chunk> chunks)
    {
        player = new Player({400, 0});
        player->position = player->spawnPoint;
        LAYERS[2].push_back(player);

        int index = 0;
        for (Chunk &chunk : chunks)
        {
            chunk.GenChunk(state, this->LAYERS, index);
            index++;
        }
    }

    Player *getPlayer()
    {
        return this->player;
    }
};
