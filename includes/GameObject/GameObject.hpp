#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include <map>

#include "./state.hpp"
#include "../Init.hpp"
#include "Animation.hpp"

struct EntityData;

struct LevelData;

struct EnemyData
{
};

enum class ObjectType
{
    player,
    level,
    ennemy,
    boss,
    npc
};

class GameObject
{
public:
    ObjectType type;

    glm::vec2 position;
    float direction;

    std::vector<Animation> animations;
    std::map<int, std::string> textures;

    SDL_Texture *tex;

    bool dynamic;
    bool inCollision = false;

    SDL_FRect collider;
    int currentAnimation;
    int currentText = 0;

    GameObject();

    virtual ~GameObject() = default;

    void drawObject(const SDLState &, float);

    SDL_Texture *LoadTexture(SDL_Renderer *, const std::string &);

    virtual void update(SDLState &, float, std::vector<GameObject *>);

    virtual void checkCollision(SDLState &, GameObject &, float);

    virtual void debugLog(SDLState &state) {}

    virtual void collisionResponse(SDLState &, const SDL_FRect &, const SDL_FRect &, const SDL_FRect &, GameObject &b, float);
};