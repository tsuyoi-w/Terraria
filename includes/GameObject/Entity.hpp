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
    Entity(ObjectType type) : acceleration(300), maxSpeedX(100)
    {
        this->type = type;
        this->position = {0, 0};
        this->direction = 0.0f;
        this->currentAnimation = 0;
        this->dynamic = true;
        this->animations.push_back(Animation(8, 1.6f));
        this->textures[0] = "data/texture/Characters/players/idle.png";
    }

    void movement(SDLState &state, float deltaTime, std::vector<GameObject *> layers) override
    {
        movementState newVec = input.checkAction(this->velocity, this->acceleration.x, this->maxSpeedX, deltaTime);
        this->direction = (newVec.direction == 0) ? this->direction : newVec.direction;
        switch (this->data.state)
        {
        case EntityState::idle:
            if (this->direction)
            {
                this->data.state = EntityState::running;
                this->currentAnimation = 0;
            }
            else
            {
                if (this->velocity.x)
                {
                    const float factor = this->velocity.x > 0 ? -1.5f : 1.5f;
                    float amount = factor * this->acceleration.x * deltaTime;
                    if (std::abs(this->velocity.x) > std::abs(amount))
                    {
                        this->velocity.x = 0;
                    }
                    else
                    {
                        this->velocity.x = amount;
                    }
                }
            }

            break;
        case EntityState::running:
            if (!this->direction)
            {
                this->data.state = EntityState::idle;
                this->currentAnimation = 0;
            }
            break;
        }

        this->velocity = newVec.velocity;
        this->position += this->velocity * deltaTime;

        if (this->position.x > state.logW - 30)
            this->position.x = state.logW - (30);
        if (this->position.x < 0)
            this->position.x = 0;

        for (auto &obj : layers)
        {
            if (obj->getType() != ObjectType::player)
            {
                checkCollision(state, *obj, deltaTime);
            }
        }
    }

    int getDirection()
    {
        return this->direction;
    }

    void setDirection(int value)
    {
        this->direction = value;
    }

    void collisionResponse(SDLState &state, const SDL_FRect &rectA, const SDL_FRect &rectB, const SDL_FRect &rectC, GameObject &b, float deltaTime) override
    {
        if (this->type == ObjectType::player)
        {
            std::cout << " Coll w = " << rectC.w << " / Coll h = " << rectC.h << std::endl;
            switch (b.getType())
            {
            case ObjectType::level:

                if (rectC.w < rectC.h)
                {
                    if (this->velocity.x > 0)
                    {
                        this->position.x -= rectC.w;
                    }
                    else if (this->velocity.x < 0)
                    {
                        this->position.x += rectC.w;
                    }
                    this->velocity.x = 0;
                }
                else
                {
                    if (this->velocity.y > 0)
                    {
                        this->position.y -= rectC.h;
                    }
                    else if (this->velocity.y < 0)
                    {
                        this->position.y += rectC.h;
                    }
                    this->velocity.y = 0;
                }
                break;
            }
        }
    }
};