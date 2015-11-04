//
//  API.cpp
//  MiniSQL
//
//  Created by zyy on 15/10/30.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#include "API.hpp"
#include "CatalogManager.hpp"

bool API::insertRecord(SQLcommand sql)
{
    //先调用catalogManager的接口判断格式是否合法
    //如果不合法，返回false
    //如果合法，调用recordManager的接口插入此条记录
//        printf("%d\n",sql.attrNum);
//        printf("%f\n",sql.condCont[2].attrValueFlo);
    printf("----API::insertRecord----\n");
    return 1;
}

bool API::createTable(TableInfo tableInfo)
{
//    printf("@@@%s\n",tableInfo.tableName.c_str());
//    printf("---%d\n",tableInfo.attrNum);
//    printf("===%s\n",tableInfo.attrType[2].c_str());
//    printf("~~~%s\n",tableInfo.primaryKey.c_str());
    printf("----API::createTable----\n");
    CatalogManager catalog;
    catalog.insertTable(tableInfo);
    return 1;
}

bool API::dropIndex(SQLcommand sql)
{
//    printf("---%s\n",sql.indexName.c_str());
    printf("----API::dropIndex----\n");
    return 1;
}

bool API::createIndex(SQLcommand sql)
{
//    printf("---%s %s %s\n",sql.indexName.c_str(), sql.tableName.c_str(), sql.attrName.c_str());
    printf("----API::createIndex----\n");
    return 1;
}

bool API::dropTable(SQLcommand sql)
{
//    printf("---%s\n",sql.tableName.c_str());
    
    printf("----API::dropTable----\n");
    return 1;
}

bool API::selectRecord(SQLcommand sql)
{
//    printf("---%d\n",sql.condNum);
//    printf("---%s %s %f\n", sql.condCont[1].attrName.c_str(), sql.condCont[1].op.c_str(), sql.condCont[1].attrValueFlo);
    
    printf("----API::selectRecord----\n");
    return 1;
}

bool API::deleteRecord(SQLcommand sql)
{
//    printf("---%d\n",sql.condNum);
//    printf("---%s %s %s\n",sql.condCont[2].attrName.c_str(), sql.condCont[2].op.c_str(), sql.condCont[2].attrValueStr.c_str());
    
    printf("----API::deleteRecord----\n");
    return 1;
}

bool API::execFile(SQLcommand sql)
{
//    printf("---%s\n",sql.fileName.c_str());
    
    return 1;
}