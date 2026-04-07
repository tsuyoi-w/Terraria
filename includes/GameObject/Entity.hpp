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
};

class Entity : public GameObject
{
protected:
    EntityData data;
    glm::vec2 velocity, acceleration;
    float maxSpeedX;
    float jumpForce;

public:
    virtual void update(SDLState &, float, std::vector<GameObject *>);

    int getDirection();

    void setDirection(int value);

    void collisionResponse(SDLState &state, const SDL_FRect &rectA, const SDL_FRect &rectB, const SDL_FRect &rectC, GameObject &b, float deltaTime) override;

    void onStateChange(EntityState);

    void checkCollision(SDLState &state, GameObject &obj, float deltaTime);
};