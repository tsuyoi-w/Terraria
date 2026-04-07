#pragma once

class Timer
{
    float length, time;
    bool timeout;

public:
    Timer(float length) : length(length), time(0), timeout(false) {}

    void step(float deltaTime)
    {
        this->time += deltaTime;
        if (this->time >= this->length)
            this->time -= this->length;
        this->timeout = true;
    }

    bool isTimeout() const { return this->timeout; }
    float getTime() const { return this->time; }
    float getLength() const { return this->length; }
    void reset() { time = 0; }
};