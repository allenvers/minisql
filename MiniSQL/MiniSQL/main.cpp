//
//  main.cpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include <iostream>
#include "BufferManager.hpp"
#include "CatalogManager.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    BufferManager buffer{};
    
    
    Page page;
    page.tableName = "test";
    page.attributeName = "test";
    page.pageType = PageType::IndexPage;
    page.pageIndex = 2;
    
    buffer.deallocatePage(page);
    
    return 0;
}
