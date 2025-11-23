#pragma once
#include <GLFW/glfw3.h>

class Camera;
extern Camera* camera;

class InputManager
{
    public:
        static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
        static void ProcessInput(GLFWwindow* window, float deltaTime);
};