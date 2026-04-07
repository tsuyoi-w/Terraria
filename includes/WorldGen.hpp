#pragma once

#include "GameObject/LevelObj.hpp"
#include "GameObject/Player.hpp"

class WorldGen
{
private:
    static constexpr unsigned int MAP_ROWS = 5;
    static constexpr unsigned int MAP_COLS = 50;
    static constexpr unsigned int TILE_SIZE = 32;
    std::vector<GameObject *> LAYERS;

public:
    WorldGen(SDLState &state)
    {
        createTiles(state);
    }

    void createTiles(const SDLState &state)
    {
        /*
        ! 1 - Ground
        ! 2 - Panel
        ! 3 - Enemy
        ! 4 - Player
        ! 5 - Grass
        ! 6 - Brick
        */
        short map[MAP_ROWS][MAP_COLS] = {
            4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        const auto creatLevel = [this, &state](ObjectType type, int r, int c)
        {
            LevelObj *obj = new LevelObj();
            glm::vec2 pos(
                c * TILE_SIZE,
                state.logH - (MAP_ROWS - r) * TILE_SIZE);
            obj->setCollider({.x = 0, .y = -1, .w = 32, .h = 32});
            obj->setPosition(pos);
            return obj;
        };

        const auto createPlayer = [this, &state](int r, int c)
        {
            glm::vec2 pos(
                c * TILE_SIZE,
                state.logH - (MAP_ROWS - r) * TILE_SIZE);
            Player *obj = new Player(pos);
            obj->setPosition(pos);
            obj->setCollider({.x = 11, .y = 6, .w = 10, .h = 26});
            return obj;
        };

        for (int r = 0; r < MAP_ROWS; r++)
        {
            for (int c = 0; c < MAP_COLS; c++)
            {
                switch (map[r][c])
                {
                case 1:
                {
                    LevelObj *obj = creatLevel(ObjectType::level, r, c);
                    LAYERS.push_back(obj);
                    break;
                }
                case 4:
                {
                    Player *player = createPlayer(r, c);
                    player->setCollider({.x = 11, .y = 6, .w = 10, .h = 26});
                    LAYERS.push_back(player);
                    break;
                }
                }
            }
        }
    }

    std::vector<GameObject *> &
    getLayers()
    {
        return this->LAYERS;
    }
};