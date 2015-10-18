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
#include <stdio.h>
#include <string>
using namespace std;


void CatalogManager::insertTable()
{
    printf("InsertTable\n");
    Page page;
    Page page2;
    BufferManager buffer;
    
    page.pageType = PageType::RecordCatalogPage;
    page.tableName = "TableName";
    page.pageIndex = 2;
    strcpy(page.pageData, "this is a test~");
    printf("page: %s\n",page.pageData);
    buffer.writePage(page);
    page2.tableName = "TableName";
    page2.pageIndex = 2;
    page2.pageType = PageType::RecordCatalogPage;
    buffer.readPage(page2);
    printf("page2: %s\n",page2.pageData);
    insertIndex("TableName", "PrimaryKey", "PrimaryKeyIndex");
}

void CatalogManager::dropTable(string tableName)
{
    printf("DropTable\n");
    if (!tableExisted(tableName))
    {
        printf("Table does not exist!");
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
    printf("AttrType\n");
    return 0;
}

bool CatalogManager::attrUnique(string tableName, string attrName)
{
    return 1;
}

string CatalogManager::primaryKey(string tableName)
{
    printf("PrimaryKey\n");
    return "AttrName";
}

bool CatalogManager::indexExisted(string tableName, string attrName)
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
    printf("InsertIndex");
    if (indexExisted(tableName, attrName))
    {
        printf("Index existed!");
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