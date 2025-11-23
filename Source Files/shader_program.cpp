#include "shader_program.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

ShaderProgram::ShaderProgram(const char* vertexShaderPath,const char* fragmentShaderPath)
{
    GLuint vertex=loadShader(vertexShaderPath,GL_VERTEX_SHADER);
    GLuint fragment=loadShader(fragmentShaderPath,GL_FRAGMENT_SHADER);

    if(!vertex||!fragment)
    {
        error=true;
        return;
    }

    program=glCreateProgram();
    glAttachShader(program,vertex);
    glAttachShader(program,fragment);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program,GL_LINK_STATUS,&success);

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program,512,NULL,infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"<<infoLog<<endl;
        error = true;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

GLuint ShaderProgram::loadShader(const char* path,GLenum type)
{
    ifstream file(path);
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open shader file: " <<path<<endl;
        return 0;
    }

    stringstream stringStream;
    stringStream<<file.rdbuf();
    string source=stringStream.str();
    const char* code=source.c_str();

    GLuint shader=glCreateShader(type);
    glShaderSource(shader,1,&code,nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        cout << "ERROR::SHADER::COMPILATION_FAILED ("
            << (type==GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << ")\n"
            << infoLog << endl;
        return 0;
    }

    return shader;
}

void ShaderProgram::use()
{
    glUseProgram(program);
}

void ShaderProgram::setMat4(const string& name, const mat4& value) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE,value_ptr(value));
}

void ShaderProgram::setVec3(const string& name, const vec3& value) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    glUniform3fv(loc,1,value_ptr(value));
}

void ShaderProgram::setFloat(const string& name, float value) const 
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    glUniform1f(loc, value);
}

void ShaderProgram::setInt(const string& name, int value) const
{
    GLint loc = glGetUniformLocation(program, name.c_str());
    glUniform1i(loc, value);
}

bool ShaderProgram::getError() { return error; }
GLuint ShaderProgram::getProgram() { return program; }
