//
//  load3DModel.cpp
//  ttttt
//
//  Created by chengjiangpo on 17-3-31.
//  Copyright (c) 2017年 jepsonCheng. All rights reserved.
//

#include "load3DModel.h"
#include <sstream>


load3DModel::load3DModel()
{
    
}

load3DModel::~load3DModel()
{
    
}

bool load3DModel::readModel(string name,vector<Vertex>& vertexVec,vector<TexCooor>& texcoorVec,vector<Normal>& normalVec,vector<VertexIndex>& indexVec)
{
    name = getFullPath(name);
    string fileData = getFileData(name.c_str());
    
    stringstream sstream(fileData);
    char line[1024];
    while (sstream.getline(line, 1024))
    {
        stringstream lineStream(line);
        
        string part;
        lineStream>>part;
        if(part == "v") // vertex position
        {
            string stringX,stringY,stringZ;
            float posX,posY,posZ;
            lineStream>>stringX>>stringY>>stringZ;
            
            posX = atof(stringX.c_str());
            posY = atof(stringY.c_str());
            posZ = atof(stringZ.c_str());
            vertexVec.push_back(makeVertex(posX, posY, posZ));
        }else if(part == "vt")  // vertex texcoodr
        {
            string texcoodr1,texcoodr2;
            float vt1,vt2;
            lineStream>>texcoodr1>>texcoodr2;
            vt1 = atof(texcoodr1.c_str());
            vt2 = atof(texcoodr2.c_str());
            texcoorVec.push_back(makeTexCoor(vt1, vt2));

        }else if (part == "vn") // vertex normal
        {
            string normal1,normal2,normal3;
            float vn1,vn2,vn3;
            lineStream>>normal1>>normal2>>normal3;
            vn1 = atof(normal1.c_str());
            vn2 = atof(normal2.c_str());
            vn3 = atof(normal3.c_str());
            normalVec.push_back(makeNormal(vn1, vn2, vn3));

        }else if(part == "f")   // face
        {
            for (int i = 0; i < 3 ; i++)
            {
                string faceString;
                lineStream >> faceString;
                vector<int> numVec = splitStringToNum(faceString,'/');
                VertexIndex index = makeVertexIndex((GLint)numVec.at(0), (GLint)numVec.at(1), (GLint)numVec.at(2));
                indexVec.push_back(index);
            }
        }
    }
    
    return false;
}


void load3DModel::loadModel(string modelName,vector<VertexInfo>& vertexInfoVec,vector<int>& indexVec)
{
    vector<Vertex>      vertexVec;
    vector<TexCooor>    texcoorVec;
    vector<Normal>      normalVec;
    vector<VertexIndex> vertexIndexVec;
    
    load3DModel load;
    load.readModel(modelName, vertexVec, texcoorVec, normalVec, vertexIndexVec);
    
    
    // 开始处理读取出来的模型的数据
    for (size_t i = 0; i < vertexIndexVec.size(); i++)
    {
        int findIndex = -1;
        VertexIndex indexA = vertexIndexVec.at(i);
        for (size_t j = 0; j < indexVec.size() ;j++)
        {
            VertexIndex indexB = vertexIndexVec.at(indexVec.at(j));
            if (indexA.positionIndex == indexB.positionIndex
                && indexA.texcoorIndex == indexB.texcoorIndex
                && indexA.nomalIndex == indexB.nomalIndex)
            {
                findIndex = (int)j;
                break;
            }
        }
        if (findIndex >= 0 )
        {
            indexVec.push_back(findIndex);
        }else
        {
            // 之前没有遇到过相同的点，需要创建新的点
            vertexInfoVec.push_back(makeVertexInfo(vertexVec.at(indexA.positionIndex-1), makeColor(1.0f, 1.0f, 1.0f, 1.0f), texcoorVec.at(indexA.texcoorIndex-1), normalVec.at(indexA.nomalIndex-1)));
            int curIndex = (int)vertexInfoVec.size()-1;
            indexVec.push_back(curIndex);
        }
    }
}

void load3DModel::loadModel(string name,VertexInfo* &pInfo,int& vertexNum,int* &pIndex,int& indexNum)
{
    vector<VertexInfo>  vecInfo;
    vector<int> vecIndex;
    
    loadModel(name, vecInfo, vecIndex);
    
    int infoSize    = (int)vecInfo.size();
    int indexSize   = (int)vecIndex.size();
    
    pInfo   = new VertexInfo[infoSize];
    pIndex  = new int[indexSize];
    
    for (int i = 0; i < infoSize; i++) {
        *(pInfo) = vecInfo.at(i);
    }
    
    for (int j = 0; j < indexSize; j++) {
        *(pIndex) = vecIndex.at(j);
    }
    
    vertexNum = infoSize;
    indexNum  = indexSize;
}



