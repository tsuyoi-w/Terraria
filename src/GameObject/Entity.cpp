#include "../../includes/GameObject/Entity.hpp"

void Entity::update(SDLState &state, float deltaTime, std::vector<GameObject *> layers)
{
}

void Entity::collisionResponse(SDLState &state, const SDL_FRect &rectA, const SDL_FRect &rectB, const SDL_FRect &rectC, GameObject &b, float deltaTime)
{

    if (this->type == ObjectType::player)
    {
        this->inCollision = true;
        switch (b.type)
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

int Entity::getDirection()
{
    return this->direction;
}

void Entity::setDirection(int value)
{
    this->direction = value;
}

void Entity::onStateChange(EntityState state)
{
    switch (state)
    {
    case EntityState::idle:
        this->currentAnimation = 0;
        this->data.state = state;
        break;
    case EntityState::walking:
        this->currentAnimation = 0;
        this->data.state = state;
        break;
    case EntityState::running:
        this->currentAnimation = 0;
        this->data.state = state;
        break;
    }
}

void Entity::debugLog(SDLState &state)
{
    if (debug)
    {
        int w = 0, h = 0;
        SDL_FRect dst[5];
        const float scale = 4.0f;

        std::string msg;

        SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};
        msg = "-- Debug --";
        text[0] = TTF_RenderText_Blended(font, msg.c_str(), 0, color);
        msg = "Life : " + std::to_string((int)this->data.life);
        text[1] = TTF_RenderText_Blended(font, msg.c_str(), 0, color);
        msg = "Position : x " + std::to_string((int)this->position.x) + " y " + std::to_string((int)this->position.y);
        text[2] = TTF_RenderText_Blended(font, msg.c_str(), 0, color);
        msg = "Velocity : x " + std::to_string((int)this->velocity.x) + " y " + std::to_string((int)this->velocity.y);
        text[3] = TTF_RenderText_Blended(font, msg.c_str(), 0, color);
        msg = "Collision : " + std::to_string(this->inCollision);
        text[4] = TTF_RenderText_Blended(font, msg.c_str(), 0, color);
        if (text)
        {
            texture[0] = SDL_CreateTextureFromSurface(state.renderer, text[0]);
            SDL_DestroySurface(text[0]);
            texture[1] = SDL_CreateTextureFromSurface(state.renderer, text[1]);
            SDL_DestroySurface(text[1]);
            texture[2] = SDL_CreateTextureFromSurface(state.renderer, text[2]);
            SDL_DestroySurface(text[2]);
            texture[3] = SDL_CreateTextureFromSurface(state.renderer, text[3]);
            SDL_DestroySurface(text[3]);
            texture[4] = SDL_CreateTextureFromSurface(state.renderer, text[4]);
            SDL_DestroySurface(text[4]);
        }
        if (!texture)
        {
            SDL_Log("Couldn't create text: %s\n", SDL_GetError());
            return;
        }

        SDL_GetTextureSize(texture[0], &dst[0].w, &dst[0].h);
        dst[0].x = 200;
        dst[0].y = 0;

        SDL_GetTextureSize(texture[1], &dst[1].w, &dst[1].h);
        dst[1].x = 200;
        dst[1].y = 20;

        SDL_GetTextureSize(texture[2], &dst[2].w, &dst[2].h);
        dst[2].x = 200;
        dst[2].y = 40;

        SDL_GetTextureSize(texture[3], &dst[3].w, &dst[3].h);
        dst[3].x = 200;
        dst[3].y = 60;

        SDL_GetTextureSize(texture[4], &dst[4].w, &dst[4].h);
        dst[4].x = 200;
        dst[4].y = 80;

        SDL_RenderTexture(state.renderer, texture[0], NULL, &dst[0]);
        SDL_RenderTexture(state.renderer, texture[1], NULL, &dst[1]);
        SDL_RenderTexture(state.renderer, texture[2], NULL, &dst[2]);
        SDL_RenderTexture(state.renderer, texture[3], NULL, &dst[3]);
        SDL_RenderTexture(state.renderer, texture[4], NULL, &dst[4]);

        this->inCollision = false;
    }
}