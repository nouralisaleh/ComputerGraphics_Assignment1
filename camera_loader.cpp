#include "camera_loader.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <cstdio>

using namespace glm;
using namespace std;
using namespace rapidjson;

CameraLoader::CameraLoader(const string& path)
{
    parse(path);
}

void CameraLoader::parse(const string& path)
{
    FILE* file=nullptr;
    if (fopen_s(&file,path.c_str(),"rb")!=0)
    {
        printf("Error: Cannot open camera.json\n",path.c_str());
        return;
    }

    char buffer[65536];
    FileReadStream is(file,buffer,sizeof(buffer));
    Document document;
    document.ParseStream(is);
    fclose(file);

    if(!document.IsObject())
    {
        printf("Error: Camera JSON root is not an object\n");
        return;
    }

    if(document.HasMember("position")&&document["position"].IsArray()&&document["position"].Size()==3)
    {
        auto& position=document["position"];
        camera.position =vec3(position[0].GetFloat(),position[1].GetFloat(),position[2].GetFloat());
    }
    else
    {
        printf("Error: Camera JSON missing valid 'position'.\n");
    }

    if(document.HasMember("lookAt")&&document["lookAt"].IsArray()&&document["lookAt"].Size()==3)
    {
        auto& lookAt=document["lookAt"];
        camera.lookAt=vec3(lookAt[0].GetFloat(),lookAt[1].GetFloat(),lookAt[2].GetFloat());
    }
    else
    {
        printf("Error: Camera JSON missing valid 'lookAt'.\n");
    }

    if(document.HasMember("up")&&document["up"].IsArray()&&document["up"].Size()==3)
    {
        auto& up=document["up"];
        camera.up=vec3(up[0].GetFloat(),up[1].GetFloat(),up[2].GetFloat());
    }
    else 
    {
        printf("Error: Camera JSON missing valid 'up'.\n");
    }
}
