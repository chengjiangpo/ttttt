//
//  texture.h
//  ttttt
//
//  Created by chengjiangpo on 17-4-8.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#ifndef __ttttt__texture__
#define __ttttt__texture__

#include "LHead.h"

class texture
{
private:
    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_texture;
    GLint  m_program;
    
    int    m_indexNum;
    
public:
    texture();
    ~texture();
    
public:
    void draw();

private:
    void init();
    void initProgram();
    void initModel();
    void initVBOAndIBO(VertexInfo* pInfo,int vertexNum,int* pIndex,int indexNum);
    void initTexture();
    void initMatrix();

};

#endif /* defined(__ttttt__texture__) */
