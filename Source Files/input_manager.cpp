#include "input_manager.h"
#include "camera.h"
#include <GLFW/glfw3.h>

Camera* camera = nullptr;

void InputManager::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    static float lastX = 0.0f;
    static float lastY = 0.0f;

    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
        return;  
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;

    lastX = (float)xpos;
    lastY = (float)ypos;

    if (camera) camera->ProcessMouseMovement(xoffset, yoffset);
}

void InputManager::ProcessInput(GLFWwindow* window, float deltaTime)
{
    if (!camera) return;
    float speed = deltaTime;

    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

    if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, speed);

    if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, speed);

    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
        camera->ProcessKeyboard(LEFT,speed);

    if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT,speed);
}
