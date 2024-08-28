#include "gameobject.hpp"
#include "game.hpp"

GameObject::GameObject() {}

void GameObject::draw(Game* game) {
    for (int i = 0; i < lines.size(); i++)
    {
        game->drawline(lines.at(i), &transform);
    }
}

GameObject::~GameObject() {}