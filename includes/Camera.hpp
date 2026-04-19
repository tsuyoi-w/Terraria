#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    glm::vec2 pos = {0, 0};

public:
    Camera() {}

    inline void set(float a) { this->pos.x += a; }
};