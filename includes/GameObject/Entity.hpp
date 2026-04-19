#pragma once

#include "GameObject.hpp"
#include "Input.hpp"

struct EntityData
{
    EntityState state;
    EntityData()
    {
        state = EntityState::idle;
    }

    int ID = 0;

    float MaxLife = 100.0f;
    float life = MaxLife;

    unsigned int Level;
    float Exp;
};

class Entity : public GameObject
{
public:
    EntityData data;
    glm::vec2 velocity, acceleration;
    float maxSpeedX;
    float jumpForce;
    bool debug = true;

public:
    virtual void update(SDLState &, float, std::vector<GameObject *>);

    int getDirection();

    void setDirection(int value);

    void collisionResponse(SDLState &state, const SDL_FRect &rectA, const SDL_FRect &rectB, const SDL_FRect &rectC, GameObject &b, float deltaTime) override;

    void onStateChange(EntityState);

    void debugLog(SDLState &state) override;
};