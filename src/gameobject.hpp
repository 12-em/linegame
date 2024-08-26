#include <glm/glm.hpp>
#include <vector>

using namespace glm;

struct Line3D {
    vec3 start, end;
};

class Transform {
private:
    mat4 translation, scale, rotationX, rotationY, rotationZ;

    void setRotationX(float angle) {
        rotationX[1][1] = std::cos(angle);
        rotationX[2][1] = -std::sin(angle);
        rotationX[1][2] = std::sin(angle);
        rotationX[2][2] = std::cos(angle);
    }
    void setRotationY(float angle) {
        rotationY[0][0] = std::cos(angle);
        rotationY[2][0] = std::sin(angle);
        rotationY[0][2] = -std::sin(angle);
        rotationY[2][2] = std::cos(angle);
    }
    void setRotationZ(float angle) {
        rotationZ[0][0] = std::cos(angle);
        rotationZ[1][0] = -std::sin(angle);
        rotationZ[0][1] = std::sin(angle);
        rotationZ[1][1] = std::cos(angle);
    }

    mat4 getRotationMatrix() {
        return rotationZ * rotationY * rotationX;
    }
public:
    Transform() : Transform(vec3(), vec3(), vec3(1,1,1)) {}

    Transform(vec3 position, vec3 eulerAngles, vec3 scale) {
        translation = mat4(1.0f);
        rotationX = mat4(1.0f);
        rotationY = mat4(1.0f);
        rotationZ = mat4(1.0f);
        this->scale = mat4(1.0f);

        setPosition(position);
        setEulerAngles(eulerAngles);
        setScale(scale);
    }
    mat4 getModelMatrix() {
        return translation * getRotationMatrix() * scale;
    }

    vec3 localToWorld(vec3 point) {
        vec4 point4 = vec4(point.x, point.y, point.z, 1);
        vec4 world4 = getModelMatrix() * point4;
        return vec3(world4.x, world4.y, world4.z);
    }

    void setPosition(vec3 position) {
        translation[3][0] = position.x;
        translation[3][1] = position.y;
        translation[3][2] = position.z;
    }
    void setEulerAngles(vec3 angles) {
        setRotationX(angles.x);
        setRotationY(angles.y);
        setRotationZ(angles.z);
    }
    void setScale(vec3 scale) {
        this->scale[0][0] = scale.x;
        this->scale[1][1] = scale.y;
        this->scale[2][2] = scale.z;
    }

    ~Transform() {}
};