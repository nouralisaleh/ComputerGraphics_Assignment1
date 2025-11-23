#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "model.h"

using namespace std;
using namespace glm;


class ShapesFactory
{
    public:
        static Model* Create(int type,const Transform& transform, const vector<vec3>& faceColors);

    private:
        static void BuildCube(vector<vec3>& position, vector<vec3>& color, const vector<vec3>& faceColors);
        static void BuildPyramid(vector<vec3>& position, vector<vec3>& color, const vector<vec3>& faceColors);
        static void BuildHexagonPrism(vector<vec3>& position, vector<vec3>& color, const vector<vec3>& faceColors);
};
