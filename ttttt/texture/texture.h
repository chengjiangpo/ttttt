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
#include "model.h"

class texture
{
private:
    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_texture;
    GLint  m_program;
    
    int    m_indexNum;
    
    Model*  m_pModel ;
    
    
public:
    texture();
    ~texture();
    
public:
    void init();
    void draw(glm::mat4 model);

private:

    GLint createProgram(string vsPath,string fsPath);
    
    void createVBOAndIBO(string modelName);
    
    void createTexture(string texName);
    

};

#endif /* defined(__ttttt__texture__) */
