//
//  main.cpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include <iostream>
#include <string>
#include "BufferManager.hpp"
#include "CatalogManager.hpp"
#include "IndexCatalogPage.hpp"
#include "TableInfo.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    BufferManager buffer{};
    
    
    Page page;
    page.tableName = "test";
    page.attributeName = "test";
    page.pageType = PageType::IndexPage;
    page.pageIndex = 2;
    
    buffer.deallocatePage(page);
    
    CatalogManager catalog;
    
    TableInfo table;
    table.tableName = "Student";
    table.attrNum = 2;
    table.attrType[0] = "int";
    table.attrType[1] = "char(10)";
    table.attrIndex[0] = "";
    table.attrIndex[1] = "";
    table.attrUnique[0] = 'Y';
    table.attrUnique[1] = 'N';
    table.attrName[0] = "studentid";
    table.attrName[1] = "studentname";
    table.primaryKeyLoc = 0;
    catalog.insertTable(table);
    
    string s;
    int k = catalog.attrType("Student", "studentname");
    printf("type = %d\n",k);
    printf("primarykey = %s\n",catalog.primaryKey("Student").c_str());
    
    IndexCatalogPage indexPage;     //这两行正式运行的时候也要用，不仅仅是测试，用于初始化存放index的文件
    indexPage.writeInitialPage();   //这两行正式运行的时候也要用，不仅仅是测试，用于初始化存放index的文件
    printf("First index is %s\n",indexPage.readIndexName(1).c_str());
    return 0;
}
