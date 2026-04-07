#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include <map>

#include "../Init.hpp"
#include "Animation.hpp"

enum class EntityState;

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

struct GameObject
{
public:
    ObjectType type;

    glm::vec2 position;
    float direction;

    std::vector<Animation> animations;
    std::map<int, std::string> textures;

    SDL_Texture *tex;

    bool dynamic;


    SDL_FRect collider;
    int currentAnimation;
    GameObject() : collider{0}
    {
    }

    virtual ~GameObject() = default;

    void drawObject(const SDLState &state, float deltaTime)
    {
        const float spriteSize = 32;
        float srcX = this->currentAnimation != -1
                         ? this->animations[this->currentAnimation].currentFrame() * spriteSize
                         : 0.0f;
        SDL_FRect src{
            .x = srcX,
            .y = 0,
            .w = spriteSize,
            .h = spriteSize};

        SDL_FRect dst{
            .x = this->position.x,
            .y = this->position.y,
            .w = spriteSize,
            .h = spriteSize};

        if (this->currentAnimation != -1)
        {
            this->animations[this->currentAnimation].step(deltaTime);
        }
        SDL_FlipMode flipMode = this->direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderTextureRotated(state.renderer, LoadTexture(state.renderer, this->textures[0]), &src, &dst, 0, nullptr, flipMode);
    }

    SDL_Texture *LoadTexture(SDL_Renderer *renderer, const std::string &filepath)
    {
        SDL_Texture *tex = IMG_LoadTexture(renderer, filepath.c_str());
        SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
        return tex;
    }

    ObjectType getType()
    {
        return this->type;
    }

    virtual void movement(SDLState &state, float deltaTime, std::vector<GameObject *> layers)
    {
        std::cout << "wrong movement" << std::endl;
    }

    void setCollider(SDL_FRect value)
    {
        this->collider = value;
    }

    virtual void checkCollision(SDLState &state, GameObject &obj, float deltaTime)
    {
        SDL_FRect rectA{
            .x = this->position.x + this->collider.x, .y = this->position.y + this->collider.y, .w = this->collider.w, .h = this->collider.h};
        SDL_FRect rectB{
            .x = obj.position.x + obj.collider.x, .y = obj.position.y + obj.collider.y, .w = obj.collider.w, .h = obj.collider.h};

        SDL_FRect rectC{0};

        if (SDL_GetRectIntersectionFloat(&rectA, &rectB, &rectC))
        {
            this->collisionResponse(state, rectA, rectB, rectC, obj, deltaTime);
        }
    }

    void setPosition(glm::vec2 pos)
    {
        this->position = pos;
    }

    glm::vec2 getPosition()
    {
        return this->position;
    }

    virtual void collisionResponse(SDLState &state, const SDL_FRect &rectA, const SDL_FRect &rectB, const SDL_FRect &rectC, GameObject &b, float deltaTime)
    {
        std::cout << "wrong collider" << std::endl;
    }
};