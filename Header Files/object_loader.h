#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "model.h"


using namespace glm;
using namespace std;

struct ObjectData
{
    int type;
    vec3 position;
    vec3 rotation;     
    vec3 scale;          
    vec3 color;
};

class ObjectLoader
{
    public:
        ObjectLoader(const string& path);
        const vector<ObjectData>& getObjects() const { return objects; }
        vector<Model*> CreateModels();

    private:
        vector<ObjectData> objects;
        void parse(const string& path);
};