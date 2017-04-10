//
//  LHead.cpp
//  opengl
//
//  Created by jepsonCheng on 17/3/3.
//  Copyright © 2017年 jepsonCheng. All rights reserved.
//

#include "LHead.h"

char* getFileData(const char* filePath)
{
    char* fileData = nullptr;
    FILE* pFile = fopen(filePath, "rb");
    if (pFile)
    {
        
        fseek(pFile, 0, SEEK_END);
        size_t length = ftell(pFile);
        fileData = new char[length + 1];
        rewind(pFile);
        
        fread(fileData, length, 1, pFile);
        fileData[length] = '\0';
    }
    
    fclose(pFile);
    return fileData;
}

string getFullPath(string releavePath)
{
    if (releavePath.find("ttttt/Resources/") != string::npos)
    {
        return releavePath;
    }
    return "/Users/chengjiangpo/Documents/github/ttttt/Resources/" + releavePath;
}

 struct Vertex makeVertex(GLfloat x, GLfloat y, GLfloat z)
 {
     struct Vertex ver;
     ver.x = x ;
     ver.y = y ;
     ver.z = z ;
 
     return ver;
 }
 
 struct Color makeColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
 {
     struct Color color;
     color.r = r ;
     color.g = g ;
     color.b = b ;
     color.a = a ;
     return color;
 }

 struct VertexColor makeVertexColor(struct Vertex vex,struct Color color)
{
    struct VertexColor vc;
    vc.vex      = vex;
    vc.color    = color;
    
    return vc;
}

struct TexCooor makeTexCoor(GLfloat first,GLfloat second)
{
    struct TexCooor texcood;
    texcood.texCoor[0] = first;
    texcood.texCoor[1] = second;
    
    return texcood;
}

struct Normal makeNormal(GLfloat x,GLfloat y,GLfloat z)
{
    struct Normal normal;
    normal.normal[0] = x;
    normal.normal[1] = y;
    normal.normal[2] = z;
    
    return normal;
}

struct VertexIndex makeVertexIndex(GLint posIndex,GLint texCoorIndex, GLint normalIndex)
{
    struct VertexIndex index;
    index.positionIndex = posIndex;
    index.texcoorIndex  = texCoorIndex;
    index.nomalIndex    = normalIndex;
    
    return index;
}

struct VertexInfo makeVertexInfo(Vertex vertex,Color color,TexCooor texcoor,Normal normal)
{
    VertexInfo info ;
    info.vertex     = vertex;
    info.color      = color;
    info.texCoor    = texcoor;
    info.normal     = normal;
    
    return info;
}


vector<string> splitString(string splitString,char split)
{
    vector<std::string> stringVec;
    size_t beginPos = 0, pos = 0;
    
    pos = splitString.find_first_of(split,beginPos);
    
    while(true)
    {
        string str = splitString.substr(beginPos, pos - beginPos);
        stringVec.push_back(str);
        
        if (pos == string::npos)
        {
            break;
        }
        // 查找下一个
        beginPos = pos + 1;
        pos = splitString.find_first_of(split,beginPos);
    }
    
    return stringVec;
}

vector<int>    splitStringToNum(string splitStr,char split)
{
    vector<string> splitVec = splitString(splitStr,split);
    vector<int> numVec;
    for (int i = 0; i < splitVec.size(); i++)
    {
        numVec.push_back(atoi(splitVec.at(i).c_str()));
    }
    
    return  numVec;
}

bool checkShaderError(GLint shader)
{
    char err[1024];
    int  size = 0;
    GLint compileResult = 0;
    memset(err, 0, 124);
    
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compileResult);
    
    if(compileResult != 1)
    {
        glGetShaderInfoLog(shader,1024,&size,err);
        cout<<"checkShaderError:"<<" compileResult = "<<compileResult<<" err = "<<err<<endl;
    }
    
    return true;
}
