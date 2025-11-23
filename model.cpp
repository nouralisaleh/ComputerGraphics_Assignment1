#include "model.h"

Model::Model(const vector<vec3>& positions,const vector<vec3>& colors,const Transform& transform):transform(transform) 
{
    verticesCount=positions.size();
    vector<float> data;
    data.reserve(verticesCount*6);

    for (size_t i=0;i<verticesCount;i++)
    {
        vec3 position=positions[i];
        vec3 color=colors.size()>i?colors[i]:vec3(1.0f);

        data.push_back(position.x);
        data.push_back(position.y);
        data.push_back(position.z);

        data.push_back(color.x);
        data.push_back(color.y);
        data.push_back(color.z);
    }

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*data.size(),data.data(),GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
  
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Model::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,verticesCount);
}

mat4 Model::getModelMatrix()const
{
    mat4 model=mat4(1.0f);
    model=translate(model,transform.position);
    model=rotate(model,radians(transform.rotation.x),vec3(1, 0, 0));
    model=rotate(model,radians(transform.rotation.y),vec3(0, 1, 0));
    model=rotate(model,radians(transform.rotation.z),vec3(0, 0, 1));
    model=scale(model,transform.scale);
    return model;
}
