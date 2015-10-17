//
//  BufferManager.hpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef BufferManager_hpp
#define BufferManager_hpp

#include "Global.hpp"
#include "Page.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <map>
#include <utility>
#include <iostream>

using namespace std;

class BufferManager {
public:
    BufferManager() {
        
        if (opendir(recordFilesDirectory.c_str()) == NULL) {
            assert(mkdir(recordFilesDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1);
        }
        if (opendir(indexFilesDirectory.c_str()) == NULL) {
            assert(mkdir(indexFilesDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1);
        }
        if (opendir(recordCatalogFilesDirectory.c_str()) == NULL) {
            assert(mkdir(recordCatalogFilesDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1);
        }
        if (opendir(indexCatalogFilesDirectory.c_str()) == NULL) {
            assert(mkdir(indexCatalogFilesDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1);
        }
        // 初始化存放文件的文件夹，根据表名以及索引键建立文件
    }
    
    bool openTableFile(string tableName);
    bool openIndexFile(string tableName, string attributeName);
    bool openTableCatalogFile(string tableName);
    bool openIndexCatalogFile(string tableName, string attributeName);
    
    void makeTwoPages(int fileHandle);
    
    bool closeTableFile(string tableName);
    bool closeIndexFile(string tableName, string attributeName);
    bool closeTableCatalogFile(string tableName);
    bool closeIndexCatalogFile(string tableName, string attributeName);
    
    string tableFilePath(string tableName);
    string indexFilePath(string tableName, string attributeName);
    string tableCatalogFilePath(string tableName);
    string indexCatalogFilePath(string tableName, string attributeName);
    
    static map<string, PageIndex> tableFileHandles;
    static map<pair<string, string>, PageIndex> indexFileHandles;
    static map<string, PageIndex> tableCatalogFileHandles;
    static map<pair<string, string>, PageIndex> indexCalalogFileHandles;
    
    static const string recordFilesDirectory;
    static const string indexFilesDirectory;
    static const string recordCatalogFilesDirectory;
    static const string indexCatalogFilesDirectory;
};

const string BufferManager::recordFilesDirectory = "./RecordFiles";
const string BufferManager::indexFilesDirectory = "./IndexFiles";
const string BufferManager::recordCatalogFilesDirectory = "./RecordCatalogFiles";
const string BufferManager::indexCatalogFilesDirectory = "./IndexCatalogFiles";

#endif /* BufferManager_hpp */
