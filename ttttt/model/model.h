//
//  model.h
//  ttttt
//
//  Created by chengjiangpo on 17-4-17.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#ifndef __ttttt__model__
#define __ttttt__model__

#include "LHead.h"

class Model
{
public:
    string      m_Name;
    VertexInfo* m_pInfo;
    int         m_InfoNum;
    
    int*        m_pIndex;
    int         m_IndexNum;
    
    
    
public:
    Model();
    ~Model();
    void load(string modelName);
    
    void print();
    
    
};

#endif /* defined(__ttttt__model__) */
