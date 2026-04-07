#include "../../includes/GameObject/Entity.hpp"

void Entity::update(SDLState &state, float deltaTime, std::vector<GameObject *> layers)
{
}
void Entity::checkCollision(SDLState &state, GameObject &obj, float deltaTime)
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

void Entity::collisionResponse(SDLState &state, const SDL_FRect &rectA, const SDL_FRect &rectB, const SDL_FRect &rectC, GameObject &b, float deltaTime)
{
    if (this->type == ObjectType::player)
    {
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
