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
#include "IndexCatalogPage.hpp"
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
    string s;
    
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
    printf("** %s\n",table.attrName[table.primaryKeyLoc].c_str());
    insertIndex(table.tableName, table.attrName[table.primaryKeyLoc], table.tableName+table.attrName[table.primaryKeyLoc]);
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
        BufferManager buffer;
        IndexCatalogPage indexPage;
        int n,nn,i,x,k;
        string s;
        
        indexPage.pageIndex=1;
        buffer.readPage(indexPage);
        n=*(int*)indexPage.pageData;
        nn=n;
        i=1;
        k=0;
        while (i<=n)                                //开始逐条检查，删除这张表上所有的索引
        {
            x=indexPage.readPrevDel(i);
            if (x==0)                               //如果当前条未被删除
            {
                s=indexPage.readTableName(i);
                if (s==tableName)                   //如果是这张表的索引，删掉
                {
                    k++;                            //k用来记录删除了多少条索引
                    indexPage.deleteIndex(i);
                    //此处应有个api接口，用来真正删除索引
                }
            }
            else                                    //如果当前条已被删除，则最后一条位置后移
                n++;
            
            i++;
        }
        
        indexPage.pageIndex=1;                      //记录索引信息首页的索引总数也需要改
        buffer.readPage(indexPage);
        *(int*)indexPage.pageData=nn-k;
        buffer.writePage(indexPage);
        buffer.deleteTableCatalogFile(tableName);   //删除当前表的文件
    }
}

bool CatalogManager::tableExisted(string tableName)
{
    BufferManager buffer;
    printf("TableExisted\n");
    if (buffer.tableCatalogFileIsExist(tableName))
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
    return 0;
}

string CatalogManager::indexLocation(string indexName)
{
    printf("IndexLocation\n");
    return "Tablename+AttrName";
}

void CatalogManager::insertIndex(string tableName, string attrName, string indexName)
{
    IndexCatalogPage indexPage;
    printf("InsertIndex\n");
    if (indexExisted(indexName))
    {
        printf("Index existed!\n");
    }
    else
    if (!attrUnique(tableName, attrName))
    {
        printf("Attribution is not unique!\n");
    }
    else
    {
        indexPage.writeIndex(tableName, attrName, tableName+attrName);
        //此处应该有个api接口，用来真正建索引
    }
}