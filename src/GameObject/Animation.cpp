#include "../../includes/GameObject/Animation.hpp"

Animation::Animation() : timer(0), frameCount(0) {}

Animation::Animation(unsigned int frameCount, float length) : frameCount(frameCount), timer(length) {}

float Animation::getLength() const { return this->timer.getLength(); }

int Animation::currentFrame() const
{
    return static_cast<int>(this->timer.getTime() / this->timer.getLength() * this->frameCount);
}

void Animation::step(float deltaTime)
{
    this->timer.step(deltaTime);
}