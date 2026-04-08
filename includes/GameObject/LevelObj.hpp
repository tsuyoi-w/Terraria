#pragma once
#include "GameObject.hpp"

class LevelObj : public GameObject
{
private:
public:
    LevelObj()
    {
        this->type = ObjectType::level;
        this->position = {0, 0};
        this->currentAnimation = -1;
        this->dynamic = false;
        this->textures[0] = "data/texture/Maps/Tiles/grass_block.png";
        this->textures[1] = "data/texture/Maps/Tiles/dirt_block.png";
        this->textures[2] = "data/texture/Maps/Tiles/stone_block.png";
    }
};