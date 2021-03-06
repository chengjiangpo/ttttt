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
#include "first3DModelProject/first3DModelProject.h"
//#include "triangleShader.h"ex
#include "texture.h"

static GLfloat GL_PI = 3.14159f;
static GLfloat angle = 0.0f;
static texture g_texture;
static void drawPolygons()
{
    static bool first = 0;
    if (first == 0 )
    {
        g_texture.init();
    }
    first++;
    
    angle += 0.01f;
//    angle = -90.0f;
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f,-0.0f,-2.0f));
    model = glm::rotate(model, angle, glm::vec3(0.0f,1.0f,0.0f));
//    model = glm::rotate(model, 3.0f, glm::vec3(1.0f,0.0f,0.0f));
    g_texture.draw(model);
    
//    first3DModelProject program;
//    program.draw();
    
//    triangleShader shader;
//    shader.draw();
    glutPostRedisplay();
       return;
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
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    createWindows(WINWIDTH,WINHIGH);
    glutReshapeFunc(changeSize);
    glutDisplayFunc(drawPolygons);
    glutIdleFunc(drawPolygons);
    
    
//  设置正反面
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_BACK, GL_FILL);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
//    glClearColor(0.7f,0.7f, 0.7f, 0.7f);
    glutMainLoop();
    
    return 0;
}

