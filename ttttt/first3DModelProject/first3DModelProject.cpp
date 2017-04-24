//
//  first3DModelProject.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-4-1.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "first3DModelProject.h"
#include "load3DModel.h"
first3DModelProject::first3DModelProject()
:m_vbo(0)
,m_ibo(0)
,m_program(0)
,m_vertexNum(0)
,m_indexNum(0)
,m_faceNum(0)
{
    init();
}

first3DModelProject::~first3DModelProject()
{
    
}

void first3DModelProject::init()
{
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glFrontFace(GL_CCW);// 指定环绕方向
    glCullFace(GL_FRONT);
}

void first3DModelProject::draw()
{
    m_program = createProject("Shader/diffuse.vs", "Shader/diffuse.fs");
    loadModel("model/niutou.obj");
    createTexCoord("image/niutou.bmp");
    
    glUseProgram(m_program);
    
    GLint posLocation,texcoordLocation,normalLocation;
    GLint MLocation,VLocation,PLocation,NMLocation, textureLocation;
    
    posLocation     = glGetAttribLocation(m_program,"pos");
    texcoordLocation = glGetAttribLocation(m_program,"texcoord");
    normalLocation  = glGetAttribLocation(m_program,"normal");
    
    MLocation       = glGetUniformLocation(m_program,"M");
    VLocation       = glGetUniformLocation(m_program,"V");
    PLocation       = glGetUniformLocation(m_program,"P");
    NMLocation      = glGetUniformLocation(m_program,"NM");
    textureLocation = glGetUniformLocation(m_program,"texture2d");
    
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(0.0f,0.0f,-100.0f));
//    model = glm::scale(model, glm::vec3(1.3,1.3,1.3));
//    model = glm::rotate(model, 180.0f, glm::vec3(0.0,1.0,0.0));
    glm::mat4 normalMatrix = glm::inverseTranspose(model);
    // 设置矩阵信息
    glUniformMatrix4fv(MLocation,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(VLocation,1,GL_FALSE,identityMatrix);
    glUniformMatrix4fv(PLocation,1,GL_FALSE,glm::value_ptr(protectionMatrix));
    glUniformMatrix4fv(NMLocation,1,GL_FALSE,glm::value_ptr(normalMatrix));
    
    
    glBindTexture(GL_TEXTURE_2D, m_textrue);
    /*
     * @pragma1:
     * @pragma2: 一定为0，表示是0#纹理单元（注意是纹理单元，不是纹理对象）
     */
    glUniform1i(textureLocation,0);
    
    // 设置顶点信息
    /*
     * 参数解释:
     * @pragma1: 要设置着色器的中该索引对应的属性的信息
     * @pragma2: 要设置的信息的数量(每次设置需要设置几个接下来的类型的数据)
     * @pragma3: 要设置的参数的类型
     * @pragma4: 输入的参数是否进行归一化操作，一般都为false
     * @pragma5: 输入参数的间隔，间隔多大的范围取下一个值
     * @pragma6: 第一个数据的地址。
     
     * 解释：具体绘制多少个点是在具体的绘制指令中指定的。
     */
    
    
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(posLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(void*)0);
    
    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation,2,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(void*)(offsetof(VertexInfo, texCoor)));
    
    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation,3,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(void*)(offsetof(VertexInfo, normal)));
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // 调用绘制命令
    glUseProgram(m_program);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
    glDrawElements(GL_TRIANGLES, m_indexNum, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glUseProgram(0);        
    
    glutSwapBuffers();
}

GLint first3DModelProject::createProject(string vsPath,string fsPath)
{
    m_program = 0;
    
    string vsFullPath = getFullPath(vsPath);
    string fsFullPath = getFullPath(fsPath);
    
    GLint vsShader = glCreateShader(GL_VERTEX_SHADER);
    GLint fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    char* vsCode = getFileData(vsFullPath.c_str());
    char* fsCode = getFileData(fsFullPath.c_str());
    
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
    
    return m_program;
}


void first3DModelProject::loadModel(string modelName)
{
    vector<VertexInfo> vertexInfoVec;
    vector<int> indexVec;
    
    load3DModel model;
    model.loadModel(modelName, vertexInfoVec, indexVec);
    
    const int vertexNum = (int)vertexInfoVec.size();
    const int indexNum  = (int)indexVec.size();
    
    m_vertexNum = vertexNum;
    m_indexNum  = indexNum;
    
    VertexInfo* vertexPtr = new VertexInfo[vertexNum];
    GLint* indexPtr = new GLint[indexNum];
    
//    Vertex *ver = new Vertex[vertexNum];
    for (int i = 0; i < vertexNum ; i++)
    {
//        vertexInfoVec.at(i).vertex.z -= 2.0f;
        *(vertexPtr+ i) = vertexInfoVec.at(i);
    }
    
    for (int j = 0; j < indexNum ; j++)
    {
        *(indexPtr + j ) = indexVec.at(j);
    }

    m_vbo = 0;
    glGenBuffers(1,&m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBufferData(GL_ARRAY_BUFFER,vertexNum*sizeof(VertexInfo),vertexPtr,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    m_ibo = 0;
    glGenBuffers(1,&m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexNum*sizeof(int),indexPtr,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

void first3DModelProject::createTexCoord(string name)
{
    name = getFullPath(name);
    char* fileData = getFileData(name.c_str());
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
    
    // 创建/绑定纹理对象
    glGenTextures(1, &m_textrue);
    glBindTexture(GL_TEXTURE_2D, m_textrue);
    
    // 设置纹理纹理缠绕过滤方式，当纹理坐标超出范围后怎么处理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    
    // 设置纹理的放大缩小过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// 采用线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // 在显卡上声明区域存放纹理数据
    /*
     *  @pragma1:指定纹理的类型是1维、2维或则3维
     *  @pragma2:指定mipmap等级，如果没有多级纹理，填0
     *  @pragma3:纹理数据在显卡上存放的格式
     *  @pragma4:纹理的宽度
     *  @pragma5:纹理的高度
     *  @pragma6:0
     *  @pragma7:原始纹理的格式（即从CPU往GPU中传递时的格式）
     *  @pragma8:每一个分量的数据类型（R分量，G分量，B分量）
     *  @pragma9:数据指针
     */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, hight, 0, GL_RGB, GL_UNSIGNED_BYTE, pixeData);

    // 解绑定
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // 清理内存
    delete [] fileData;
}


