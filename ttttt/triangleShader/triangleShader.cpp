//
//  triangleShader.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-3-27.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "triangleShader.h"

triangleShader::triangleShader()
{
    
}

triangleShader::~triangleShader()
{
    
}

void triangleShader::init()
{
    // 初始化glew
    glewInit();
    
    // 清理背影颜色
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
}

GLint triangleShader::initProgram()
{
    GLint program;
    GLint vsShader = glCreateShader(GL_VERTEX_SHADER);
    GLint fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    string vsFilePath = getFullPath("Shader/firstVertexShader.txt");
    string fsFilePath = getFullPath("Shader/firstFrameShader.txt");
    
    char* vsCode = getFileData(vsFilePath.c_str());
    char* fsCode = getFileData(fsFilePath.c_str());
    
    glShaderSource(vsShader,1,&vsCode,nullptr);
    glShaderSource(fsShader,1,&fsCode,nullptr);
    
    glCompileShader(vsShader);
    glCompileShader(fsShader);
    
    program = glCreateProgram();
    
    glAttachShader(program,vsShader);
    glAttachShader(program,fsShader);
    
    glLinkProgram(program);
    
    glDetachShader(program,vsShader);
    glDetachShader(program,fsShader);
    
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    
    return program;
}


GLuint triangleShader::createVBO(size_t length,void* pInfo)
{
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,length,pInfo,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    return vbo;
}


GLuint triangleShader::createIBO()
{
    GLint index[] = {0,1,2,3};
    
    GLuint ibo;
    glGenBuffers(1,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    return ibo;
}

VertexColor* triangleShader::createVertexInfos(GLint& length)
{
    VertexColor* vc = new VertexColor[length];
    vc[0] = makeVertexColor(makeVertex(0.0f, 0.0f, -100.0f), makeColor(1.0f, 0.0f, 0.0f, 1.0f));
    
    vc[1] = makeVertexColor(makeVertex(0.0f, 50.0f, -100.0f), makeColor(0.0f, 1.0f, 0.0f, 1.0f));
    
    vc[2] = makeVertexColor(makeVertex(50.0f, 0.0f, -100.0f), makeColor(0.0f, 0.0f, 1.0f, 1.0f));
    
    vc[3] = makeVertexColor(makeVertex(50.0f, 50.0f, -100.0f), makeColor(1.0f, 1.0f, 1.0f, 1.0f));
    
    return  vc;
}

void triangleShader::setShaderInfo(GLint program,GLuint vbo,GLuint ibo)
{
    glUseProgram(program);
    
    GLint posLocation,colorLocation,MLocation,VLocation,PLocation;
    posLocation = glGetAttribLocation(program,"pos");
    colorLocation = glGetAttribLocation(program,"color");
    
    MLocation = glGetUniformLocation(program,"M");
    VLocation = glGetUniformLocation(program,"V");
    PLocation = glGetUniformLocation(program,"P");
    
    //  初始化矩阵信息
    glUniformMatrix4fv(MLocation,1,GL_FALSE,identityMatrix);
    glUniformMatrix4fv(VLocation,1,GL_FALSE,identityMatrix);
    glUniformMatrix4fv(PLocation,1,GL_FALSE,glm::value_ptr(protectionMatrix));
    
    // 初始化顶点的坐标信息和颜色信息
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(posLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexColor),(void*)0);
    
//    glEnableVertexAttribArray(colorLocation);
//    glVertexAttribPointer(colorLocation,4,GL_FLOAT,GL_FALSE,sizeof(VertexColor),(void*)(sizeof(GLfloat)*3));
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(GLuint)*0));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );
    
//    glBindBuffer(GL_ARRAY_BUFFER,vbo);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glBindBuffer(GL_ARRAY_BUFFER,0);
    glUseProgram(0);
    
    glutSwapBuffers();
    
}

void triangleShader::draw()
{
    init();
    
    
    GLint vertexNum = 4;
    VertexColor* vc = createVertexInfos(vertexNum);
    
    GLint program = initProgram();
    GLuint vbo = createVBO(sizeof(VertexColor)*vertexNum,vc);
    GLuint ibo = createIBO();
    
//    glBindBuffer(GL_ARRAY_BUFFER,vbo);
//    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(VertexColor)*vertexNum,vc);
//    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    setShaderInfo(program,vbo,ibo);
    
    
    delete [] vc;
}


