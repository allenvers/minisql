//
//  TableInfo.hpp
//  MiniSQL
//
//  Created by zyy on 15/10/18.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef TableInfo_hpp
#define TableInfo_hpp

#include <stdio.h>
#include <string>
using namespace std;

class TableInfo
{
public:
    int attrNum;
    string tableName;
    string attrName[33];
    string attrType[33];
    char attrUnique[33];
    string attrIndex[33];
    int primaryKeyLoc;
};

#endif /* TableInfo_hpp */
