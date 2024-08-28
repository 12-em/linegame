#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "camera.hpp"
#include <vector>
#include "gameobject.hpp"

using namespace glm;

class Game {
private:
    int windowWidth, windowHeight;
    SDL_Window* window;
    void sdlprinterr(std::string message);
    void sdlinit();
public:
    Camera* camera;
    SDL_Renderer* renderer;

    Game(int w, int h);

    void drawline(Line3D line, Transform* transform);
    void drawline(int r, int g, int b, vec2 start, vec2 end);

    void init();
    void run();
    void loop(int frame_n);
    void quit();
};