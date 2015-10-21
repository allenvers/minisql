//
//  IndexCatalogPage.hpp
//  MiniSQL
//
//  Created by zyy on 15/10/21.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef IndexCatalogPage_hpp
#define IndexCatalogPage_hpp

#include "Page.hpp"
#include <stdio.h>


class IndexCatalogPage: public Page
{
public:
    IndexCatalogPage(){pageType = PageType::IndexCatalogPage; pageIndex = 1;}
    ~IndexCatalogPage(){};
    int writeIndex(string, string, string); //参数：表名、列名、索引名；返回值：
    void writeInitialPage();
    string readAttrName(int);
    string readAttrType(int);
    string readAttrIndex(int);
    char readAttrUnique(int);
};


#endif /* IndexCatalogPage_hpp */

