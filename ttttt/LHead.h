//
//  LHead.h
//  opengl
//
//  Created by jepsonCheng on 17/3/3.
//  Copyright © 2017年 jepsonCheng. All rights reserved.
//

#ifndef LHead_h
#define LHead_h

#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Macro.h"
#include <string>
#include <vector>

using namespace std;


const GLfloat identityMatrix[] =
{
    1.0f,0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    0.0f,0.0f,1.0f,0.0f,
    0.0f,0.0f,0.0f,1.0f
};

const glm::mat4 protectionMatrix = glm::perspective(90.0f, WINWIDTH/WINHIGH, 0.1f, 1000.0f);

struct Vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Color
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

struct VertexColor
{
    Vertex vex;
    Color color;
};

struct TexCooor
{
    float texCoor[2];
};

struct Normal
{
    float normal[3];
};

struct VertexIndex
{
    GLint positionIndex;
    GLint texcoorIndex;
    GLint nomalIndex;
};

struct VertexInfo
{
    struct Vertex       vertex;
    struct Color        color;
    struct TexCooor     texCoor;
    struct Normal       normal;
};


extern struct Vertex makeVertex(GLfloat x, GLfloat y, GLfloat z);

extern struct Color makeColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a);

extern struct VertexColor makeVertexColor(struct Vertex vex,struct Color color);

extern struct TexCooor makeTexCoor(GLfloat first,GLfloat second);

extern struct Normal makeNormal(GLfloat x,GLfloat y,GLfloat z);

extern struct VertexIndex makeVertexIndex(GLint posIndex,GLint texCoorIndex, GLint normalIndex);
extern struct VertexInfo makeVertexInfo(Vertex vertex,Color color,TexCooor texcoor, Normal normal);



char* getFileData(const char* filePath);
string getFullPath(string releavePath);


vector<string> splitString(string string,char split);

vector<int>    splitStringToNum(string splitString,char split);



bool checkShaderError(GLint shader);

#endif /* LHead_h */
