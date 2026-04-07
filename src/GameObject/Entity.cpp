#include "../../includes/GameObject/Entity.hpp"

Entity::Entity(ObjectType type) : acceleration(300), maxSpeedX(100)
{
    this->type = type;
    this->position = {0, 0};
    this->direction = 0.0f;
    this->currentAnimation = 0;
    this->dynamic = true;
    this->animations.push_back(Animation(8, 1.6f));
    this->textures[0] = "data/texture/Characters/players/idle.png";
    this->textures[1] = "data/texture/Characters/players/walking.png";
}

void Entity::movement(SDLState &state, float deltaTime, std::vector<GameObject *> layers)
{
    if (this->dynamic)
        this->velocity += glm::vec2(0, 500) * deltaTime;

    movementState newVec = input.checkAction(this->velocity, this->acceleration.x, this->maxSpeedX, deltaTime);
    this->direction = (newVec.direction == 0) ? this->direction : newVec.direction;
    switch (this->data.state)
    {
    case EntityState::idle:
        if (this->direction)
        {
            this->onStateChange(EntityState::walking);
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
            this->onStateChange(EntityState::idle);
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
        break;
    case EntityState::walking:
        this->currentAnimation = 0;
        break;
    case EntityState::running:
        this->currentAnimation = 0;
        break;
    }
}
