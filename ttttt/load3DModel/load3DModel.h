//
//  load3DModel.h
//  ttttt
//
//  Created by chengjiangpo on 17-3-31.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#ifndef __ttttt__load3DModel__
#define __ttttt__load3DModel__

#include <iostream>
#include "LHead.h"

class load3DModel
{
public:
    load3DModel();
    ~load3DModel();
    
public:
    bool readModel(string name,vector<Vertex>& vertexVec,vector<TexCooor>& texcoorVec,vector<Normal>& normalVec,vector<VertexIndex>& indexVec);
    
    void loadModel(string modelName,vector<VertexInfo>& vertexInfoVec,vector<int>& indexVec);
    void loadModel(string name,VertexInfo* & pInfo,int& vertexNum,int* &pIndex,int& indexNum);
};


#endif /* defined(__ttttt__load3DModel__) */
