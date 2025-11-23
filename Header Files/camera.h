#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
    public:
        vec3 Position;
        vec3 Front;
        vec3 Up;
        vec3 Right;
        vec3 WorldUp;

        float Yaw;
        float Pitch;
        float MovementSpeed;
        float MouseSensitivity;

        Camera(vec3 position, vec3 lookAt, vec3 up);

        mat4 GetViewMatrix();

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset);

    private:
        void updateCameraVectors();
};

