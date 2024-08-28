#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera {
private:
    glm::mat4 projection, view;
    glm::vec2 windowSize;
    glm::vec3 position, lookAtTarget;

    glm::mat4 getTransformationMatrix() {
        return projection * view;
    }
public:
    Camera(float fov, glm::vec2 windowSize) {
        this->position = glm::vec3();
        this->lookAtTarget = glm::vec3(0,0,1);
        this->windowSize = windowSize;
        projection = glm::perspective(fov, ((float) windowSize.x / (float) windowSize.y), 0.1f, 100.0f);
        view = glm::lookAt(position, glm::vec3(0,0,1), glm::vec3(0,1,0));
    }

    void setPosition(glm::vec3 newPosition) {
        position = newPosition;
        view = glm::lookAt(position, lookAtTarget, glm::vec3(0,-1,0));
    }

    void lookAt(glm::vec3 target) {
        lookAtTarget = target;
        view = glm::lookAt(position, lookAtTarget, glm::vec3(0,-1,0));
    }

    glm::vec2 worldToScreen(glm::vec3 point) {
        glm::vec4 pos = glm::vec4(point.x, point.y, point.z, 1);

        pos = getTransformationMatrix() * pos;

        glm::vec3 ndc = glm::vec3(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w);

        return glm::vec2((ndc.x + 1) / 2 * windowSize.x, 
            (ndc.y + 1) / 2 * windowSize.y);
    }

    ~Camera() {}
};