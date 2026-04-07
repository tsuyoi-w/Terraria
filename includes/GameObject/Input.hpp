#pragma once

#include <SDL3/SDL.h>

struct movementState
{
    glm::vec2 velocity;
    float direction;
};

class Input
{
private:
    const bool *keys;

public:
    Input()
    {
        keys = SDL_GetKeyboardState(nullptr);
    }

    bool getKeys() const
    {
        return this->keys;
    }

    movementState checkAction(glm::vec2 &velocity, float &acceleration, float &maxSpeed, float dt)
    {
        float currentDirection = 0;
        bool moov = false;
        if (keys[SDL_SCANCODE_A])
        {
            currentDirection += -1;
            moov = true;
        }
        if (keys[SDL_SCANCODE_D])
        {
            currentDirection += 1;
            moov = true;
        }

        if (moov)
        {
            velocity += currentDirection * acceleration * dt;
            if (std::abs(velocity.x) > maxSpeed)
                velocity.x = currentDirection * maxSpeed;
            return {{velocity.x , 500}, currentDirection};
        }
        return {glm::vec2(0, 500), currentDirection};
    }
};