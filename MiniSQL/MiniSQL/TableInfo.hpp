//
//  TableInfo.hpp
//  MiniSQL
//
//  Created by zyy on 15/10/18.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef TableInfo_hpp
#define TableInfo_hpp

#include <cstdio>
#include <string>
using namespace std;

class TableInfo
{
public:
    TableInfo() {attrNum=0; primaryKey=""; primaryKeyLoc=0;}
    int attrNum;
    string tableName;
    string attrName[33];
    string attrType[33];
    char attrUnique[33];
    string primaryKey;
    int primaryKeyLoc;
    void reset() {attrNum=0; primaryKey=""; primaryKeyLoc=0;}
};

#endif /* TableInfo_hpp */
