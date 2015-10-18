//
//  CatalogManager.cpp
//  MiniSQL
//
//  Created by zyy on 15/10/17.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#include "CatalogManager.hpp"
#include "BufferManager.hpp"
#include "Page.hpp"
#include "CatalogPage.hpp"
#include "TableInfo.hpp"
#include <stdio.h>
#include <string>
using namespace std;

void CatalogManager::insertTable(TableInfo table)
{
    printf("InsertTable\n");
    CatalogPage page;
    BufferManager buffer;
    int i;
    
    page.tableName = table.tableName;
    page.pageData[0] = (char)table.attrNum;
    page.pageData[1] = (char)table.primaryKeyLoc;
    for (i=0; i<table.attrNum; i++)
    {
        page.writeAttr(i*100+2, table.attrName[i]);
        page.writeAttr(i*100+22, table.attrType[i]);
        page.writeAttr(i*100+42, table.attrIndex[i]);
        page.pageData[i*100+62] = table.attrUnique[i];
    }
    
    buffer.writePage(page);
    insertIndex("TableName", "PrimaryKey", "PrimaryKeyIndex");
}

void CatalogManager::dropTable(string tableName)
{
    printf("DropTable\n");
    if (!tableExisted(tableName))
    {
        printf("Table does not exist!\n");
    }
    else
    {
        
    }
}

bool CatalogManager::tableExisted(string tableName)
{
    BufferManager bufferManager;
    printf("TableExisted\n");
    if (1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CatalogManager::attrType(string tableName, string attrName)
{
    int i,j,num;
    string s="";
    
    printf("AttrType\n");
    CatalogPage page;
    BufferManager buffer;
    
    page.tableName = tableName;
    buffer.readPage(page);
    num = (int)page.pageData[0];
    for (i=0; i<num; i++)
        if (page.readAttrName(i) == attrName)
            s = page.readAttrType(i);
    
    if (s == "")
        return 0;
    else
    if (s == "int")
        return 1;
    else
    if (s == "float")
        return 2;
    else
    {
        j=0;
        for (i=5; s[i]!=')'; i++)
            j = j*10+s[i]-'0';
        
        return j+2;
    }
}

bool CatalogManager::attrUnique(string tableName, string attrName)
{
    int i,num;
    char c = '\0';
    
    printf("AttrUnique\n");
    CatalogPage page;
    BufferManager buffer;
    
    page.tableName = tableName;
    buffer.readPage(page);
    num = (int)page.pageData[0];
    for (i=0; i<num; i++)
        if (page.readAttrName(i) == attrName)
            c = page.readAttrUnique(i);

    if (c=='Y')
        return 1;
    else
        return 0;
}

string CatalogManager::primaryKey(string tableName)
{
    CatalogPage page;
    BufferManager buffer;
    
    page.tableName = tableName;
    buffer.readPage(page);
    printf("PrimaryKey\n");
    return page.readAttrName((int)page.pageData[1]);
}

bool CatalogManager::indexExisted(string indexName)
{
    printf("IndexExisted\n");
    return 1;
}

string CatalogManager::indexLocation(string indexName)
{
    printf("IndexLocation\n");
    return "Tablename+AttrName";
}

void CatalogManager::insertIndex(string tableName, string attrName, string indexName)
{
    printf("InsertIndex\n");
    if (indexExisted(indexName))
    {
        printf("Index existed!\n");
    }
    else
    if (!attrUnique(tableName, attrName))
    {
        printf("Attribution is not unique!");
    }
    else
    {
        
    }
}