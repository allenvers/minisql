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
    
    buffer.allocatePage(page);
    
    cout << page.pageIndex << endl;
    
    buffer.closeAllFiles();
    
    return 0;
}
