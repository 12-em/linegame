#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "camera.hpp"

class Game {
private:
    int windowWidth, windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Camera* camera;

    void sdlprinterr(std::string message) {
        std::cerr << message << SDL_GetError() << std::endl;
    }


    void sdlinit() {
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

    void drawline(int r, int g, int b, glm::vec2 start, glm::vec2 end) {
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }
public:
    Game(int w, int h) {
        this->windowWidth = w;
        this->windowHeight = h;

        camera = new Camera(45.0f, glm::vec2(w, h));
        init();
    }

    void init() {
        sdlinit();

        camera->setPosition(glm::vec3(0,0,-10));
        camera->lookAt(glm::vec3(0,0,1));

        run();
    }

    void run() {
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

    void loop(int frame_n) {
        float camNewX = std::sin(frame_n * 0.01f);
        float camNewZ = std::cos(frame_n * 0.01f);
        glm::vec3 camNewPos = glm::vec3(camNewX, 2, camNewZ);
        camera->setPosition(camNewPos);
        camera->lookAt(glm::vec3());

        glm::vec3 pos1 = glm::vec3();
        glm::vec3 pos2 = glm::vec3(1,0,0);
        glm::vec3 pos3 = glm::vec3(0,1,0);
        glm::vec3 pos4 = glm::vec3(0,0,1);

        glm::vec2 p1 = camera->worldToScreen(pos1);
        glm::vec2 p2 = camera->worldToScreen(pos2);
        glm::vec2 p3 = camera->worldToScreen(pos3);
        glm::vec2 p4 = camera->worldToScreen(pos4);

        drawline(255,0,0, p1, p2);
        drawline(0,255,0, p1, p3);
        drawline(0,0,255, p1, p4);
    }

    void quit() {
        delete camera;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    ~Game() {}
};