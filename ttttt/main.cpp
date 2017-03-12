//
//  main.cpp
//  ttttt
//
//  Created by jepsonCheng on 17/3/3.
//  Copyright © 2017年 jepsonCheng. All rights reserved.
//

#include <iostream>
#include "LHead.h"
#include "math.h"
#include <unistd.h>
static GLfloat GL_PI = 3.14159f;
//篝火图像
GLubyte fire[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01, 0xf0,
    0x00, 0x00, 0x07, 0xf0, 0x0f, 0x00, 0x1f, 0xe0,
    0x1f, 0x80, 0x1f, 0xc0, 0x0f, 0xc0, 0x3f, 0x80,
    0x07, 0xe0, 0x7e, 0x00, 0x03, 0xf0, 0xff, 0x80,
    0x03, 0xf5, 0xff, 0xe0, 0x07, 0xfd, 0xff, 0xf8,
    0x1f, 0xfc, 0xff, 0xe8, 0xff, 0xe3, 0xbf, 0x70,
    0xde, 0x80, 0xb7, 0x00, 0x71, 0x10, 0x4a, 0x80,
    0x03, 0x10, 0x4e, 0x40, 0x02, 0x88, 0x8c, 0x20,
    0x05, 0x05, 0x04, 0x40, 0x02, 0x82, 0x14, 0x40,
    0x02, 0x40, 0x10, 0x80, 0x02, 0x64, 0x1a, 0x80,
    0x00, 0x92, 0x29, 0x00, 0x00, 0xb0, 0x48, 0x00,
    0x00, 0xc8, 0x90, 0x00, 0x00, 0x85, 0x10, 0x00,
    0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00
};

static void drawPolygons()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//    glColor3f(1.0f, 1.0f, 0.0f);
    // 开启深度测试
//    glEnable(GL_DEPTH_TEST);
//    glMatrixMode(GL_PROJECTION);    // 设置投影模式
//    gluPerspective(90.0f, 1.0f, 0, 800.0f);
//    glMatrixMode(GL_MODELVIEW);
    // 光照
    // 开启光照
    glEnable(GL_LIGHTING);
    
    GLfloat ambientLight[] = {0.3,0.3,0.3,1.0f};
    GLfloat diffuseLight[] = {0.7,0.7,0.7,1.0f};
    GLfloat shiningLight[] = {1.0f,0.0f,0.0f,1.0f};
    
    GLenum lightType = GL_LIGHT0;
    glLightfv(lightType, GL_AMBIENT, ambientLight);     // 环境光
    glLightfv(lightType, GL_DIFFUSE, diffuseLight);     // 漫反色光
    glLightfv(lightType, GL_SPECULAR, shiningLight);   // 镜面光
    glEnable(lightType);
    GLfloat lightPos[] = {0,0.0f,-50,1.0f};
    glLightfv(lightType, GL_POSITION, lightPos);        // 光源位置
    
    // 设置聚光灯效果
    // 1、设置光照的方向
    GLfloat direction[] = { 0.0f,-1.0f,0.5f};
    glLightfv(lightType, GL_SPOT_DIRECTION, direction);
    
    // 2、设置光照的聚光度
    GLfloat exponent = 1.0f;
    glLightfv(lightType, GL_SPOT_EXPONENT, &exponent);
    
    // 3、设置光照角度
    GLfloat cutoff = 180;
    glLightfv(lightType, GL_SPOT_CUTOFF, &cutoff);
    
    // 设置全局的环境光强度
    GLfloat gAmbint[] = {0.0f,0.0f,0.0f,0.7f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,gAmbint);
    
    // 设置观看点是否是近距离的
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    
    
    
    
    // 设置材料属性
    GLfloat animationMater[] = {1.0f,0.5f,0.5f,1.0f};
    GLfloat specular[] = {0.0f,1.0f,0.5f,1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, animationMater);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    
    
    //设置填充模式
//    glEnable(GL_POLYGON_STIPPLE);
//    glPolygonStipple(fire);
    
    
    
    
    
    
    
    
    
    
    
    glLoadIdentity();
    glTranslated(50,50, -50);
    
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);    // 设置投影模式
    gluPerspective(90.0f, 1.0f, 0, 800.0f);
    glMatrixMode(GL_MODELVIEW);

    glutSolidSphere(50, 50, 50);    // 1、半径，2、经线条数，3、纬线条数
    
    
    
    
    GLfloat color[] = {0.5f,0.5f,0.5f,1.0f};
    GLfloat color2[] = {1.0f,1.0f,1.0f,1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color2);
    
    
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glTranslated(-50, -50, -50);
    glutSolidSphere(50, 50, 50);
//    glutSolidSphere(50, 50, 50);
    glFlush();
}


void changeSize(GLsizei width, GLsizei height)
{
    LOG(__func__);
    GLfloat nRange = 100.0f;
    glViewport(0, 0, width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat aspectRatio = width/height;
    if (width <= height)
    {
        glOrtho(-nRange, nRange, -nRange/aspectRatio, nRange/aspectRatio, -nRange, nRange);
    }
    else
    {
        glOrtho(-aspectRatio, aspectRatio, -nRange, nRange, -nRange, nRange);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void createWindows(GLsizei width, GLsizei height)
{
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutCreateWindow("jepsonTest");
    
}




int main(int argc, char * argv[]) {
    // insert code here...
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    
    
    createWindows(600,600);
    glutReshapeFunc(changeSize);
    glutDisplayFunc(drawPolygons);
    
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(0.7f,0.7f, 0.7f, 0.7f);
    glutMainLoop();
    
    return 0;
}
