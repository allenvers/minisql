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
#include <unistd.h>
#include <cstring>
#include <string>

using namespace std;


class Page {
public:
    Page(string fileName = "", PageIndex pageNumber = UNDEFINEED_PAGE) {
        this->fileName = fileName;
        this->pageNumber = pageNumber;
        this->pageData = new char[PAGESIZE];
    }
    
    Page(const Page &page) {
        this->fileName = page.fileName;
        this->pageNumber = page.pageNumber;
        this->pageData = new char[PAGESIZE];
        memcpy(this->pageData, page.pageData, PAGESIZE);
    }
    
    ~Page() {
        if (pageData != nullptr)
            delete []pageData;
    }
    
//    void fetchDataFromDisk();
//    void writeDataToDisk();
    
    string fileName;
    PageIndex pageNumber;
    char *pageData;
};

#endif /* Page_hpp */
