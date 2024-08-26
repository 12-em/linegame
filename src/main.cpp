#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "game.hpp"

void sdlprinterr(std::string message) {
    std::cerr << message << SDL_GetError() << std::endl;
}

int main() {
    std::cout << "linegame 0.0.1" << std::endl;

    Game game(800, 600);
}