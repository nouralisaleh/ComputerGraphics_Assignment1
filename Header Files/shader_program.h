#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

using namespace std;
using namespace glm;

class ShaderProgram
{
    public:
        ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
        bool getError();
        GLuint getProgram();
        void use();
        void setMat4(const string& name, const mat4& value) const;
        void setVec3(const string& name, const vec3& value) const;
        void setFloat(const string& name, float value) const;
        void setInt(const string& name, int value) const;


    private:
        GLuint program=0;
        bool error=false;
        GLuint loadShader(const char* path,GLenum type);
};
