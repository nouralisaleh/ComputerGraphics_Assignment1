#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "input_manager.h"
#include "object_loader.h"
#include "shapes_factory.h"
#include "shader_program.h"
#include "camera_loader.h"
#include <vector>

using namespace glm;

int main()
{
    if (!glfwInit()) return -1;

    GLFWwindow* window=glfwCreateWindow(1920,1080,"Computer Graphics Assignment1",nullptr,nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glewInit();

    glfwSetCursorPosCallback(window, InputManager::MouseCallback);
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);

    // --- Load camera ---
    CameraLoader camLoader("assets/camera.json");
    Camera cam(camLoader.getCamera().position,
    camLoader.getCamera().lookAt,
    camLoader.getCamera().up);
    camera = &cam;

    // --- Load objects ---
    ObjectLoader loader("assets/objects.json");
    std::vector<Model*> models = loader.CreateModels();

    // --- Load shader ---
    ShaderProgram shader("assets/shaders/shader.vert", "assets/shaders/shader.frag");
    if (shader.getError()) return -1;

    while (!glfwWindowShouldClose(window))
    {
        float deltaTime = 0.016f; 
        InputManager::ProcessInput(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        shader.use();
        mat4 view = camera->GetViewMatrix();
        mat4 perspective = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        for (auto model : models)
        {
            mat4 modelMatrix = model->getModelMatrix();
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, &modelMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "view"), 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "perspective"), 1, GL_FALSE, &perspective[0][0]);

            model->draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
