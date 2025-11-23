#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

using namespace glm;

Camera::Camera(vec3 position,vec3 lookAt,vec3 up)
{
    Position=position;
    WorldUp=up;
    Front=normalize(lookAt-position);
    Yaw=degrees(atan2(Front.x, Front.z));
    Pitch=degrees(asin(Front.y));
    MovementSpeed= 0.5f;
    MouseSensitivity= 0.1f;

    updateCameraVectors();
}

mat4 Camera::GetViewMatrix()
{
    return lookAt(Position, Position+Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity= MovementSpeed * deltaTime;

    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    vec3 front;

    front.x = cos(radians(Pitch)) * sin(radians(Yaw));
    front.y = sin(radians(Pitch));
    front.z = cos(radians(Pitch)) * cos(radians(Yaw));

    Front =normalize(front);
    Right =normalize(cross(Front, WorldUp));
    Up =normalize(cross(Right, Front));
}