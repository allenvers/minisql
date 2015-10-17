//
//  CatalogManager.hpp
//  MiniSQL
//
//  Created by zyy on 15/10/17.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef _CatalogManager_hpp_
#define _CatalogManager_hpp_

#include <stdio.h>
#include "BufferManager.hpp"
#include <string>
using namespace std;

class CatalogManager
{
public:
    CatalogManager(){};
    ~CatalogManager(){};
    void InsertTable();                 //参数：表名、属性数目、主键、每个属性的类型、每个属性是否unique
    void DropTable(string);             //参数：表名
    bool TableExisted(string);          //参数：表名
    int AttrType(string, string);       //参数：表名、列名；返回值：0-不存在，1-int，2-float，>2-char(返回值-2)（例如5表示char(3)）
    string PrimaryKey(string);          //参数：表名；返回值：列名
    bool IndexExisted(string, string);  //参数：表名、列名
    string IndexLocation(string);       //参数：索引名；返回值：表名、列名
    void InsertIndex(string, string, string);   //参数：表名，列名，索引名
    
};

#endif /* CatalogManager_hpp */
