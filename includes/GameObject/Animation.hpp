#pragma once
#include "Timer.hpp"

class Animation
{
    Timer timer;
    unsigned int frameCount;

public:
    Animation();
    Animation(unsigned int frameCount, float length);

    float getLength() const;
    int currentFrame() const;

    void step(float);
};
