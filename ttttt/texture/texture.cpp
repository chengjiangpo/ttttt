//
//  texture.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-4-8.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "texture.h"


texture::texture()
:m_vbo(0)
,m_ibo(0)
,m_texture(0)
,m_program(0)
,m_pModel(NULL)
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
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

GLint texture::createProgram(string vsPath, string fsPath)
{
    GLint program = -1;
    vsPath = getFullPath(vsPath);
    fsPath = getFullPath(fsPath);
    
    char* vsCode,*fsCode ;
    vsCode = getFileData(vsPath.c_str());
    fsCode = getFileData(fsPath.c_str());
    
    GLint vsShader = 0, fsShader = 0;
    vsShader = glCreateShader(GL_VERTEX_SHADER);
    fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vsShader,1,&vsCode,0);
    glShaderSource(fsShader,1,&fsCode,0);
    
    glCompileShader(vsShader);
    glCompileShader(fsShader);
    
    checkShaderError(vsShader);
    checkShaderError(fsShader);
    
    program = glCreateProgram();
    
    glAttachShader(program,vsShader);
    glAttachShader(program,fsShader);
    
    glLinkProgram(program);
    

    
    glDetachShader(program,vsShader);
    glDetachShader(program,fsShader);
    
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    
    delete [] vsCode;
    delete [] fsCode;
    
   
    
    return program;
}

void texture::createVBOAndIBO(string modelName)
{
    modelName = getFullPath(modelName);
    m_pModel = new Model;
    m_pModel->load(modelName);
    m_pModel->print();
    
    m_vbo = 0;
    glGenBuffers(1,&m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(VertexInfo)*m_pModel->m_InfoNum,m_pModel->m_pInfo,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    m_ibo = 0;
    glGenBuffers(1,&m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*m_pModel->m_IndexNum,m_pModel->m_pIndex,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void texture::createTexture(string texName)
{
    m_texture = 0;
    texName = getFullPath(texName);
    
    char* fileData = getFileData(texName.c_str());
    unsigned char* imageData = (unsigned char*) fileData;
    
    if (*((unsigned short*)imageData) != 0x4D42)// 判断是否是bmp文件
    {
        LOG("文件不是BMP文件");
        delete [] fileData;
        return ;
    }
    
    // 像素内容的偏移
    size_t pixeDataOffset = *((int*)(imageData + 10));
    
    int width =*((int*)(imageData + 18));
    int hight =*((int*)(imageData + 22));
    
    unsigned char* pixeData = (imageData + pixeDataOffset);
    
    for (size_t i = 0; i < width*hight*3; i += 3)
    {
        // bgr->rgb
        unsigned char temp = pixeData[i+2];
        pixeData[i+2] = pixeData[i];
        pixeData[i] = temp;
    }
    
    
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, hight, 0, GL_RGB, GL_UNSIGNED_BYTE, pixeData);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    delete [] fileData;
    
}


void texture::draw()
{
    init();
    m_program = createProgram("Shader/texcoord.vs", "Shader/texcoord.fs");
    createVBOAndIBO("model/Cube.obj");
    createTexture("image/earth.bmp");
    
    glUseProgram(m_program);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    
    // 初始化
    GLint posL,normalL,texcoordL;
    posL    = glGetAttribLocation(m_program,"pos");
    normalL = glGetAttribLocation(m_program,"normal");
    texcoordL = glGetAttribLocation(m_program,"texcoord");

    GLint ML,VL,PL,NML,textureL;
    ML      = glGetUniformLocation(m_program,"M");
    VL      = glGetUniformLocation(m_program,"V");
    PL      = glGetUniformLocation(m_program,"P");
    NML     = glGetUniformLocation(m_program,"NM");
    textureL= glGetUniformLocation(m_program,"textureL");
    
    // 向顶点着色器程序传递顶点数据
    glEnableVertexAttribArray(posL);
    glVertexAttribPointer(posL,3,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(void*)(0));
    
    glEnableVertexAttribArray(normalL);
    glVertexAttribPointer(normalL,3,GL_FLOAT,GL_FALSE,sizeof(VertexIndex),(void*)(offsetof(VertexInfo, normal)));
    
    glEnableVertexAttribArray(texcoordL);
    glVertexAttribPointer(texcoordL,2,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(void*)(offsetof(VertexInfo, texCoor)));
    
    
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f,0.0f,-1.0f));
    model = glm::rotate(model, 90.0f, glm::vec3(0.0f,1.0f,0.0f));

    glm::mat4 nm = glm::inverseTranspose(model);
    glUniformMatrix4fv(ML,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(VL,1,GL_FALSE,identityMatrix);
    glUniformMatrix4fv(PL,1,GL_FALSE,glm::value_ptr(protectionMatrix));
    glUniformMatrix4fv(NML,1,GL_FALSE,glm::value_ptr(nm));
    
    // 设置纹理单元
//    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform1f(textureL,0);
    
    
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0 );
    
    
    
    // 开始绘制
//    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
    glDrawElements(GL_TRIANGLES, m_pModel->m_IndexNum, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glUseProgram(0);
    
    
    glutSwapBuffers();
}




