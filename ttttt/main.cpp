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

static GLfloat GL_PI = 3.14159f;
void drawPoint()
{
    GLfloat z = -50.0f;
    
    //清空画布
    glClear(GL_COLOR_BUFFER_BIT);
    
    //设置画图使用的颜色
    glColor3f(1.0f, 0.0f, 0.0f);
    
    //保存矩阵
    glPushMatrix();
    
    //旋转, 如果不旋转，那些不同层次的点都重叠在一起，看不出3D效果了。
    /*
     * @glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
     * @angle:旋转的角度
     * @x:是否围绕x轴旋转，x > 0:逆时针旋转，x < 0:正时针旋转
     * @y: 同x
     * @z: 同z
     */
    glRotatef(1.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(120.5f, 0.0f, 1.0f, 0.0f);
//    glRotatef(120.5f, 0.0f, 0.0f, 1.0f);
    //获取点的大小的范围，以及增长的步长
    GLfloat size[2];
    GLfloat sizeStep;
    glGetFloatv(GL_POINT_SIZE_RANGE, size); // 获取点的最大、最小值
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &sizeStep);  // 粒度
    GLfloat curStep = size[0];
    for (GLfloat a = 0.0; a < GL_PI*3.0f; a += 0.1f)
    {
        GLfloat x = 50.0f*cos(a);
        GLfloat y = 50.0f*sin(a);
        //设置点的大小
        glPointSize((size[0]+size[1])/50.0);
        curStep += sizeStep;
        //设置顶点
        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();
        //调整z值
        z += 0.5f;
    }
    glPopMatrix(); 
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
    
    
    createWindows(400,400);
    glutReshapeFunc(changeSize);
    glutDisplayFunc(drawPoint);     // 点
    
    glClearColor(0.7, 0.7, 0.7, 0.7);
    glutMainLoop();
    
    return 0;
}
