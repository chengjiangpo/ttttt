//
//  model.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-4-17.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "model.h"
#include "load3DModel.h"

Model::Model()
:m_Name("")
,m_pInfo(NULL)
,m_pIndex(NULL)
,m_InfoNum(0)
,m_IndexNum(0)
{
    
}

Model::~Model()
{
    if (m_pIndex)
    {
        delete [] m_pInfo;
    }
    
    if (m_pIndex)
    {
        delete [] m_pIndex;
    }
}

void Model::load(string modelName)
{
    m_Name              = modelName;
    vector<VertexInfo>  vecVertexInfo;
    vector<int>         vecVertexIndex;
    
    load3DModel model;
    model.loadModel(modelName, vecVertexInfo, vecVertexIndex);
    
    m_InfoNum = (int)vecVertexInfo.size();
    m_IndexNum  = (int)vecVertexIndex.size();
    
    m_pInfo     = new VertexInfo[m_InfoNum];
    m_pIndex    = new int[m_IndexNum];
    
    for (int i = 0; i < m_InfoNum; i++)
    {
        *(m_pInfo + i) = vecVertexInfo.at(i);
    }
    
    for (int j = 0; j < m_IndexNum; j++)
    {
        *(m_pIndex + j) = vecVertexIndex.at(j);
    }
}


void Model::print()
{
    if (m_pIndex == NULL)
    {
        printf("模型尚未初始化！！！\n");
    }else
    {
        printf("模型信息：\n");
        printf("name: %s\n",m_Name.c_str());
        
        printf("vertex Num = %d\n",m_InfoNum);
        printf("vertex Info = {\n");
        for(int i = 0; i < m_InfoNum; i++)
        {
            Vertex* vertex = &((m_pInfo + i)->vertex);
            printf("x = %f\t, y = %f\t, z = %f\n",vertex->x, vertex->y, vertex->z);
        }
        
        printf("}\n\n");
        
        printf("index Num = %d\n",m_IndexNum);
        printf("vertexIndex ifno = {\n");
        for (int i = 0 ; i < m_IndexNum; i++) {
            int index = *(m_pIndex+i);
            printf("index = %d\n",index);
        }
        
        printf("}\n");
        
    }
}



