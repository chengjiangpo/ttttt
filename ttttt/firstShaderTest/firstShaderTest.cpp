//
//  firstShaderTest.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-3-26.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "firstShaderTest.h"

firstShaderTest::firstShaderTest()
{
    
}

firstShaderTest::~firstShaderTest()
{
    
}

void firstShaderTest::init()
{
    glewInit();

}

void firstShaderTest::draw()
{
    init();
    
    GLint program = createGPUProgram();
    
    GLuint vbo = createVBO();
    
    glUseProgram(program);
    
    setShaderPargram(program,vbo);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glutSwapBuffers();
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

GLint firstShaderTest::createGPUProgram()
{
    GLint program = 0;
    
    GLint vsShader = glCreateShader(GL_VERTEX_SHADER);
    GLint fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    string vsPath = getFullPath("/Shader/firstVertexShader.txt");
    string fsPath = getFullPath("/Shader/firstFrameShader.txt");
    char* vsCode = getFileData(vsPath.c_str());
    char* fsCode = getFileData(fsPath.c_str());
    
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


GLuint firstShaderTest::createVBO()
{
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    
    VertexColor* vc = setVertexInfo();
    glBufferData(GL_ARRAY_BUFFER,sizeof(VertexColor)*3,vc,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    return vbo;
    
}

void firstShaderTest::setShaderPargram(GLint program,GLuint vbo)
{
    // 获取各个属性在shader中的地址
    GLint posLocation,colorLocation,MLocaktion,VLocation,PLocation;
    
    posLocation = glGetAttribLocation(program,"pos");
    colorLocation = glGetAttribLocation(program,"color");
    
    MLocaktion = glGetUniformLocation(program,"M");
    VLocation  = glGetUniformLocation(program,"V");
    PLocation  = glGetUniformLocation(program,"P");
    
    
    // 设置矩阵相关信息
    glm::mat4 protectionMatrix = glm::perspective(90.0f, WINWIDTH/WINHIGH, 0.1f, 1000.0f);
    glUniformMatrix4fv(MLocaktion,1,GL_FALSE,identityMatrix);
        glUniformMatrix4fv(VLocation,1,GL_FALSE,identityMatrix);
    glUniformMatrix4fv(PLocation,1,GL_FALSE,glm::value_ptr(protectionMatrix));
    
    // 设置顶点坐标和颜色
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    // 默认情况下，所有的顶点着色器的属性（Attribute）都是关闭的，glEnableVertexAttribArray可以开启对应的属性
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(posLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexColor),nullptr);
    
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexColor),(void*)(sizeof(GL_FLOAT)*3));
}

VertexColor* firstShaderTest::setVertexInfo()
{
    VertexColor* vc = new VertexColor[3];
    vc[0] = makeVertexColor(makeVertex(0.0f, 0.0f, -100.0f), makeColor(1.0f, 0.0f, 0.0f, 1.0f));
    
    vc[1] = makeVertexColor(makeVertex(0.0f, 50.0f, -100.0f),makeColor(0.0f, 1.0f, 0.0f, 1.0f));
    
    vc[2] = makeVertexColor(makeVertex(50.0f, 0.0f, -100.0f), makeColor(0.0f, 0.0f, 1.0f, 1.0f));
    
    
    return vc;
}







