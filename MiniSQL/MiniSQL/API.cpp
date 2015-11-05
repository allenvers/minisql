//
//  API.cpp
//  MiniSQL
//
//  Created by zyy on 15/10/30.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#include "API.hpp"

bool API::insertRecord(SQLcommand sql)
{
//        printf("%d\n",sql.attrNum);
//        printf("%f\n",sql.condCont[2].attrValueFlo);
    clock_t begin = clock();
    printf("----API::insertRecord----\n");
    /* sql使用方法：
        sql.tableName为用户想要插入的表名
        sql.attrNum为用户输入的数据个数
        sql.condCont[1..attrNum]里面为每一个数据的情况，其中有如下参数可以使用
        condCont[i].attrType 为 "INT" "FLOAT" "CHAR" 中的一种，要注意当用户输入"INT"时，表的属性是"FLOAT"也是合法的
        对应的，根据condCont[i].attrType，以下三个里面会有一个有值，要注意当attrType为"INT"时，attrValueFlo里面也会有一份
            condCont[i].attrValueFlo / condCont[i].attrValueInt / condCond[i].attrValueStr
    */
    CatalogManager catalog;
    if (!catalog.tableExisted(sql.tableName)) {
        printf("Table %s doesn't exist! Insertion failed!\n", sql.tableName.c_str());
    }
    vector<Attribute> vec=catalog.tableInformation(sql.tableName);
    int i;
    if (vec.size()!=sql.attrNum)
    {
        printf("Failed to insert record. Wrong number of attributes.\n");
        return 0;
    }
    
    for (i=1; i<=sql.attrNum; i++)
    {
        if (vec[i-1].type==AttributeType::CHAR)
        {
            if (sql.condCont[i].attrType!="CHAR")
            {
                printf("Failed to insert record. Wrong type of value.\n");
                return 0;
            }
            
            if (sql.condCont[i].attrValueStr.length()>vec[i-1].length)
            {
                printf("Failed to insert record. Value is too long.\n");
                return 0;
            }
            memset(vec[i - 1].chardata, 0, vec[i - 1].length);
            memcpy(vec[i - 1].chardata, sql.condCont[i].attrValueStr.c_str(), sql.condCont[i].attrValueStr.length());
        }
        else
        if (vec[i-1].type==AttributeType::FLOAT)
        {
            if (sql.condCont[i].attrType=="CHAR")
            {
                printf("Failed to insert record. Wrong type of value.\n");
                return 0;
            }
            if (sql.condCont[i].attrType == "INT") {
                vec[i - 1].floatdata = (float) sql.condCont[i].attrValueInt;
            } else {
                vec[i - 1].floatdata = sql.condCont[i].attrValueFlo;
            }
        }
        else
        {
            if (sql.condCont[i].attrType!="INT")
            {
                printf("Failed to insert record. Wrong type of value.\n");
                return 0;
            }
            vec[i - 1].intdata = sql.condCont[i].attrValueInt;
        }
    }
    
    //现在数量和类型都是对的了，就等插入了
    //注意判unique的属性不能和表中已有的重复
    //判一个属性是否unique可以调用catalogManager的函数
    //bool attrUnique(string, string);  参数：表名、列名
    //vec[i].attrName可以读列名
    
    Table table(sql.tableName);
    table.insertTuple(vec);
    
    
    printf("Command running time: %f second\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
    return 1;
}

bool API::createTable(TableInfo tableInfo)
{
//    printf("@@@%s\n",tableInfo.tableName.c_str());
//    printf("---%d\n",tableInfo.attrNum);
//    printf("===%s\n",tableInfo.attrType[2].c_str());
//    printf("~~~%s\n",tableInfo.primaryKey.c_str());
    clock_t begin = clock();
    printf("----API::createTable----\n");
    CatalogManager catalog;
    catalog.insertTable(tableInfo);
    printf("Command running time: %f second\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
    return 1;
}

bool API::dropIndex(SQLcommand sql)
{
//    printf("---%s\n",sql.indexName.c_str());
    printf("----API::dropIndex----\n");
    CatalogManager catalog;
    catalog.deleteIndex(sql.indexName);
    return 1;
}

bool API::createIndex(SQLcommand sql)
{
//    printf("---%s %s %s\n",sql.indexName.c_str(), sql.tableName.c_str(), sql.attrName.c_str());
    printf("----API::createIndex----\n");
    CatalogManager catalog;
    if (catalog.insertIndex(sql.tableName, sql.attrName, sql.indexName))
    {
        //catalog创建成功，调用indexManager的接口真正建索引
    }

    return 1;
}

bool API::dropTable(SQLcommand sql)
{
//    printf("---%s\n",sql.tableName.c_str());
    
    printf("----API::dropTable----\n");
    CatalogManager catalog;
    catalog.dropTable(sql.tableName);
    return 1;
}

bool API::selectRecord(SQLcommand sql)
{
//    printf("---%d\n",sql.condNum);
//    printf("---%s %s %f\n", sql.condCont[1].attrName.c_str(), sql.condCont[1].op.c_str(), sql.condCont[1].attrValueFlo);
    
    printf("----API::selectRecord----\n");
    //飞哥加油么么哒~
    CatalogManager cm;
    for (auto itr: cm.tableInformation(sql.tableName)) {
        printf("%s\t", itr.attrName.c_str());
    }
    cout << endl;
    
    Table table(sql.tableName);
    for (auto itr: table.getAll()) {
        table.printinfo(itr);
    }
    return 1;
}

bool API::deleteRecord(SQLcommand sql)
{
//    printf("---%d\n",sql.condNum);
//    printf("---%s %s %s\n",sql.condCont[2].attrName.c_str(), sql.condCont[2].op.c_str(), sql.condCont[2].attrValueStr.c_str());
    
    printf("----API::deleteRecord----\n");
    //飞哥加油么么哒~
    return 1;
}
