#pragma once
#include "Entity.hpp"
#include "../Camera.hpp"

class Player : public Entity
{
public:
    Input input;
    glm::vec2 spawnPoint;
    float cooldown = 0;
    Camera camera;

    Player() {}

    Player(glm::vec2 sw)
    {
        this->type = ObjectType::player;
        this->acceleration = glm::vec2(300);
        this->maxSpeedX = 100;
        this->type = type;
        this->position = {0, 0};
        this->direction = 0.0f;
        this->currentAnimation = 0;
        this->dynamic = true;
        this->animations.push_back(Animation(8, 1.6f));
        this->textures[0] = "data/texture/Characters/players/idle.png";
        this->textures[1] = "data/texture/Characters/players/walking.png";
        this->spawnPoint = sw;
        this->collider = {.x = 11, .y = 6, .w = 10, .h = 26};
    }
    void update(SDLState &state, float deltaTime, std::vector<GameObject *> layers) override
    {
        cooldown += deltaTime;
        if (this->dynamic && !this->inCollision)
            this->velocity += glm::vec2(0, 500) * deltaTime;

        movementState newMov = input.checkAction();
        this->direction = newMov.direction;
        this->data.state = newMov.state;
        switch (this->data.state)
        {
        case EntityState::idle:
            if (this->velocity.x)
            {
                this->currentAnimation = 0;
                const float factor = this->velocity.x > 0 ? -5.0f : 5.0f;
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
            break;
        case EntityState::respawn:
            this->respawn();
            this->velocity.y -= this->velocity.y;
            this->data.life -= 5;
            this->camera.pos = {0, 0};
            break;
        case EntityState::debug:

            this->debug = !this->debug;
            break;
        case EntityState::jumping:
            this->velocity.y = 0;
            this->velocity.y = -200;
            break;
        }

        this->velocity.x += this->direction * this->acceleration.x * deltaTime;
        if (std::abs(this->velocity.x) > this->maxSpeedX)
        {
            this->velocity.x = this->direction * this->maxSpeedX;
        }
        this->position += this->velocity * deltaTime;

        this->camera.set((this->velocity.x * deltaTime) * -1);

        for (auto &obj : layers)
        {
            if (obj->type != ObjectType::player)
            {
                checkCollision(state, *obj, deltaTime);
            }
        }
    }

    void respawn()
    {
        this->position = spawnPoint;
    }
};