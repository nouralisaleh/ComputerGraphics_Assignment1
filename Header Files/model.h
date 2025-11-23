#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

using namespace glm;
using namespace std;

struct Transform
{
    vec3 position;
    vec3 rotation;
    vec3 scale;
};

class Model
{
    public:
        Model(const vector<vec3>& vertices, const vector<vec3>& colors, const Transform& transform);
        void draw();
        mat4 getModelMatrix() const;

    private:
        GLuint VAO;
        GLuint VBO;
        unsigned int verticesCount;
        Transform transform;
};
