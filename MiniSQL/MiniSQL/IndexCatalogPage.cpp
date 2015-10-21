//
//  IndexCatalogPage.cpp
//  MiniSQL
//
//  Created by zyy on 15/10/21.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#include "IndexCatalogPage.hpp"
#include <string>
#include "Global.h"
using namespace std;

void IndexCatalogPage::writeInitialPage()
{
    *(int *)(pageData) = UNDEFINEED_PAGE_NUM;
}

int IndexCatalogPage::writeIndex(string tableName, string attrName, string indexName)
{
    return 1;
}

//
//
//void CatalogPage::writeAttr(int start, string cont)
//{
//    int i,len;
//    
//    len=cont.length();
//    for (i=0; i<len; i++)
//        pageData[start+i]=cont[i];
//}
//
//string CatalogPage::readAttrName(int num)
//{
//    int i;
//    string s="";
//    
//    for (i=num*100+2; pageData[i]!=0; i++)
//        s = s+pageData[i];
//    
//    return s;
//}
//
//string CatalogPage::readAttrType(int num)
//{
//    int i;
//    string s="";
//    
//    for (i=num*100+22; pageData[i]!=0; i++)
//        s = s+pageData[i];
//    
//    return s;
//}
//
//string CatalogPage::readAttrIndex(int num)
//{
//    int i;
//    string s="";
//    
//    for (i=num*100+42; pageData[i]!=0; i++)
//        s = s+pageData[i];
//    
//    return s;
//}
//
//char CatalogPage::readAttrUnique(int num)
//{
//    return pageData[num*100+62];
//}