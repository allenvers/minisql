//
//  CatalogManager.cpp
//  MiniSQL
//
//  Created by zyy on 15/10/17.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#include "CatalogManager.hpp"
#include <stdio.h>
#include <string>
using namespace std;


void CatalogManager::InsertTable()
{
    printf("InsertTable\n");
    InsertIndex("TableName", "PrimaryKey", "PrimaryKeyIndex");
}

void CatalogManager::DropTable(string TableName)
{
    printf("DropTable\n");
    if (!TableExisted(TableName))
    {
        printf("Table does not exist!");
    }
    else
    {
        
    }
}
bool CatalogManager::TableExisted(string TableName)
{
    printf("TableExisted\n");
    return 1;
}

int CatalogManager::AttrType(string TableName, string AttrName)
{
    printf("AttrType\n");
    return 0;
}

string CatalogManager::PrimaryKey(string TableName)
{
    printf("PrimaryKey\n");
    return "AttrName";
}

bool CatalogManager::IndexExisted(string TableName, string AttrName)
{
    printf("IndexExisted\n");
    return 1;
}

string CatalogManager::IndexLocation(string IndexName)
{
    printf("IndexLocation\n");
    return "Tablename+AttrName";
}

void CatalogManager::InsertIndex(string TableName, string AttrName, string IndexName)
{
    printf("InsertIndex");
}