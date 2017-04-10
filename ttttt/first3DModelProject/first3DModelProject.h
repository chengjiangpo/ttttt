//
//  first3DModelProject.h
//  ttttt
//
//  Created by chengjiangpo on 17-4-1.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#ifndef __ttttt__first3DModelProject__
#define __ttttt__first3DModelProject__

#include <iostream>
#include "LHead.h"

class first3DModelProject
{
private:
    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_textrue;
    
    int  m_vertexNum;
    int  m_indexNum;
    int  m_faceNum;
    
    GLint m_program;
    
public:
    first3DModelProject();
    ~first3DModelProject();
    
public:
    void init();
    void draw();
    void newDraw();
    GLint createProject(string vsPath,string fsPath);
    
    void loadModel(string modelName);
    
    
public:
    void createTexCoord(string name);
    
    
};

#endif /* defined(__ttttt__first3DModelProject__) */
