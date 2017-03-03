//
//  LeanOpenGL.cpp
//  opengl
//
//  Created by jepsonCheng on 17/3/3.
//  Copyright © 2017年 jepsonCheng. All rights reserved.
//

#include "LeanOpenGL.h"
static void RenderScenceCB()
{
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f( 0.0f, 1.0f, 0.0f );
    glRectf( -25.0f, 25.0f, 25.0f, -25.0f );
    glFlush();
}

void changeSize(GLsizei width, GLsizei height)
{
    LOG(__func__);
    
    glViewport(0, 0, width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat aspectRatio = width/height;
    glOrtho(-100, 100, -100.0f/aspectRatio, 100.0f/aspectRatio, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void createWindows(GLsizei width, GLsizei height)
{
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(width, height);
    glutCreateWindow("jepsonTest");
    
}

void drawTest(int argc, const char * argv[])
{
//    LOG_FUNCNAME;
//    glutInit(&argc, &argv);
//    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
//    
//    
//    createWindows(400,400);
//    glutReshapeFunc(changeSize);
//    glutDisplayFunc( RenderScenceCB );
//    
//    glClearColor(1.0f, 0, 0, 0);
//    glutMainLoop();
}
