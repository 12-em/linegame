#include<vector>
#include<glm/glm.hpp>
#include "game.hpp"

using namespace glm;

void Game::drawline(Line3D line, Transform* transform) {
        vec3 pos1 = transform->localToWorld(line.start);
        vec3 pos2 = transform->localToWorld(line.end);
        vec2 p1 = this->camera->worldToScreen(pos1);
        vec2 p2 = this->camera->worldToScreen(pos2);

        this->drawline(line.r, line.g, line.b, p1, p2);
}


void Game::sdlprinterr(std::string message) {
    std::cerr << message << SDL_GetError() << std::endl;
}


void Game::sdlinit() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        sdlprinterr("SDL init error: ");
    }

    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    window = SDL_CreateWindow(
        "linegame 0.0.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_OPENGL
    );

    if(!window) {
        sdlprinterr("Window creation error: ");
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) {
        sdlprinterr("Renderer creation error: ");
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

Game::Game(int w, int h) {
    this->windowWidth = w;
    this->windowHeight = h;

    camera = new Camera(45.0f, glm::vec2(w, h));
    init();
}

void Game::init() {
    sdlinit();

    camera->setPosition(glm::vec3(0,0,-10));
    camera->lookAt(glm::vec3(0,0,1));

    run();
}

void Game::run() {
    int frame = 0;
    bool shouldQuit = false;
    SDL_Event event;
    while(!shouldQuit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                shouldQuit = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

        loop(frame);

        SDL_RenderPresent(renderer);

        frame++;
    }

    quit();
}

void Game::loop(int frame_n) {

    GameObject go;

    go.lines.push_back(Line3D(255,255,255, glm::vec3(-1,-1,1), glm::vec3(1,-1,1)));
    go.lines.push_back(Line3D(255,255,255, vec3(-1,-1,1), vec3(-1, -1, -1)));
    go.lines.push_back(Line3D(255,255,255, glm::vec3(-1,-1,-1), glm::vec3(1,-1,-1)));
    go.lines.push_back(Line3D(255,255,255, vec3(1,-1,-1), vec3(1, -1, 1)));

    go.lines.push_back(Line3D(255,255,255, glm::vec3(-1,1,1), glm::vec3(1,1,1)));
    go.lines.push_back(Line3D(255,255,255, vec3(-1,1,1), vec3(-1, 1, -1)));
    go.lines.push_back(Line3D(255,255,255, glm::vec3(-1,1,-1), glm::vec3(1,1,-1)));
    go.lines.push_back(Line3D(255,255,255, vec3(1,1,-1), vec3(1, 1, 1)));

    go.lines.push_back(Line3D(255,255,255, glm::vec3(-1,-1,1), glm::vec3(-1,1,1)));
    go.lines.push_back(Line3D(255,255,255, vec3(1,1,1), vec3(1, -1, 1)));
    go.lines.push_back(Line3D(255,255,255, glm::vec3(-1,1,-1), glm::vec3(-1,-1,-1)));
    go.lines.push_back(Line3D(255,255,255, vec3(1,1,-1), vec3(1, -1, -1)));
    go.transform.setPosition(glm::vec3(0,0,-1));
    go.transform.setScale(glm::vec3(std::sin(frame_n*0.05f)*0.5f+1, std::sin(frame_n*0.05f)*0.5f+1, std::sin(frame_n * 0.05f)*0.5f+1));
    go.transform.setEulerAngles(glm::vec3(frame_n*0.05f, frame_n*0.05f, frame_n*0.05f));
    go.draw(this);
}

void Game::quit() {
    delete camera;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::drawline(int r, int g, int b, glm::vec2 start, glm::vec2 end) {
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
}