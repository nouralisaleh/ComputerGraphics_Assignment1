#include "object_loader.h"
#include "shapes_factory.h"      
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <cstdio>
#include <iostream>

using namespace glm;
using namespace std;
using namespace rapidjson;

ObjectLoader::ObjectLoader(const string& path) 
{
    parse(path);
}

void ObjectLoader::parse(const string& path)
{

    FILE* file=nullptr;
    if (fopen_s(&file,path.c_str(),"rb")!=0)
    {
        printf("Error: Cannot open objects.json\n",path.c_str());
        return;
    }


    char buffer[65536];
    FileReadStream is(file,buffer,sizeof(buffer));
    Document document;
    document.ParseStream(is);
    fclose(file);

    if (!document.IsArray())
    {
        printf("Error: objects array missing in JSON.\n");
        return;
    }

    for(auto& item:document.GetArray())
    {

        ObjectData objectDate;
        objectDate.type=item.HasMember("type")&&item["type"].IsInt()?item["type"].GetInt():0;

        if(item.HasMember("position")&&item["position"].IsArray())
        {
            const auto& position=item["position"].GetArray();
            objectDate.position=vec3(position[0].GetFloat(),position[1].GetFloat(),position[2].GetFloat());
        }
        else objectDate.position=vec3(0.0f);

        if(item.HasMember("rotation")&&item["rotation"].IsArray())
        {
            const auto& rotation=item["rotation"].GetArray();
            objectDate.rotation=vec3(rotation[0].GetFloat(),rotation[1].GetFloat(),rotation[2].GetFloat());
        }
        else objectDate.rotation=vec3(0.0f);

        if(item.HasMember("scale")&&item["scale"].IsArray())
        {
            const auto& scale=item["scale"].GetArray();
            objectDate.scale=vec3(scale[0].GetFloat(),scale[1].GetFloat(),scale[2].GetFloat());
        }
        else objectDate.scale =vec3(1.0f);

        if(item.HasMember("color")&&item["color"].IsArray())
        {
            const auto& color=item["color"].GetArray();
            objectDate.color=vec3(color[0].GetFloat(),color[1].GetFloat(),color[2].GetFloat());
        }
        else objectDate.color=vec3(1.0f); 

        objects.push_back(objectDate);
    }

}

vector<Model*> ObjectLoader::CreateModels()
{
    vector<Model*> models;

    for(auto& obj:objects)
    {
        Transform transform;
        transform.position=obj.position;
        transform.rotation=obj.rotation;
        transform.scale=obj.scale;
        vector<vec3> faceColors;
        faceColors.resize(8,obj.color);
       
        Model* model=ShapesFactory::Create(obj.type,transform,faceColors);
        if (model) models.push_back(model);
    }
    return models;
}
