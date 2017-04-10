//
//  texture.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-4-8.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "texture.h"
#include "load3DModel.h"

texture::texture()
:m_vbo(0)
,m_ibo(0)
,m_texture(0)
,m_program(0)
{
    
}

texture::~texture()
{
    
}


void texture::init()
{
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_TEST);
}

void texture::initProgram()
{
    string vsName = getFullPath("Shader/texcoord.vs");
    string fsName = getFullPath("Shader/texcoord.fs");
    
    char* vsCode = getFileData(vsName.c_str());
    char* fsCode = getFileData(fsName.c_str());
    
    GLint vsShader = glCreateShader(GL_VERTEX_SHADER);
    GLint fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vsShader,1,&vsCode,0);
    glShaderSource(fsShader,1,&fsCode,0);
    
    glCompileShader(vsShader);
    glCompileShader(fsShader);
    checkShaderError(vsShader);
    checkShaderError(fsShader);
    
    m_program = glCreateProgram();
    
    glAttachShader(m_program,vsShader);
    glAttachShader(m_program,fsShader);
    
    glLinkProgram(m_program);
    
    glDetachShader(m_program,vsShader);
    glDetachShader(m_program,fsShader);
    
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    
    delete [] vsCode;
    delete [] fsCode;
}

void texture::initModel()
{
    string name = getFullPath("model/Sphere.obj");
    
    VertexInfo* pInfo   = NULL;
    int*        pIndex  = NULL;
    int         vertexNum = 0, indexNum = 0;
    
    load3DModel model;
    model.loadModel(name, pInfo,vertexNum, pIndex,indexNum);
    m_indexNum = indexNum;
    
    // 创建VBO和IBO
    initVBOAndIBO(pInfo,vertexNum, pIndex,indexNum);
//    delete [] pInfo;
//    delete [] pIndex;
}

void texture::initVBOAndIBO(VertexInfo* pInfo,int vertexNum,int* pIndex,int indexNum)
{
    m_vbo = 0;
    glGenBuffers(1,&m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBufferData(GL_ARRAY_BUFFER,vertexNum*sizeof(VertexInfo),pInfo,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    m_ibo = 0;
    glGenBuffers(1,&m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexNum*sizeof(int),pIndex,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
void texture::initMatrix()
{
    GLint posLocation,texcoordLocation,normalLocation;
    GLint MLocation,VLocation,PLocation,NMLocation;
    
    glUseProgram(m_program);
    posLocation = glGetAttribLocation(m_program,"pos");
    texcoordLocation = glGetAttribLocation(m_program,"texcoord");
    normalLocation = glGetAttribLocation(m_program,"normal");
    
    MLocation = glGetUniformLocation(m_program,"M");
    VLocation = glGetUniformLocation(m_program,"V");
    PLocation = glGetUniformLocation(m_program,"P");
    NMLocation = glGetUniformLocation(m_program,"NM");
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f,0.0f,-1.0f));
    glUniformMatrix4fv(MLocation,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(VLocation,1,GL_FALSE,identityMatrix);
    glUniformMatrix4fv(PLocation,1,GL_FALSE,glm::value_ptr(protectionMatrix));
    
    // 设置顶点信息
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(posLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(void*)(offsetof(VertexInfo, vertex)));
    
    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation,2,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(void*)(offsetof(VertexInfo, texCoor)));
    
    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(void*)(offsetof(VertexInfo, normal)));
    
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform1i(GL_TEXTURE_2D,0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture::initTexture()
{
    string name = getFullPath("image/earth.bmp");
    
    char* fileData = getFileData(name.c_str());
    if (!fileData || *((unsigned short*)fileData) != 0x4D42)
    {
        LOG("纹理文件不是BMP文件！！！");
        delete [] fileData;
        return;
    }
    
    int offset  = *((int *)(fileData + 10));
    int width   = *((int *)(fileData + 18));
    int height  = *((int *)(fileData + 22));
    
    char* textureData = (fileData + offset);
    for (size_t i = 0; i < width*height*3; i+=3)
    {
        unsigned char temp = textureData[i];
        textureData[i] = textureData[i+2];
        textureData[i+2] = temp;
    }
    
    m_texture = 0;
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    // 设置超出边界时的环绕过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // 设置放大缩小过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    delete []fileData;
}

void texture::draw()
{
    init();
    initProgram();
    initModel();
    initTexture();
    initMatrix();
    
    glUseProgram(m_program);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
    glDrawElements(GL_TRIANGLES, m_indexNum, GL_UNSIGNED_BYTE, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glUseProgram(0);
    
    glutSwapBuffers();
}






