//
//  firstShader.h
//  ttttt
//
//  Created by chengjiangpo on 17-3-25.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#ifndef __ttttt__firstShader__
#define __ttttt__firstShader__

#include <iostream>
#include "LHead.h"

class firstShader
{
public:
    firstShader();
    ~firstShader();
    
public:
    void init();
    
    char* loadFileContent(const char* path);
    
    GLint createGPUProgram(const char* vsShaderPath,const char* fsShaderPath);

    void draw();
    
    VertexColor* setTriangleInfo();
};

#endif /* defined(__ttttt__firstShader__) */
