#pragma once

#include "transform.hpp"
#include <vector>

class Game;

class GameObject {
public:
    std::vector<Line3D> lines;
    Transform transform;

    GameObject();

    void draw(Game* game);

    ~GameObject();
};