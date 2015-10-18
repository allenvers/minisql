//
//  BufferManager.cpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "BufferManager.hpp"

map<string, PageIndexType> BufferManager::tableFileHandles;
map<pair<string, string>, PageIndexType> BufferManager::indexFileHandles;
map<string, PageIndexType> BufferManager::tableCatalogFileHandles;
map<pair<string, string>, PageIndexType> BufferManager::indexCalalogFileHandles;

const string BufferManager::recordFilesDirectory = "./RecordFiles";
const string BufferManager::indexFilesDirectory = "./IndexFiles";
const string BufferManager::recordCatalogFilesDirectory = "./RecordCatalogFiles";
const string BufferManager::indexCatalogFilesDirectory = "./IndexCatalogFiles";


bool BufferManager::openTableFile(string tableName) {
    string filePath = tableFilePath(tableName);
    if (tableFileHandles.find(tableName) == tableFileHandles.end()) {
        int fileHandle = open(filePath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fileHandle < 0) return false;
        tableFileHandles[tableName] = fileHandle;
        makeTwoPages(fileHandle);
        return true;
    }
    cout << "File " << filePath << " " << "already opened" << endl;
    return false;
}

bool BufferManager::openIndexFile(string tableName, string attributeName) {
    auto indexPair = make_pair(tableName, attributeName);
    string filePath = indexFilePath(tableName, attributeName);
    if (indexFileHandles.find(indexPair) == indexFileHandles.end()) {
        int fileHandle = open(filePath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fileHandle < 0) return false;
        indexFileHandles[indexPair] = fileHandle;
        makeTwoPages(fileHandle);
        return true;
    }
    cout << "File " << filePath << " " << "already opened" << endl;
    return false;
}

bool BufferManager::openTableCatalogFile(string tableName) {
    string filePath = tableCatalogFilePath(tableName);
    if (tableCatalogFileHandles.find(tableName) == tableCatalogFileHandles.end()) {
        int fileHandle = open(filePath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fileHandle < 0) return false;
        tableCatalogFileHandles[tableName] = fileHandle;
        makeTwoPages(fileHandle);
        return true;
    }
    cout << "File " << filePath << " " << "already opened" << endl;
    return false;
}

bool BufferManager::openIndexCatalogFile(string tableName, string attributeName) {
    auto indexPair = make_pair(tableName, attributeName);
    string filePath = indexFilePath(tableName, attributeName);
    if (indexCalalogFileHandles.find(indexPair) == indexCalalogFileHandles.end()) {
        int fileHandle = open(filePath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fileHandle < 0) return false;
        indexCalalogFileHandles[indexPair] = fileHandle;
        makeTwoPages(fileHandle);
        return true;
    }
    cout << "File " << filePath << " " << "already opened" << endl;
    return false;
}

string BufferManager::tableFilePath(string tableName) {
    return recordFilesDirectory + "/" + tableName + ".db";
}

string BufferManager::indexFilePath(string tableName, string attributeName) {
    return indexFilesDirectory + "/" + tableName + "_" + attributeName + ".db";
}

string BufferManager::tableCatalogFilePath(string tableName) {
    return recordCatalogFilesDirectory + "/" + tableName + ".db";
}

string BufferManager::indexCatalogFilePath(string tableName, string attributeName) {
    return indexCatalogFilesDirectory + "/" + tableName + "_" + attributeName + ".db";
}

void BufferManager::makeTwoPages(int fileHandle) {
    if (lseek(fileHandle, 0, SEEK_END) / PAGESIZE < 2) {
        char *pageBuffer = new char[PAGESIZE * 2];
        memset(pageBuffer, 0 , PAGESIZE * 2);
        write(fileHandle, pageBuffer, PAGESIZE * 2);
    }
}

bool BufferManager::closeTableFile(string tableName) {
    if (tableFileHandles.find(tableName) == tableFileHandles.end())
        return false;
    int handle = tableFileHandles[tableName];
    if (close(handle) != -1) return true;
    return false;
}

bool BufferManager::closeIndexFile(string tableName, string attributeName) {
    auto indexPair = make_pair(tableName, attributeName);
    if (indexFileHandles.find(indexPair) == indexFileHandles.end())
        return false;
    int handle = indexFileHandles[indexPair];
    if (close(handle) != -1) return true;
    return false;
}

bool BufferManager::closeTableCatalogFile(string tableName) {
    if (tableCatalogFileHandles.find(tableName) == tableCatalogFileHandles.end()) {
        return false;
    }
    int handle = tableCatalogFileHandles[tableName];
    if (close(handle) != -1) return true;
    return false;
}

bool BufferManager::closeIndexCatalogFile(string tableName, string attributeName) {
    auto indexPair = make_pair(tableName, attributeName);
    if (indexCalalogFileHandles.find(indexPair) == indexCalalogFileHandles.end()) {
        return false;
    }
    int handle = indexCalalogFileHandles[indexPair];
    if (close(handle != -1)) return true;
    return false;
}

void BufferManager::checkPageFile(Page &page) {
    assert(page.pageType != PageType::UndefinedPage);
    switch (page.pageType) {
        case PageType::RecordPage:
        {
            assert(page.tableName != "");
            if (tableFileHandles.find(page.tableName) == tableFileHandles.end())
                assert(openTableFile(page.tableName) == true);
            page.fileHandle = tableFileHandles[page.tableName];
        }
            break;
        case PageType::IndexPage:
        {
            assert(page.tableName != "");
            assert(page.attributeName != "");
            auto indexPair = make_pair(page.tableName, page.attributeName);
            if (indexFileHandles.find(indexPair) == indexFileHandles.end())
                assert(openIndexFile(page.tableName, page.attributeName) == true);
            page.fileHandle = indexFileHandles[indexPair];
        }
            break;
        case PageType::RecordCatalogPage:
        {
            assert(page.tableName != "");
            if (tableCatalogFileHandles.find(page.tableName) == tableCatalogFileHandles.end())
                assert(openTableCatalogFile(page.tableName) == true);
            page.fileHandle = tableCatalogFileHandles[page.tableName];
        }
            break;
        case PageType::IndexCatalogPage:
        {
            assert(page.tableName != "");
            assert(page.attributeName != "");
            auto indexPair = make_pair(page.tableName, page.attributeName);
            if (indexCalalogFileHandles.find(indexPair) == indexCalalogFileHandles.end())
                assert(openIndexCatalogFile(page.tableName, page.attributeName) == true);
            page.fileHandle = indexCalalogFileHandles[indexPair];
        }
            break;
        default:
            break;
    }
}

bool BufferManager::readPage(Page &page) {
    assert(page.pageType != PageType::UndefinedPage);
    assert(page.pageIndex != UNDEFINEED_PAGE_NUM);
    checkPageFile(page);
    lseek(page.fileHandle, page.pageIndex * PAGESIZE, SEEK_SET);
    read(page.fileHandle, page.pageData, PAGESIZE);
    return true;
}

bool BufferManager::writePage(Page &page) {
    assert(page.pageType != PageType::UndefinedPage);
    checkPageFile(page);
    lseek(page.fileHandle, page.pageIndex * PAGESIZE, SEEK_SET);
    write(page.fileHandle, page.pageData, PAGESIZE);
    return true;
}

bool BufferManager::allocatePage(Page &page) {
    assert(page.pageType != PageType::UndefinedPage);
    checkPageFile(page);
    char pageBuffer[PAGESIZE];
    lseek(page.fileHandle, 0, SEEK_SET);
    read(page.fileHandle, pageBuffer, PAGESIZE);
    
    PageIndexType pageIndex = *((PageIndexType*) pageBuffer);
    if (pageIndex != 0) {
        lseek(page.fileHandle, pageIndex * PAGESIZE, SEEK_SET);
        read(page.fileHandle, pageBuffer, PAGESIZE);
        lseek(page.fileHandle, 0, SEEK_SET);
        write(page.fileHandle, pageBuffer, PAGESIZE);
    } else {
        pageIndex = lseek(page.fileHandle, 0, SEEK_END) / PAGESIZE;
        memset(pageBuffer, 0, PAGESIZE);
        write(page.fileHandle, pageBuffer, PAGESIZE);
    }
    
    page.pageIndex = pageIndex;
    return true;
}

bool BufferManager::deallocatePage(Page &page) {
    assert(page.pageType != PageType::UndefinedPage);
    checkPageFile(page);
    
    char pageBuffer[PAGESIZE];
    lseek(page.fileHandle, 0, SEEK_SET);
    read(page.fileHandle, pageBuffer, PAGESIZE);
    
    lseek(page.fileHandle, page.pageIndex * PAGESIZE, SEEK_SET);
    write(page.fileHandle, pageBuffer, PAGESIZE);
    
    PageIndexType *pageIndex = (PageIndexType*) pageBuffer;
    *pageIndex = page.pageIndex;
    
    lseek(page.fileHandle, 0, SEEK_SET);
    write(page.fileHandle, pageBuffer, PAGESIZE);
    
    page.pageIndex = -1;
    
    return true;
}
