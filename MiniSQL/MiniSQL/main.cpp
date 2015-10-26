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
    IndexCatalogPage indexPage;
//    indexPage.writeInitialPage();   //这行只在第一次运行的时候要用，用于初始化存放index的文件
   
    
    Page page;
    page.tableName = "test";
    page.attributeName = "test";
    page.pageType = PageType::IndexPage;
    page.pageIndex = 2;
    
    buffer.deallocatePage(page);
    
    CatalogManager catalog;
    
    TableInfo table;
    table.tableName = "student";
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
    catalog.insertIndex("student", "studentname", "allname");
    catalog.insertIndex("student", "studentid", "studentNumber");
//    catalog.deleteIndex("studentNumber");
    string s;
    printf("primarykey = %s\n",catalog.primaryKey("student").c_str());
    printf("First index is %s\n",indexPage.readIndexName(1).c_str());
    printf("Second index is %s\n",indexPage.readIndexName(2).c_str());
    return 0;
}
