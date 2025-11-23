#pragma once
#include <string>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

struct CameraData
{
    vec3 position;
    vec3 lookAt;
    vec3 up;
};

class CameraLoader
{
    public:
        CameraLoader(const string& path);
        CameraData getCamera() const { return camera; }

    private:
        CameraData camera;
        void parse(const string& path);
};