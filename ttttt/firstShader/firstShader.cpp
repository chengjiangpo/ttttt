//
//  firstShader.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-3-25.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "firstShader.h"

firstShader::firstShader()
{
    
}

firstShader::~firstShader()
{
    
}

void firstShader::init()
{
    // 初始化glew库
    glewInit();
    
    // 清理颜色和深度信息
    glClearColor(GRAYCOLOR);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

char* firstShader::loadFileContent(const char* path)
{
    FILE* pfile = fopen(path, "rb");
    if (pfile)
    {
        fseek(pfile, 0, SEEK_END);
        size_t length = ftell(pfile);
        
        char* buff = new char[length];
        rewind(pfile);
        fread(buff, length, 1, pfile);
        
        fclose(pfile);
        return buff;
    }
    fclose(pfile);
    return NULL;
}

GLint firstShader::createGPUProgram(const char* vsShaderPath,const char* fsShaderPath)
{
    // 1、创建一个某种类型的shader
    GLint vsShader = glCreateShader(GL_VERTEX_SHADER);
    GLint fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // 2、加载shader文件代码
    const char* vsCode = loadFileContent(vsShaderPath);
    const char* fsCode = loadFileContent(fsShaderPath);
    
    // 3、将shader代码发送到显卡上
    glShaderSource(vsShader, 1, &vsCode, NULL);
    glShaderSource(fsShader, 1, &fsCode, NULL);
    
    // 4、编译shader
    glCompileShader(vsShader);
    glCompileShader(fsShader);
    
    // 5、创建程序
    GLint program = glCreateProgram();
    
    // shader绑定到程序中
    glAttachShader(program, vsShader);
    glAttachShader(program, fsShader);
    
    // 6、链接程序
    glLinkProgram(program);
    
    // 7、解绑shader
    glDetachShader(program, vsShader);
    glDetachShader(program, fsShader);
    
    // 8、清理shader
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    
    return program;
}

void firstShader::draw()
{
    init();
    
    GLint program = createGPUProgram("/Users/chengjiangpo/Desktop/firstVertexShader.txt", "/Users/chengjiangpo/Desktop/firstFrameShader.txt");
    
    
    VertexColor* vc = setTriangleInfo();
    
    // 创建缓冲区的三个步骤：
    GLuint vbo;
    // 1、创建一个缓冲区对象
    glGenBuffers(1,&vbo);
    // 2、绑定该缓冲区对象（将该缓冲区设置为当前缓冲区）
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    // 3、将数据拷贝到缓冲区对象中
    glBufferData(GL_ARRAY_BUFFER,sizeof(VertexColor)*3,vc,GL_STATIC_DRAW);
    
    // 4、解绑缓冲区
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    // 查找这个参数在shader程序中的位置。
    GLint posLocation, colorLocation, MLocation,VLocation,PLocation;
    posLocation     = glGetAttribLocation(program,"pos");
    colorLocation   = glGetAttribLocation(program,"color");
    MLocation       = glGetUniformLocation(program,"M");
    VLocation       = glGetUniformLocation(program,"V");
    PLocation       = glGetUniformLocation(program, "P");
    
    
    // 向GPU程序传递参数
    glUseProgram(program);
    // 传递矩阵参数到shader
    glm::mat4 protection = glm::perspective(90.0f, WINWIDTH/WINHIGH, 0.1f, 1000.0f);
    glUniformMatrix4fv(MLocation,1,GL_FALSE,identityMatrix);
    glUniformMatrix4fv(VLocation,1,GL_FALSE,identityMatrix);
    glUniformMatrix4fv(PLocation,1,GL_FALSE,glm::value_ptr(protection));
    
    
    // 传递vertex和color相关信息(从 VBO中取出数据)
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(posLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexColor),nullptr);
    
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexColor),(void*)(sizeof(GLfloat)*3));
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    glutSwapBuffers();
    // 重置
    glUseProgram(0);
    
}

VertexColor* firstShader::setTriangleInfo()
{
    // 定义三角形的三个顶点信息
    GLfloat zorder = -100.0f;
    
    VertexColor* vc = new VertexColor[3];
    vc[0] = makeVertexColor(makeVertex(0.0f, 0.0f, zorder), makeColor(1.0f, 0.0f, 0.0f, 1.0f));
    
    vc[1] = makeVertexColor(makeVertex(50.0f, 0.0f, zorder), makeColor(0.0f, 1.0f, 0.0f, 1.0f));
    
    vc[2] = makeVertexColor(makeVertex(0.0f, 50.0f, zorder), makeColor(0.0f, 0.0f, 1.0f, 1.0f));
    
    return vc;
}



