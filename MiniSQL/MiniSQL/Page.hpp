//
//  Page.hpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef Page_hpp
#define Page_hpp

#include "Global.hpp"
#include <cstring>
#include <string>

using namespace std;

enum class PageType {
    UndefinedPage,
    RecordPage,
    IndexPage,
    RecordCatalogPage,
    IndexCatalogPage
};

class Page {
public:
    Page(string tableName = "", string attributeName = "", PageType pageType = PageType::UndefinedPage, PageIndex pageNumber = UNDEFINEED_PAGE_NUM) {
        this->tableName = tableName;
        this->attributeName = attributeName;
        this->pageType = pageType;
        this->pageNumber = pageNumber;
        this->pageData = new char[PAGESIZE];
    }
    
    Page(const Page &page) {
        this->tableName = page.tableName;
        this->attributeName = page.attributeName;
        this->pageType = pageType;
        this->pageNumber = page.pageNumber;
        this->pageData = new char[PAGESIZE];
        memcpy(this->pageData, page.pageData, PAGESIZE);
    }
    
    ~Page() {
        if (pageData != nullptr)
            delete []pageData;
    }
    
    string tableName;
    string attributeName;
    PageType pageType;
    PageIndex pageNumber;
    char *pageData;
};

#endif /* Page_hpp */
