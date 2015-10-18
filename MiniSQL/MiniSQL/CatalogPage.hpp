//
//  CatalogPage.hpp
//  MiniSQL
//
//  Created by zyy on 15/10/18.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef CatalogPage_hpp
#define CatalogPage_hpp

#include <stdio.h>
#include "Page.hpp"

class CatalogPage: public Page
{
public:
    CatalogPage(){pageType = PageType::RecordCatalogPage; pageIndex = 1;}
    void writeAttr(int, string);
    string readAttrName(int);
    string readAttrType(int);
    string readAttrIndex(int);
    char readAttrUnique(int);
};

#endif /* CatalogPage_hpp */
