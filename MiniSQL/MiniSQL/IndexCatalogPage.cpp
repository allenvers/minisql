//
//  IndexCatalogPage.cpp
//  MiniSQL
//
//  Created by zyy on 15/10/21.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#include "BufferManager.hpp"
#include "IndexCatalogPage.hpp"
#include <string>
#include "Global.h"
using namespace std;

//由于index信息只存在一个文件内，因此用第一页来存放总体信息
//pageData[0]表示当前index条目总数，pageData[1]表示最后一个被删除的条目编号，如果没有则为0
void IndexCatalogPage::writeInitialPage()
{
    BufferManager buffer;
    
    pageData[0]=0;
    pageData[1]=0;
    buffer.writePage(*this);
}

int IndexCatalogPage::readPrevDel(int indexPos)
{
    int i,j,x;
    
    i=(indexPos-1)/recordLimit+2;
    j=(indexPos-1)%recordLimit+1;
    x=*(int*)(pageData+(j-1)*400+300);
    return x;
}

string IndexCatalogPage::readIndexName(int indexPos)
{
    int i,j,k;
    string s="";
    BufferManager buffer;
    
    i=(indexPos-1)/recordLimit+2;
    j=(indexPos-1)%recordLimit+1;
    pageIndex=i;
    buffer.readPage(*this);
    for (k=(j-1)*400+200; pageData[k]!=0; k++)
        s=s+pageData[k];
    
    return s;
}

void IndexCatalogPage::writeCont(int start, string cont)
{
    int i,len;
    
    len=(int)cont.length();
    for (i=0; i<len; i++)
        pageData[start+i]=cont[i];
    
    pageData[start+i]=0;
}

int IndexCatalogPage::writeIndex(string tableName, string attrName, string indexName)
{
    int n,m,i,j,x,target;
    BufferManager buffer;
    
    n = (int)pageData[0];
    n++;
    m = (int)pageData[1];
    if (m==0)                  //没有删除的条目，即目前为满排列，直接插到最后
    {
        target=n;
        i=(n-1)/recordLimit+2;  //i为页数
        j=(n-1)%recordLimit+1;  //j为行数
    }
    else                        //有删除的条目，插到最后一次删除的位置，并更改删除信息
    {
        target=m;
        i=(m-1)/recordLimit+2;
        j=(m-1)%recordLimit+1;
        x=readPrevDel(m);
        pageData[1]=x;
    }
    
    buffer.writePage(*this);    //改首页信息
    pageIndex=i;                //强行改成第i页并读第i页数据
    buffer.readPage(*this);
    writeCont((j-1)*400, tableName);
    
    writeCont((j-1)*400+100, attrName);
    writeCont((j-1)*400+200, indexName);
    *(int*)(pageData+(j-1)*400+300) = -1;
    buffer.writePage(*this);
    
    return target;
}
