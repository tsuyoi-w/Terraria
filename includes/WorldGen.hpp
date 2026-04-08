#pragma once

#include "GameObject/LevelObj.hpp"
#include "GameObject/Player.hpp"

class WorldGen
{
private:
    static constexpr unsigned int MAP_ROWS = 10;
    static constexpr unsigned int MAP_COLS = 50;
    static constexpr unsigned int TILE_SIZE = 32;

public:
    const unsigned int BG_INDEX = 0;
    const unsigned int TILES_INDEX = 1;
    const unsigned int ENTITY_INDEX = 2;

    std::array<std::vector<GameObject *>, 3> LAYERS;

    WorldGen(SDLState &state)
    {
        createTiles(state);
    }

    void createTiles(const SDLState &state)
    {
        short map[MAP_ROWS][MAP_COLS];
        map[1][1] = 4;
        const auto creatLevel = [this, &state](ObjectType type, int r, int c)
        {
            LevelObj *obj = new LevelObj();
            glm::vec2 pos(
                c * TILE_SIZE,
                state.logH - (MAP_ROWS - r) * TILE_SIZE);
            obj->collider = {.x = 0, .y = -1, .w = 32, .h = 32};
            obj->position = pos;
            return obj;
        };

        const auto createPlayer = [this, &state](int r, int c)
        {
            glm::vec2 pos(
                c * TILE_SIZE,
                state.logH - (MAP_ROWS - r) * TILE_SIZE);
            Player *obj = new Player(pos);
            obj->position = pos;
            obj->collider = {.x = 11, .y = 6, .w = 10, .h = 26};
            return obj;
        };

        for (int r = 0; r < MAP_ROWS; r++)
        {
            for (int c = 0; c < MAP_COLS; c++)
            {
                if (r == 3 || r == 4 || r == 5)
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
                    LAYERS[TILES_INDEX].push_back(obj);
                    continue;
                }
                switch (map[r][c])
                {
                case 4:
                {
                    Player *player = createPlayer(r, c);
                    LAYERS[ENTITY_INDEX].push_back(player);
                    break;
                }
                }
            }
        }
    }
};
