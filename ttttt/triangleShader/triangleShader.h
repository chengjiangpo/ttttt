//
//  triangleShader.h
//  ttttt
//
//  Created by chengjiangpo on 17-3-27.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#ifndef __ttttt__triangleShader__
#define __ttttt__triangleShader__

#include <iostream>
#include "LHead.h"

class triangleShader
{
public:
    triangleShader();
    ~triangleShader();
    
public:
    void init();
    
    GLint initProgram();
    
    GLuint createVBO(size_t length,void* pInfo);
    
    GLuint createIBO();
    
    VertexColor* createVertexInfos(GLint& length);
    
    void setShaderInfo(GLint program,GLuint vbo,GLuint ibo);
    
    void draw();
};

#endif /* defined(__ttttt__triangleShader__) */
