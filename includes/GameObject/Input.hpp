#pragma once

#include <SDL3/SDL.h>
#include "state.hpp"

struct movementState
{
    EntityState state;
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

    movementState checkAction()
    {
        EntityState st = EntityState::idle;
        float currentDirection = 0;
        if (keys[SDL_SCANCODE_A])
        {
            st = EntityState::walking;
            currentDirection += -1;
        }
        else
        {
            st = EntityState::idle;
        }
        if (keys[SDL_SCANCODE_D])
        {
            st = EntityState::walking;
            currentDirection += 1;
        }
        if (keys[SDL_SCANCODE_SPACE])
        {
            st = EntityState::jumping;
        }
        if (keys[SDL_SCANCODE_R])
        {
            st = EntityState::respawn;
        }
        if (keys[SDL_SCANCODE_TAB])
        {
            st = EntityState::debug;
        }
        return {st, currentDirection};
    }
};