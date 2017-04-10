//
//  firstGPUProgram.h
//  ttttt
//
//  Created by chengjiangpo on 17-3-24.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#ifndef __ttttt__firstGPUProgram__
#define __ttttt__firstGPUProgram__

#include <iostream>
#include "LHead.h"

class firstGPUProgram
{
public:
    firstGPUProgram();
    ~firstGPUProgram();
    
public:
    
    void newDraw();
    void draw();
    
    void initOpenGl();
    
    void runDraw();
    
    void initLight();
    
    void setMaterialColor(Color* amibentColor,Color* specularColor);
};

#endif /* defined(__ttttt__firstGPUProgram__) */
