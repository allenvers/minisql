//
//  CatalogManager.hpp
//  MiniSQL
//
//  Created by zyy on 15/10/17.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef CatalogManager_hpp
#define CatalogManager_hpp

#include <stdio.h>
#include "BufferManager.hpp"
#include "TableInfo.hpp"
#include <string>
using namespace std;

class CatalogManager
{
public:
    CatalogManager(){};
    ~CatalogManager(){};
    void insertTable(TableInfo);                 //参数：表名、属性数目、主键、每个属性的类型、每个属性是否unique
    void dropTable(string);             //参数：表名
    bool tableExisted(string);          //参数：表名
    int attrType(string, string);       //参数：表名、列名；返回值：0-不存在，1-int，2-float，>2-char(返回值-2)（例如5表示char(3)）
    bool attrUnique(string, string);    //参数：表名、列名
    string primaryKey(string);          //参数：表名；返回值：列名
    bool indexExisted(string, string);  //参数：表名、列名
    string indexLocation(string);       //参数：索引名；返回值：表名、列名
    void insertIndex(string, string, string);   //参数：表名，列名，索引名
    
};

#endif /* CatalogManager_hpp */
