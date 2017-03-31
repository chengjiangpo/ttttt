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
    vc.vex = vex;
    vc.color = color;
    
    return vc;
}
