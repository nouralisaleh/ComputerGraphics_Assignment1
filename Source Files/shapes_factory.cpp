#include "shapes_factory.h"

using namespace std;
using namespace glm;

// ================== Cube ==================
void ShapesFactory::BuildCube(vector<vec3>& vertices,vector<vec3>& colors,const vector<vec3>& faceColors)
{
    vec3 p0(-0.5f, -0.5f, -0.5f);
    vec3 p1(0.5f, -0.5f, -0.5f);
    vec3 p2(0.5f, 0.5f, -0.5f);
    vec3 p3(-0.5f, 0.5f, -0.5f);
    vec3 p4(-0.5f, -0.5f, 0.5f);
    vec3 p5(0.5f, -0.5f, 0.5f);
    vec3 p6(0.5f, 0.5f, 0.5f);
    vec3 p7(-0.5f, 0.5f, 0.5f);

    auto pushFace=[&](vec3 a,vec3 b,vec3 c,vec3 d,vec3 color) 
        {
            vertices.push_back(a); vertices.push_back(b); vertices.push_back(c);
            colors.push_back(color); colors.push_back(color); colors.push_back(color);
            vertices.push_back(a); vertices.push_back(c); vertices.push_back(d);
            colors.push_back(color); colors.push_back(color); colors.push_back(color);
        };
   
    pushFace(p0, p1, p2, p3, faceColors[0]);
    pushFace(p5, p4, p7, p6, faceColors[1]);
    pushFace(p4, p0, p3, p7, faceColors[2]);
    pushFace(p1, p5, p6, p2, faceColors[3]);
    pushFace(p3, p2, p6, p7, faceColors[4]);
    pushFace(p4, p5, p1, p0, faceColors[5]);
}

// ================== Pyramid ==================
void ShapesFactory::BuildPyramid(vector<vec3>& vertices,vector<vec3>& colors,const vector<vec3>& faceColors)
{
    vec3 top(0.0f, 0.5f, 0.0f);
    vec3 p0(-0.5f, -0.5f, -0.5f);
    vec3 p1(0.5f, -0.5f, -0.5f);
    vec3 p2(0.5f, -0.5f, 0.5f);
    vec3 p3(-0.5f, -0.5f, 0.5f);

    auto pushTri=[&](vec3 a,vec3 b,vec3 c,vec3 color)
        {
        vertices.push_back(a); vertices.push_back(b); vertices.push_back(c);
        colors.push_back(color); colors.push_back(color); colors.push_back(color);
        };

    vertices.push_back(p0); vertices.push_back(p1); vertices.push_back(p2);
    vertices.push_back(p0); vertices.push_back(p2); vertices.push_back(p3);
    colors.insert(colors.end(), 6, faceColors[0]); 

    pushTri(p0, p1, top, faceColors[1]);
    pushTri(p1, p2, top, faceColors[2]);
    pushTri(p2, p3, top, faceColors[3]);
    pushTri(p3, p0, top, faceColors[4]);
}

// ================== Hexagon Prism ==================
void ShapesFactory::BuildHexagonPrism(vector<vec3>& vertices, vector<vec3>& colors, const vector<vec3>& faceColors)
{
    float h= 0.5f; 
    float r= 0.5f; 
    vector<vec3> topVerts, bottomVerts;

    for (int i = 0; i < 6; i++)
    {
        float angle = i * glm::radians(60.0f);
        float x = r * cos(angle);
        float z = r * sin(angle);
        topVerts.push_back(vec3(x, h, z));
        bottomVerts.push_back(vec3(x, -h, z));
    }

    vec3 topColor = (0 < faceColors.size()) ? faceColors[0] : vec3(1.0f);
    vec3 bottomColor = (1 < faceColors.size()) ? faceColors[1] : topColor;


    for (int i = 0; i < 6; i++) 
    {
        int next = (i + 1) % 6;
        vertices.push_back(topVerts[i]); vertices.push_back(topVerts[next]); vertices.push_back(topVerts[0]);
        colors.push_back(faceColors[0]); colors.push_back(faceColors[0]); colors.push_back(faceColors[0]);

        vertices.push_back(bottomVerts[i]); vertices.push_back(bottomVerts[next]); vertices.push_back(bottomVerts[0]);
        colors.push_back(faceColors[1]); colors.push_back(faceColors[1]); colors.push_back(faceColors[1]);
        
        vertices.push_back(bottomVerts[i]); vertices.push_back(bottomVerts[next]); vertices.push_back(topVerts[next]);
        vertices.push_back(bottomVerts[i]); vertices.push_back(topVerts[next]); vertices.push_back(topVerts[i]);
        colors.insert(colors.end(), 6, faceColors[2 + i % 4]); 
    }
}

Model* ShapesFactory::Create(int type,const Transform& transform,const vector<vec3>& faceColors)
{
    vector<vec3> position;
    vector<vec3> color;
    
    switch (type)
    {
    case 1:
        BuildCube(position,color,faceColors);
        break;

    case 2:
        BuildPyramid(position,color,faceColors);
        break;

    case 3:
        BuildHexagonPrism(position,color,faceColors);
        break;

    default:
        return nullptr;
    }

    return new Model(position,color,transform);
}
