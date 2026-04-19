#pragma once

#include "GameObject/LevelObj.hpp"
#include "GameObject/Player.hpp"
#include <glm/glm.hpp>
#include "Init.hpp"

enum class Biome
{
    plain,
    forest,
    desert
};

class Chunk
{
private:
    static constexpr unsigned int MAP_ROWS = 5;
    static constexpr unsigned int MAP_COLS = 10;
    static constexpr unsigned int TILE_SIZE = 32;

public:
    Biome biome;

    const unsigned int BG_INDEX = 0;
    const unsigned int TILES_INDEX = 1;
    const unsigned int ENTITY_INDEX = 2;

public:
    Chunk()
    {
        this->biome = Biome::plain;
    }

    void GenChunk(const SDLState &state, std::array<std::vector<GameObject *>, 3> &LAYERS, int index)
    {
        short map[MAP_ROWS][MAP_COLS];
        const auto creatLevel = [this, &state, index](ObjectType type, int r, int c)
        {
            int offset = MAP_COLS * index;
            LevelObj *obj = new LevelObj();
            glm::vec2 pos(
                (c * 32) + (offset * 32),
                state.logH - (5 - r) * TILE_SIZE);
            obj->collider = {.x = 0, .y = 0, .w = TILE_SIZE, .h = TILE_SIZE};
            obj->position = pos;
            return obj;
        };

        for (int r = 0; r < MAP_ROWS; r++)
        {
            for (int c = 0; c < MAP_COLS; c++)
            {

                map[r][c] = 1;
                LevelObj *obj = creatLevel(ObjectType::level, r, c);
                if (map[r - 1][c] == 1 && r > 4)
                {
                    obj->currentText = 2;
                }
                else if (map[r - 1][c] == 1)
                {
                    obj->currentText = 1;
                }
                if (c > 24)
                {
                    obj->currentText = 2;
                }
                LAYERS[TILES_INDEX].push_back(obj);
                continue;
            }
        }
    }
};