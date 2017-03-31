//
//  firstShaderTest.h
//  ttttt
//
//  Created by chengjiangpo on 17-3-26.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#ifndef __ttttt__firstShaderTest__
#define __ttttt__firstShaderTest__

#include <iostream>
#include "LHead.h"

class firstShaderTest
{
public:
    firstShaderTest();
    ~firstShaderTest();
    
public:
    void init();
    void draw();
    
    GLint createGPUProgram();
    GLuint createVBO();
    
    void setShaderPargram(GLint program,GLuint vbo);
    
    VertexColor* setVertexInfo();
};

#endif /* defined(__ttttt__firstShaderTest__) */
