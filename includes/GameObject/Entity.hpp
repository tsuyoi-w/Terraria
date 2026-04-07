#pragma once

#include "GameObject.hpp"
#include "Input.hpp"

enum class EntityState
{
    idle,
    walking,
    running,
    jumping,
    falling,
    flying,
    swiming
};

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
private:
    EntityData data;

    Input input;

    glm::vec2 velocity, acceleration;
    float maxSpeedX;

public:
    Entity(ObjectType);

    void movement(SDLState &, float, std::vector<GameObject *>) override;

    int getDirection();

    void setDirection(int value);

    void collisionResponse(SDLState &state, const SDL_FRect &rectA, const SDL_FRect &rectB, const SDL_FRect &rectC, GameObject &b, float deltaTime) override;

    void onStateChange(EntityState);

    void checkCollision(SDLState &state, GameObject &obj, float deltaTime);
};