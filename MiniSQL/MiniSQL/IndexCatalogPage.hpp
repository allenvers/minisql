//
//  IndexCatalogPage.hpp
//  MiniSQL
//
//  Created by zyy on 15/10/21.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef IndexCatalogPage_hpp
#define IndexCatalogPage_hpp

#include "Page.hpp"
#include <stdio.h>

class IndexCatalogPage: public Page
{
public:
    int recordLimit;
    
    IndexCatalogPage(){pageType = PageType::IndexCatalogPage; pageIndex = 1; recordLimit=10;}
    ~IndexCatalogPage(){};
    int writeIndex(string, string, string); //参数：表名、列名、索引名；返回值：条目存储位置
    void writeInitialPage();
    void writeCont(int, string);            //参数：开始写的位置、写的内容
    int readPrevDel(int);                   //参数：当前这条被删除的条目位置编号
    string readIndexName(int);              //参数：索引存储位置编号
};


#endif /* IndexCatalogPage_hpp */

