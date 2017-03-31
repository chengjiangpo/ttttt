//
//  firstGPUProgram.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-3-24.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "firstGPUProgram.h"

firstGPUProgram::firstGPUProgram()
{
    
}

firstGPUProgram::~firstGPUProgram()
{
    
}

void firstGPUProgram::initOpenGl()
{
    // 1、清理背景颜色
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // 2、开启深度测试
    glEnable(GL_DEPTH_TEST);
    
    // 3、初始化投影矩阵
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // 设置透视投影相关信息
    gluPerspective(90, WINWIDTH/WINHIGH, 0.1f, 1000.0f);

    // 4、初始化模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void firstGPUProgram::runDraw()
{
    // 1、关闭深度测试
    glDisable(GL_DEPTH_TEST);
    
    // 2、 还原模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    // 3、还原投影矩阵
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    
    // 4、关闭光照
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    // 切换两个缓冲区
    glutSwapBuffers();
}


void firstGPUProgram::draw()
{
    initOpenGl();
    initLight();
    
    Color color1 = makeColor(1.0f, 1.0f, 1.0f,0.5f);
    Color color2 = makeColor(1.0f, 0.0f, 0.0f, 1.0f);
    setMaterialColor(&color1, &color2);
    
    
    // 创建三角形1
    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex3f(50.0f, 0.0f, -100.0f);
    
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex3f(0.0f, 50.0f, -100.0f);
    glEnd();

    Color color3 = makeColor(0.0f, 1.0f, 0.0f, 0.2f);
    Color color4 = makeColor(0.0f, 0.0f, 1.0f, 1.0f);
    setMaterialColor(&color3, &color4);
    // 创建三角形2
    glBegin(GL_TRIANGLES);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-50.0f, -50.0f, -100.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-50.0f, 0.0f, -100.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -50.0f, -100.0f);

    glEnd();
    

    
    
    runDraw();
    
}

void firstGPUProgram::initLight()
{
    // 1、开启光照
    glEnable(GL_LIGHTING);
    
    
    // 2、 开启0号光源
    glEnable(GL_LIGHT0);
    
    // 3、设置0号光源相关信息
    GLfloat ambientColor[] = {1.0f,0.0f,0.0f,0.3f};
    GLfloat diffuseColor[] = {0.0f,0.0f,1.0f,0.8f};
    GLfloat specularColor[]   = {0.0,1.0f,1.0f,1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
    
    // 设置光源的位置
    GLfloat lightPos[] = {0.0f,0.0f,0.0f,1.0f}; // 第四个参数为0表示光源在无限远的地方,否则为位置光源
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    // 设置光照的方向，聚合度等，cutoff表示光源发散角度的一半
    GLfloat direction[] = {0.0f,0.0f,-1.0f};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
    
    
    // 设置全局环境光  glLightModel
    GLfloat gloabAmbient[] = {0.5,0.5,0.5,0.5};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gloabAmbient);
    
    // 设置是否是近距离观看
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    
    
//    glDisable(GL_LIGHTING);
//    glDisable(GL_LIGHT0);
}


void firstGPUProgram::setMaterialColor(Color* amibentColor,Color* specularColor)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,(GLfloat* )amibentColor);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat* )specularColor);
    
}



















