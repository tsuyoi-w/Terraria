#pragma once
#include "Timer.hpp"

class Animation
{
    Timer timer;
    unsigned int frameCount;

public:
    Animation() : timer(0), frameCount(0) {}
    Animation(unsigned int frameCount, float length) : frameCount(frameCount), timer(length) {}

    float getLength() const { return this->timer.getLength(); }
    int currentFrame() const
    {
        return static_cast<int>(this->timer.getTime() / this->timer.getLength() * this->frameCount);
    }

    void step(float deltaTime)
    {
        this->timer.step(deltaTime);
    }
};
